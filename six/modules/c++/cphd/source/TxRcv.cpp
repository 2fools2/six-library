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

#include <cphd/TxRcv.h>
#include <six/Init.h>

namespace cphd
{

ParameterType::ParameterType() :
    identifier(six::Init::undefined<std::string>()),
    freqCenter(six::Init::undefined<double>()),
    lfmRate(six::Init::undefined<double>())
{
}

TxWFParameters::TxWFParameters() :
    pulseLength(six::Init::undefined<double>()),
    rfBandwidth(six::Init::undefined<double>()),
    power(six::Init::undefined<double>())
{
}

RcvParameters::RcvParameters() :
    windowLength(six::Init::undefined<double>()),
    sampleRate(six::Init::undefined<double>()),
    ifFilterBW(six::Init::undefined<double>()),
    pathGain(six::Init::undefined<double>())
{
}

TxRcv::TxRcv() :
    numTxWFs(six::Init::undefined<size_t>()),
    numRcvs(six::Init::undefined<size_t>())
{
}

std::ostream& operator<< (std::ostream& os, const ParameterType& p)
{
    os << "    Identifier     : " << p.identifier << "\n"
        << "    FreqCenter     : " << p.freqCenter << "\n"
        << "    LFMRate        : " << p.lfmRate << "\n"
        << "    Polarization   : " << p.polarization.toString() << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const TxWFParameters& t)
{
    os << "  TxWFParamters:: \n"
        << (ParameterType)t
        << "    PulseLength    : " << t.pulseLength << "\n"
        << "    RFBandwidth    : " << t.rfBandwidth << "\n"
        << "    Power          : " << t.power << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const RcvParameters& r)
{
    os << "  RcvParamters:: \n"
        << (ParameterType)r
        << "    WindowLength   : " << r.windowLength << "\n"
        << "    SampleRate     : " << r.sampleRate << "\n"
        << "    IFFilterBW       : " << r.ifFilterBW << "\n"
        << "    PathGain       : " << r.pathGain << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const TxRcv& t)
{
    os << "TxRcv:: \n"
        << "  NumTxWFs         : " << t.numTxWFs << "\n"
        << "  NumRcvs          : " << t.numRcvs << "\n";
    for (size_t i = 0; i < t.txWFParameters.size(); ++i)
    {
        os << t.txWFParameters[i] << "\n";
    }
    for (size_t i = 0; i < t.rcvParameters.size(); ++i)
    {
        os << t.rcvParameters[i] << "\n";
    }
    return os;
}

}
