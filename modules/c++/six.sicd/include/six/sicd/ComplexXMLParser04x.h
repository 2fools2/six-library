/* =========================================================================
 * This file is part of six.sicd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2013, General Dynamics - Advanced Information Systems
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
 */
#ifndef __SIX_SICD_COMPLEX_XML_PARSER_04X_H__
#define __SIX_SICD_COMPLEX_XML_PARSER_04X_H__

#include <six/sicd/ComplexXMLParser.h>

namespace six
{
namespace sicd
{
class ComplexXMLParser04x : public ComplexXMLParser
{
public:
    ComplexXMLParser04x(const std::string& version,
                        bool addClassAttributes,
                        std::auto_ptr<SICommonXMLParser> comParser,
                        logging::Logger* log = NULL,
                        bool ownLog = false);

protected:

    virtual XMLElem convertRMATToXML(const RMAT* obj, 
                                     XMLElem parent = NULL) const = 0;
    virtual void parseRMATFromXML(const XMLElem rmatElem, RMAT* obj) const = 0;

protected:

    virtual XMLElem convertGeoInfoToXML(const GeoInfo *obj,
                                        XMLElem parent = NULL) const;
    virtual XMLElem convertWeightTypeToXML(const WeightType& obj, 
                                           XMLElem parent = NULL) const;
    virtual XMLElem convertRadarCollectionToXML(const RadarCollection *radar,
                                                XMLElem parent) const;
    virtual XMLElem convertImageFormationToXML(const ImageFormation *obj, 
                                       XMLElem parent = NULL) const;
    virtual XMLElem convertImageFormationAlgoToXML(
        const PFA* pfa, const RMA* rma, 
        const RgAzComp* rgAzComp, 
        XMLElem parent = NULL) const;
    virtual XMLElem convertMatchInformationToXML(const MatchInformation *obj, 
                                                 XMLElem parent = NULL) const;
    virtual XMLElem convertRMAToXML(const RMA *obj, 
                                    XMLElem parent = NULL) const;
    virtual XMLElem convertHPBWToXML(const HalfPowerBeamwidths* obj, 
                                     XMLElem parent = NULL) const;
    virtual XMLElem convertAntennaParamArrayToXML(
        const std::string& name,
        const GainAndPhasePolys* obj, 
        XMLElem parent = NULL) const;

    virtual void parseWeightTypeFromXML(const XMLElem gridRowColXML,
        mem::ScopedCopyablePtr<WeightType>& obj) const;
    virtual void parsePolarizationCalibrationFromXML(
        const XMLElem polCalXML,
        six::sicd::PolarizationCalibration* obj) const;
    virtual void parseTxRcvPolFromXML(const XMLElem parent,
                         six::DualPolarizationType& obj) const;
    virtual void parseMatchInformationFromXML(const XMLElem matchInfoXML, 
                                              MatchInformation *obj) const;
    virtual void parseRMCRFromXML(const XMLElem rmcrElem, RMCR* obj) const;
    virtual void parseAntennaParamArrayFromXML(
        const XMLElem antennaParamsXML, 
        six::sicd::AntennaParameters* obj) const;
    virtual void parseRadarCollectionFromXML(const XMLElem radarCollectionXML,
                                             RadarCollection *obj) const;

private:
    XMLElem createRcvChannels(const RadarCollection* radar,
                              XMLElem parent = NULL) const;
};
}
}

#endif

