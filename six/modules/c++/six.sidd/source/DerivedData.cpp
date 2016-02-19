/* =========================================================================
 * This file is part of six.sidd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
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
#include <sys/Conf.h>
#include <except/Exception.h>
#include <six/sidd/DerivedData.h>

namespace six
{
namespace sidd
{
const char DerivedData::VENDOR_ID[] = "MDA-IS";

DerivedData::DerivedData() :
    productCreation(new ProductCreation),
    mVersion("1.0.0")
{
}

Data* DerivedData::clone() const
{
    return new DerivedData(*this);
}

LatLonCorners DerivedData::getImageCorners() const
{
    if (geographicAndTarget.get())
    {
        // SIDD 1.1
        if (geographicAndTarget->imageCorners.get())
        {
            return *geographicAndTarget->imageCorners;
        }

        // SIDD 1.0
        if (geographicAndTarget->geographicCoverage.get())
        {
            return geographicAndTarget->geographicCoverage->footprint;
        }
    }

    throw except::Exception(Ctxt(
            "GeographicAndTarget fields aren't set to provide image corners"));
}

void DerivedData::setImageCorners(const LatLonCorners& imageCorners)
{
    if (geographicAndTarget.get() && geographicAndTarget->imageCorners.get())
    {
        *geographicAndTarget->imageCorners = imageCorners;
    }
    else if (geographicAndTarget.get() &&
             geographicAndTarget->geographicCoverage.get())
    {
        geographicAndTarget->geographicCoverage->footprint = imageCorners;
    }
    else
    {
        throw except::Exception(Ctxt(
                "GeographicAndTarget fields aren't allocated to set image "
                "corners"));
    }
}

DateTime DerivedData::getCollectionStartDateTime() const
{
    if (!exploitationFeatures.get() ||
        exploitationFeatures->collections.empty())
    {
        throw except::Exception(Ctxt("Must add a collection first"));
    }

    return exploitationFeatures->collections[0]->information.collectionDateTime;
}

LUT* DerivedData::getDisplayLUT()
{
    if (mVersion == "1.0.0")
    {
        return display->remapInformation->remapLUT.get();
    }
    else if (mVersion == "1.1.0")
    {
        if (display->nonInteractiveProcessing->productGenerationOptions.dataRemapping->custom.get())
        {
            return &(display->nonInteractiveProcessing->productGenerationOptions.dataRemapping->custom->lut);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        throw except::Exception(Ctxt("Unknown version. Expected 1.1.0 or 1.0.0"));
    }
}

types::RowCol<double>
DerivedData::pixelToImagePoint(const types::RowCol<double>& pixelLoc) const
{
    const types::RowCol<double> posRC(pixelLoc);
    types::RowCol<double> fullScenePos;
    if (downstreamReprocessing.get() &&
            downstreamReprocessing->geometricChip.get())
    {
        fullScenePos = downstreamReprocessing->geometricChip->
                getFullImageCoordinateFromChip(posRC);
    }
    else
    {
        fullScenePos = posRC;
    }

    if (!measurement->projection->isMeasurable())
    {
        throw except::Exception(Ctxt(
                "Currently require a measurable projection type"));
    }

    const six::sidd::MeasurableProjection* projection =
            reinterpret_cast<six::sidd::MeasurableProjection*>(
                    measurement->projection.get());
    const types::RowCol<double> ctrPt = projection->referencePoint.rowCol;

    return types::RowCol<double>(
            (fullScenePos.row - ctrPt.row) * projection->sampleSpacing.row,
            (fullScenePos.col - ctrPt.col) * projection->sampleSpacing.col);
}
}
}
