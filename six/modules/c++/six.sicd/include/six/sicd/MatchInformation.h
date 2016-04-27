/* =========================================================================
 * This file is part of six.sicd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
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
#ifndef __SIX_MATCH_INFORMATION_H__
#define __SIX_MATCH_INFORMATION_H__

#include "six/Types.h"
#include "six/Init.h"
#include "six/Parameter.h"
#include "six/ParameterCollection.h"
#include <mem/ScopedCopyablePtr.h>

namespace six
{
namespace sicd
{

/*!
 *  \struct MatchCollect
 *  \brief  Block containing information about match collection. Block repeated
 *          for match collection = 1 to NumMatchCollections.
 *
 *  Added in 1.0.0 
 *  This object is used for fields previously in 0.4.1
 *      - coreName
 *      - parameters
 */
struct MatchCollect
{
    //! Constructor
    MatchCollect();

    //! Text string that uniquely identifies the matching collection.
    std::string coreName;

    //! Collection sequence index for the match collection.
    //  Added in 1.0.0
    int matchIndex;

    //! Relevant match parameter. Attribute name identifies the parameter.
    ParameterCollection parameters;

    //! Equality operator
    bool operator==(const MatchCollect& rhs) const
    {
        return (coreName == rhs.coreName && matchIndex == rhs.matchIndex &&
            parameters == rhs.parameters);
    }

    bool operator!=(const MatchCollect& rhs) const
    {
        return !(*this == rhs);
    }
};

/*!
 *  \struct MatchCollection
 *  \brief SICD MatchInfoo/Collect
 *
 *  Block containing information about the n'th matched
 *  collection.  Match types are text strings describing the
 *  collection (e.g., COHERENT, STEREO)
 */
struct MatchType
{
    //! Constructor
    MatchType();

    //! Platform id.  List rcv only platform for bistatic colls
    //  only exists in 0.4.1
    std::string collectorName;

    //! Optional - tx platform identifier for bistatic match colls
    //  only exists in 0.4.1
    std::string illuminatorName;

    //! Match type is a string describing the collect
    //  only exists in 0.4.1
    std::vector<std::string> matchType;

    //! Text string identifying the match type. Examples: COHERENT, STEREO
    //  added in 1.0.0
    std::string typeID;

    //! Optional - Collection sequence index for the current collection.
    //  added in 1.0.0
    int currentIndex;

    //! Block containing information about match collection. Block repeated
    //  for match collection = 1 to NumMatchCollections.
    std::vector<MatchCollect> matchCollects;

    bool operator==(const MatchType& rhs) const;
    bool operator!=(const MatchType& rhs) const
    {
        return !(*this == rhs);
    }
};

/*!
 *  \struct MatchInformation
 *  \brief SICD MatchInfo
 *
 *  Parameters describing other imaging collections that are matched
 *  or related to this collection.  This parameter block is optional
 *  in the SICD spec.
 */
struct MatchInformation
{
public:

    //!  Constructor.  Creates a single default-constructed collection.
    MatchInformation();

    /*!
     *  At least one is mandatory.
     *  called "Collect" in 0.4.x
     *  called "MatchType" in 1.x
     */
    std::vector<mem::ScopedCopyablePtr<MatchType> > types;

    //! Equality operator
    bool operator==(const MatchInformation& rhs) const
    {
        return types == rhs.types;
    }

    bool operator!=(const MatchInformation& rhs) const
    {
        return !(*this == rhs);
    }
};

}
}
#endif

