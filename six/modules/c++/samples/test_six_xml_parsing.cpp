/* =========================================================================
 * This file is part of six.sicd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
 *
 * six.sicd-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not,
 * see <http://www.gnu.org/licenses/>.
 *
 * Simple program to round-trip SICD or SIDD XML and verify the resulting XML matches
 */
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <sys/OS.h>
#include <sys/Path.h>
#include <except/Exception.h>
#include <six/XMLControl.h>
#include <six/sicd/ComplexXMLControl.h>
#include <six/sidd/DerivedXMLControl.h>
#include <six/sidd/DerivedData.h>
#include <six/Utilities.h>
#include <io/FileInputStream.h>
#include <logging/StreamHandler.h>

namespace
{
class XMLVerifier
{
public:
    XMLVerifier();

    void verify(const std::string& pathname) const;

private:
    void readFile(const std::string& pathname, std::string& contents) const;

private:
    six::XMLControlRegistry mXmlRegistry;
    std::vector<std::string> mSchemaPaths;
    mutable logging::Logger mLog;

    mutable std::vector<char> mScratch;
};

XMLVerifier::XMLVerifier()
{
    // Verify schema path is set
    sys::OS os;

    try
    {
        mSchemaPaths.push_back(os.getEnv(six::SCHEMA_PATH));
    }
    catch(const except::Exception& ex)
    {
        std::ostringstream oss;
        oss << "Must specify SICD/SIDD schema path via "
            << six::SCHEMA_PATH << " environment variable";
        throw except::Exception(Ctxt(oss.str()));
    }

    mXmlRegistry.addCreator(six::DataType::COMPLEX,
            new six::XMLControlCreatorT<
                    six::sicd::ComplexXMLControl>());
    mXmlRegistry.addCreator(six::DataType::DERIVED,
            new six::XMLControlCreatorT<
                    six::sidd::DerivedXMLControl>());

    mLog.addHandler(new logging::StreamHandler(logging::LogLevel::LOG_INFO),
                    true);
}

void XMLVerifier::readFile(const std::string& pathname,
                           std::string& contents) const
{
    sys::File inFile(pathname);
    mScratch.resize(inFile.length());

    if (mScratch.empty())
    {
        contents.clear();
    }
    else
    {
        inFile.readInto(&mScratch[0], mScratch.size());
        contents.assign(&mScratch[0], mScratch.size());
    }
}

void XMLVerifier::verify(const std::string& pathname) const
{
    std::cout << "Verifying " << pathname << "...";

    // Read the file in and save it off to a string for comparison later
    std::string inStr;
    readFile(pathname, inStr);

    // Parse the XML - this verifies both that the XML validates against
    // the schema and that our parser reads it without errors
    io::StringStream inStream;
    inStream.write(reinterpret_cast<const sys::byte*>(inStr.c_str()),
                   inStr.length());

    std::auto_ptr<six::Data> data(six::parseData(mXmlRegistry,
                                                 pathname,
                                                 mSchemaPaths,
                                                 mLog));

    // Write it back out - this verifies both that the XML we write validates
    // against the schema and that our parser writes it without errors
    std::auto_ptr<six::XMLControl> xmlControl(mXmlRegistry.newXMLControl(data->getDataType(), &mLog));
    std::auto_ptr<xml::lite::Document> xmlDoc(xmlControl->toXML(data.get(),
                                              mSchemaPaths));

    std::vector<std::string> separatedPath = str::split(pathname, ".");
    std::string roundTrippedPath = separatedPath[0] + "_out";
    if (separatedPath.size() == 2)
    {
        roundTrippedPath += separatedPath[1];
    }
    else
    {
        roundTrippedPath.clear();
        for (size_t ii = 0; ii < separatedPath.size() - 1; ++ii)
        {
            roundTrippedPath += separatedPath[ii];
        }
        roundTrippedPath += "_out" + separatedPath[separatedPath.size() - 1];
    }

    io::FileOutputStream outStream(roundTrippedPath);
    xmlDoc->getRootElement()->prettyPrint(outStream);
    outStream.close();

    // Now re-read the output and make sure the Data objects
    // are equal.
    std::string outStr;
    readFile(roundTrippedPath, outStr);
    inStream.reset();
    inStream.write(reinterpret_cast<const sys::byte*>(outStr.c_str()),
        outStr.length());

    std::auto_ptr<six::Data> readData(six::parseData(mXmlRegistry,
        roundTrippedPath,
        mSchemaPaths,
        mLog));

    if (data.get() == NULL || readData.get() == NULL || *data != *readData)
    {
        throw except::Exception(Ctxt(
            "Round-tripped Data does not match for '" + pathname + "'"));
    }

    std::cout << " verified" << std::endl;
}
}

int main(int argc, char** argv)
{
    try
    {
        // Parse the command line
        if (argc < 2)
        {
            std::cerr << "Usage: " << sys::Path::basename(argv[0])
                      << " <SICD or SIDD XML pathname #1>"
                      << " <SICD or SIDD XML pathname #2> ...\n";
            return 1;
        }

        XMLVerifier verifier;
        for (int ii = 1; ii < argc; ++ii)
        {
            verifier.verify(argv[ii]);
        }

        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Caught std::exception: " << ex.what() << std::endl;
        return 1;
    }
    catch (const except::Exception& ex)
    {
        std::cerr << "Caught except::exception: " << ex.getMessage()
                  << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception\n";
        return 1;
    }
}
