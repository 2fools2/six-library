/* =========================================================================
 * This file is part of cphd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2019, MDA Information Systems LLC
 *
 * cphd-c++ is free software; you can redistribute it and/or modify
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
 */

#ifndef __CPHD_CPHD_WRITER_H__
#define __CPHD_CPHD_WRITER_H__

#include <string>
#include <vector>

#include <types/RowCol.h>
#include <io/FileOutputStream.h>
#include <sys/OS.h>

#include <sys/Conf.h>
#include <cphd/FileHeader.h>
#include <cphd/Metadata.h>
#include <cphd/PVP.h>
#include <cphd/PVPBlock.h>

namespace cphd
{
/*
 *  \class CPHDWriter
 *  \brief Used to write a CPHD file. You must be able to provide the
 *         appropriate metadata and vector based metadata.
 */
class CPHDWriter
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the CPHDWriter
     *
     *  The default argument for numThreads should be sys::OS().getNumCPUs().
     *  However, SWIG doesn't seem to like that.
     *  As a workaround, we pass in 0 for the default, and the ctor sets the
     *  number of threads to the number of CPUs if this happens.
     *
     *  \param metadata A filled out metadata struct for the file that will be
     *         written. The data.arraySize and data.numCPHDChannels will be
     *         filled in internally. All other data must be provided.
     *  \param pathname The file path to be written to
     *  \param schemaPaths (Optional) A vector of XML schema paths for validation
     *  \param numThreads (Optional) The number of threads to use for processing.
     *  \param scratchSpaceSize (Optional) The maximum size of internal scratch space
     *         that may be used if byte swapping is necessary.
     *         Default is 4 MB
     */
    CPHDWriter(
            const Metadata& metadata,
            const std::string& pathname,
            const std::vector<std::string>& schemaPaths = std::vector<std::string>(),
            size_t numThreads = 0,
            size_t scratchSpaceSize = 4 * 1024 * 1024);

    /*
     *  \func write
     *  \brief Writes the complete CPHD into the file.
     *         This only works with valid CPHDWriter data types:
     *              std:: ubyte* (for compressed data)
     *              std::complex<float>
     *              std::complex<sys::Int16_T>
     *              std::complex<sys::Int8_T>
     *
     *  \param pvpBlock The vector based metadata to write.
     *  \param widebandData .The wideband data to write to disk
     *  \param supportData (Optional) The support array data to write to disk.
     */
    template<typename T>
    void write(
            const PVPBlock& pvpBlock,
            const T* widebandData,
            const sys::ubyte* supportData = nullptr);

    /*
     *  \func writeMetadata
     *  \brief Writes the header, and metadata into the file. This should
     *         be used in situations where you need to write out the CPHD
     *         data in chunks.
     *
     *  \param pvpBlock The vector based metadata to write.
     */
    void writeMetadata(const PVPBlock& pvpBlock);

    /*
     *  \func writeSupportData
     *  \brief Writes the specified support Array to the file
     *         Does not include padding.
     *
     *  \param data A pointer to the start of the support array that
     *        will be written to file
     *  \param id The unique identifier of the support array
     */
    template <typename T>
    void writeSupportData(const T* data,
                          const std::string& id)
    {
        writeSupportDataImpl(reinterpret_cast<const sys::ubyte*>(data),
                             mMetadata.data.getSupportArrayById(id).numRows * mMetadata.data.getSupportArrayById(id).numCols,
                             mMetadata.data.getSupportArrayById(id).bytesPerElement);
    }

    /*
     *  \func writeSupportData
     *  \brief Writes all of the support Arrays to the file
     *         Includes padding
     *
     *  \param data A pointer to the start of the support array data block
     */
    template <typename T>
    void writeSupportData(const T* data)
    {
        const sys::ubyte* dataPtr = reinterpret_cast<const sys::ubyte*>(data);
        for (auto it = mMetadata.data.supportArrayMap.begin(); it != mMetadata.data.supportArrayMap.end(); ++it)
        {
            // Move inputstream head to offset of particular support array
            mFile.seek(mHeader.getSupportBlockByteOffset() + it->second.arrayByteOffset, io::FileOutputStream::START);
            writeSupportDataImpl(dataPtr + it->second.arrayByteOffset,
                                 it->second.numRows * it->second.numCols,
                                 it->second.bytesPerElement);
        }
        // Move inputstream head to the end of the support block after all supports have been written
        mFile.seek(mHeader.getSupportBlockByteOffset() + mHeader.getSupportBlockSize(), io::FileOutputStream::START);
    }


