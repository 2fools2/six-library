/* =========================================================================
* This file is part of six.sicd-c++
* =========================================================================
*
* (C) Copyright 2004 - 2016, MDA Information Systems LLC
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

#include <cmath>
#include <iostream>
#include <vector>
#include <math/Bessel.h>
#include <six/sicd/Functor.h>

namespace six
{
namespace sicd
{

RaisedCos::RaisedCos(double coef) :
    mCoef(coef)
{
}

std::vector<double> RaisedCos::operator()(size_t n) const
{
    std::vector<double> ret;
    ret.resize(std::ceil(n / 2.0));
    for (size_t ii = 0; ii < ret.size(); ++ii)
    {
        ret[ii] = mCoef - (1 - mCoef) * std::cos(2 * M_PI * ii / (n - 1));
    }
    if (n % 2 == 0)
    {
        std::reverse_copy(ret.begin(), ret.end(), std::back_inserter(ret));
    }
    else
    {
        std::copy(ret.begin(), ret.end() - 1, std::back_inserter(ret));
    }
    return ret;
}

Kaiser::Kaiser(double beta) :
    mBeta(beta)
{
}

std::vector<double> Kaiser::operator()(size_t L) const
{
    std::vector<double> ret;
    if (L == 1)
    {
        ret.push_back(1);
        return ret;
    }

    size_t m = L - 1;
    double k;
    for (size_t ii = 0; ii < L; ++ii)
    {
        k = 2 * mBeta / m * std::sqrt(ii * (m - ii));
        ret.push_back(math::besselI(0, k) / math::besselI(0, mBeta));
    }

    return ret;
}
}
}
