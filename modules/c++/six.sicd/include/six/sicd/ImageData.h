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
#ifndef __SIX_IMAGE_DATA_H__
#define __SIX_IMAGE_DATA_H__

#include "six/Types.h"
#include "six/Init.h"
#include "six/Parameter.h"

namespace six
{
namespace sicd
{

/*!
 *  \struct ImageData
 *  \brief SICD ImageData parameters
 *
 *  This block describes image pixel data
 */
struct ImageData
{
    //!  Everything is undefined at this time
    ImageData() :
        pixelType(PixelType::NOT_SET),
        amplitudeTable(NULL),
        numRows(Init::undefined<size_t>()),
        numCols(Init::undefined<size_t>()),
        firstRow(0),
        firstCol(0)
    {
    }

    //!  Destructor, deletes amplitudeTable if non-NULL
    ~ImageData();

    //!  Clone this object, including amplitudeTable if non-NULL
    ImageData* clone() const;

    /*!
     *  Indicates the pixel type and binary format of the data.
     *  \todo We currently do not support AMP8I_PHS8I
     *
     */
    PixelType pixelType;

    /*!
     *  SICD AmpTable parameter.  If the data is AMP8I_PHS8I (see above)
     *  this could be initialized, and could store a double precision
     *  LUT (256 entries) that the phase portion signifies.
     *
     */
    AmplitudeTable* amplitudeTable;

    //!  Number of rows in the product, including zero-filled pixels
    size_t numRows;

    //!  Number of cols in the product, including zero-filled pixels
    size_t numCols;

    //!  Global row index (assuming this is an ROI)
    size_t firstRow;
    
    //!  Global col index (assuming this is an ROI)
    size_t firstCol;

    //!  Global row/col size (assuming this is an ROI)
    RowColInt fullImage;

    //!  Scene center (in global scene)
    RowColInt scpPixel;

    // If this doesnt have at least 3 vertices, its not going to get written
    std::vector<RowColInt> validData;

};
}
}
#endif

