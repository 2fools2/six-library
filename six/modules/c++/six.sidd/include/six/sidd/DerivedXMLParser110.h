/* =========================================================================
 * This file is part of six.sidd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2015, MDA Information Systems LLC
 *
 * six.sidd-c++ is free software; you can redistribute it and/or modify
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

#ifndef __SIX_SIDD_DERIVED_XML_PARSER_110_H__
#define __SIX_SIDD_DERIVED_XML_PARSER_110_H__

#include <six/sidd/DerivedXMLParser.h>

namespace six
{
namespace sidd
{
class DerivedXMLParser110 : public DerivedXMLParser
{
public:
    DerivedXMLParser110(logging::Logger* log = NULL,
                        bool ownLog = false);

    virtual xml::lite::Document* toXML(const DerivedData* data) const;

    virtual DerivedData* fromXML(const xml::lite::Document* doc) const;

protected:
    virtual void parseDerivedClassificationFromXML(
            const XMLElem classificationXML,
            DerivedClassification& classification) const;

    virtual XMLElem convertDerivedClassificationToXML(
            const DerivedClassification& classification,
            XMLElem parent = NULL) const;

    virtual void parseCompressionFromXML(const XMLElem compressionXML,
                                         Compression& compression) const;

    virtual XMLElem convertCompressionToXML(const Compression& compression,
                                    XMLElem parent = NULL) const;

    virtual XMLElem convertDisplayToXML(const Display& display,
                                        XMLElem parent = NULL) const;

    virtual void parseDisplayFromXML(const XMLElem displayXML,
                                     Display& display) const;


private:
    static const char VERSION[];
    static const char SI_COMMON_URI[];
    static const char ISM_URI[];

    XMLElem convertLookupTableToXML(
            const std::string& name,
            const LookupTable& table,
            XMLElem parent = NULL) const;

    XMLElem convertNonInteractiveProcessingToXML(
            const NonInteractiveProcessing& processing,
            XMLElem parent = NULL) const;

    XMLElem convertInteractiveProcessingToXML(
            const InteractiveProcessing& processing,
            XMLElem parent = NULL) const;

    XMLElem convertPredefinedFilterToXML(
            const Filter::Predefined& predefined,
            XMLElem parent = NULL) const;

    XMLElem convertKernelToXML(
            const Filter::Kernel& kernel,
            XMLElem parent = NULL) const;

    XMLElem convertBankToXML(
            const Filter::Bank& bank,
            XMLElem parent = NULL) const;

    XMLElem convertFilterToXML(const std::string& name,
                               const Filter& Filter,
                               XMLElem parent = NULL) const;

    void convertJ2KToXML(const J2KCompression& j2k,
                         XMLElem& parent) const;

    XMLElem convertGeographicTargetToXML(const GeographicAndTarget& g,
                                         XMLElem parent = NULL) const;

    XMLElem convertDigitalElevationDataToXML(const DigitalElevationData& ded,
                                             XMLElem parent = NULL) const;

    void parseJ2KCompression(const XMLElem j2kElem,
                             J2KCompression& j2k) const;

    void parseGeographicTargetFromXML(
            const XMLElem elem,
            GeographicAndTarget& geographicAndTarget) const;

    void parseDigitalElevationDataFromXML(const XMLElem elem,
                                          DigitalElevationData& ded) const;

    void parseBandInformationFromXML(const XMLElem bandXML,
         BandInformation& bandInformation) const;
    
    void parseNonInteractiveProcessingFromXML(const XMLElem procElem,
         NonInteractiveProcessing& nonInteractiveProcessing) const;

    void parseProductGenerationOptionsFromXML(const XMLElem optionsElem,
         ProductGenerationOptions& options) const; 

    void parseBandEqualizationFromXML(const XMLElem bandElem,
         BandEqualization& band) const;
    
    void parseRRDSFromXML(const XMLElem rrdsElem, RRDS& rrds) const;

    void parsePredefinedFilterFromXML(const XMLElem predefinedElem,
         Filter::Predefined& predefined) const;

    void parseKernelFromXML(const XMLElem kernelElem, 
         Filter::Kernel& kernel) const;

    void parseBankFromXML(const XMLElem bankElem, Filter::Bank& bank) const;

    void parseFilterFromXML(const XMLElem filterELem, Filter& filter) const;

    void parseInteractiveProcessingFromXML(const XMLElem interactiveElem,
         InteractiveProcessing& interactive) const;

    void parseGeometricTransformFromXML(const XMLElem geomElem,
         GeometricTransform& transform) const;
         
    void parseSharpnessEnhancementFromXML(const XMLElem sharpElem,
         SharpnessEnhancement& sharpness) const;

    void parseColorSpaceTransformFromXML(const XMLElem colorElem,
         ColorSpaceTransform& transform) const;

    void parseDynamicRangeAdjustmentFromXML(const XMLElem rangeElem,
         DynamicRangeAdjustment& rangeAdjustment) const;

    void parseLookupTableFromXML(const XMLElem lookupElem,
          LookupTable& lookupTable) const;
};
}
}

#endif
