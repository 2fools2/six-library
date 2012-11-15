/* =========================================================================
 * This file is part of six-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2009, General Dynamics - Advanced Information Systems
 *
 * six-c++ is free software; you can redistribute it and/or modify
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

#ifndef __SIX_SI_COMPLEX_COMMON_XML_PARSER_01X_H__
#define __SIX_SI_COMPLEX_COMMON_XML_PARSER_01X_H__

#include <six/SICommonXMLParser.h>

namespace six
{

class SICommonXMLParser01x : public SICommonXMLParser
{
public:
    SICommonXMLParser01x(const std::string& defaultURI,
                         bool addClassAttributes,
                         const std::string& siCommonURI,
                         logging::Logger* log = NULL,
                         bool ownLog = false);

    virtual XMLElem convertRadiometryToXML(
        const Radiometric *obj, 
        XMLElem parent = NULL) const;

    virtual void parseRadiometryFromXML(
        const XMLElem radiometricXML, 
        Radiometric *obj) const;


protected:

    virtual XMLElem convertCompositeSCPToXML(
        const ErrorStatistics* errorStatistics,
        XMLElem parent = NULL) const;

    virtual void parseCompositeSCPFromXML(
        const XMLElem errorStatsXML,
        ErrorStatistics* errorStatistics) const;

};

}

#endif
