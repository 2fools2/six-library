/* =========================================================================
 * This file is part of scene-c++ 
 * =========================================================================
 * 
 * (C) Copyright 2004 - 2009, General Dynamics - Advanced Information Systems
 *
 * scene-c++ is free software; you can redistribute it and/or modify
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
#ifndef __SCENE_LLA_TO_ECEF_TRANSFORM_H__
#define __SCENE_LLA_TO_ECEF_TRANSFORM_H__

#include "scene/CoordinateTransform.h"
#include <sstream>

namespace scene
{

class LLAToECEFTransform : public CoordinateTransform
{
public:

    /**
     * This constructor just calls the base class constructor
     */
    LLAToECEFTransform();

    /**
     * This constructor just calls the base class constructor
     */
    LLAToECEFTransform(const EllipsoidModel *initVals);

    ~LLAToECEFTransform(){}

    /**
     * This function returns a pointer to a clone of the LLAToECEFTransform
     * object.
     */
    LLAToECEFTransform* clone() const;

    /**
     * This function transforms an LatLonAlt to an Vector3.
     *
     * @param lla   The lla coordinate to transform
     * @return      A Vector3
     */
    Vector3 transform(const LatLonAlt& lla);
private:

    double computeRadius(const LatLonAlt& lla);
    double computeLatitude(const double lat);


};

}
#endif
