/* =========================================================================
 * This file is part of cphd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
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

#ifndef __CPHD_CHANNEL_H__
#define __CPHD_CHANNEL_H__

#include <ostream>
#include <vector>
#include <stddef.h>

namespace cphd
{
struct ChannelParameters
{
    ChannelParameters();

    bool operator==(const ChannelParameters& other) const
    {
        return srpIndex == other.srpIndex &&
               nomTOARateSF == other.nomTOARateSF &&
               fxCtrNom == other.fxCtrNom &&
               bwSavedNom == other.bwSavedNom &&
               toaSavedNom == other.toaSavedNom &&
               txAntIndex == other.txAntIndex &&
               rcvAntIndex == other.rcvAntIndex &&
               twAntIndex == other.twAntIndex;
    }

    bool operator!=(const ChannelParameters& other) const
    {
        return !((*this) == other);
    }

    size_t srpIndex;
    double nomTOARateSF;
    double fxCtrNom;
    double bwSavedNom;
    double toaSavedNom;

    // optional
    size_t txAntIndex;

    // optional
    size_t rcvAntIndex;

    // optional
    size_t twAntIndex;
};

std::ostream& operator<< (std::ostream& os, const ChannelParameters& d);

struct Channel
{
    Channel()
    {
    }
    virtual ~Channel() {}

    bool operator==(const Channel& other) const
    {
        return parameters == other.parameters;
    }

    bool operator!=(const Channel& other) const
    {
        return !((*this) == other);
    }

    std::vector<ChannelParameters> parameters;
};

std::ostream& operator<< (std::ostream& os, const Channel& d);
}

#endif