    /*
     *  \func writePVPData
     *  \brief Writes the PVP to the file
     *
     *  \param PVPBlock A populated PVPBlock object that will be written
     *         to the file as a block of data
     */
    void writePVPData(const PVPBlock& PVPBlock);

    /*
     *  \func writeCPHDData
     *  \brief Writes a chunk of CPHD data to disk. To create a proper
     *         CPHD file you must call writeMetadata and writePVPData before
     *         using this method. This only works with
     *         valid CPHDWriter data types:
     *              std:: ubyte* (for compressed data)
     *              std::complex<float>
     *              std::complex<sys::Int16_T>
     *              std::complex<sys::Int8_T>
     *
     *  \param data The data to write to disk.
     *  \param numElements The number of elements in data. Treat the data
     *         as complex when computing the size (do not multiply by 2
     *         for correct byte swapping this is done internally).
     */
    template <typename T>
    void writeCPHDData(const T* data,
                       size_t numElements,
                       size_t channel = 1);

    /*
     * Closes the FileInputStream if open
     */
    void close()
    {
        if (mFile.isOpen())
        {
            mFile.close();
        }
    }

private:
    /*
     * Write metadata helper
     */
    void writeMetadata(
        size_t supportSize, // Optional
        size_t pvpSize,
        size_t cphdSize);

    /*
     * Write pvp helper
     */
    void writePVPData(const sys::ubyte* PVPBlock,
                      size_t index);

    /*
     * Implementation of write wideband
     */
    void writeCPHDDataImpl(const sys::ubyte* data,
                           size_t size);

    /*
     * Implementation of write compressed wideband
     */
    void writeCompressedCPHDDataImpl(const sys::ubyte* data,
                                     size_t channel);

    /*
     * Implementation of write support data
     */
    void writeSupportDataImpl(const sys::ubyte* data,
                              size_t numElements, size_t elementSize);

    /*
     * \class DataWriter
     *
     * \brief Class to handle writing to file and byte swapping
     */
    class DataWriter
    {
    public:
        /*
         * Constructor
         */
        DataWriter(io::FileOutputStream& stream,
                   size_t numThreads);

        /*
         * Destructor
         */
        virtual ~DataWriter();

        /*
         * Implementation of writing and byteswapping
         */
        virtual void operator()(const sys::ubyte* data,
                                size_t numElements,
                                size_t elementSize) = 0;

    protected:
        //! Output stream of CPHD file
        io::FileOutputStream& mStream;
        //! Number of threads for parallelism
        const size_t mNumThreads;
    };

    /*
     * \class DataWriterLittleEndian
     *
     * \brief Class to handle writing to file and byte swapping
     * for little endian to big endian storage
     * Inherits from DataWriter class
     */
    class DataWriterLittleEndian : public DataWriter
    {
    public:
        DataWriterLittleEndian(io::FileOutputStream& stream,
                               size_t numThreads,
                               size_t scratchSize);

        virtual void operator()(const sys::ubyte* data,
                                size_t numElements,
                                size_t elementSize);

    private:
        const size_t mScratchSize;
        const mem::ScopedArray<sys::byte> mScratch;
    };

    /*
     * \class DataWriterBigEndian
     *
     * \brief Class to handle writing to file
     * No byte swap. Already big endian.
     * Inherits from DataWriter class
     */
    class DataWriterBigEndian : public DataWriter
    {
    public:
        DataWriterBigEndian(io::FileOutputStream& stream,
                            size_t numThreads);

        virtual void operator()(const sys::ubyte* data,
                                size_t numElements,
                                size_t elementSize);
    };
    //! DataWriter object
    std::auto_ptr<DataWriter> mDataWriter;

    // Book-keeping element
    //! metadata information
    Metadata mMetadata;
    //! header information
    FileHeader mHeader;
    //! size of each element in signal block
    const size_t mElementSize;
    //! size of scratch space for byte swapping
    const size_t mScratchSpaceSize;
    //! number of threads for parallelism
    const size_t mNumThreads;
    //! schemas for XML validation
    std::vector<std::string> mSchemaPaths;
    //! Output stream contains CPHD file
    io::FileOutputStream mFile;
};
}

#endif
