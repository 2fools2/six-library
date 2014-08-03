/* =========================================================================
 * This file is part of scene-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2013, General Dynamics - Advanced Information Systems
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
#ifndef __SCENE_ERRORS_H__
#define __SCENE_ERRORS_H__

#include <math/linear/MatrixMxN.h>
#include <scene/FrameType.h>

namespace scene
{
struct Errors
{
    Errors();

    void clear();

    FrameType mFrameType;
    math::linear::MatrixMxN<7, 7> mSensorErrorCovar;
    math::linear::MatrixMxN<2, 2> mUnmodeledErrorCovar;
    math::linear::MatrixMxN<2, 2> mIonoErrorCovar;
    math::linear::MatrixMxN<1, 1> mTropoErrorCovar;
    double mPositionCorrCoefZero;
    double mPositionDecorrRate;
    double mRangeCorrCoefZero;
    double mRangeDecorrRate;
};
}

#endif
