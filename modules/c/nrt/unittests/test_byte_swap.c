/* =========================================================================
 * This file is part of NITRO
 * =========================================================================
 *
 * (C) Copyright 2004 - 2016, MDA Information Systems LLC
 *
 * NITRO is free software; you can redistribute it and/or modify
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
 * License along with this program;
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <import/nrt.h>
#include "Test.h"


TEST_CASE(testFourBytes)
{
    nrt_Uint32 value;
    nrt_Uint32 swappedValue;

    value = 0x03040506;
    swappedValue = 0x06050403;
    nrt_Utils_byteSwap(&value, 4);
    TEST_ASSERT(value == swappedValue);
}

TEST_CASE(testTwoBytes)
{
    nrt_Uint16 value;
    nrt_Uint16 swappedValue;

    value = 0x0304;
    swappedValue = 0x0403;
    nrt_Utils_byteSwap(&value, 2);
    TEST_ASSERT(value == swappedValue);
}

TEST_CASE(testEightBytes)
{
    nrt_Uint64 value;
    nrt_Uint64 swappedValue;
    nrt_Uint64 originalValue;

    value = 0x0102030405060708;
    originalValue = 0x0102030405060708;
    swappedValue = 0x0807060504030201;
    /* This shouldn't do anything, because we don't handle this case */
    nrt_Utils_byteSwap(&value, 8);
    TEST_ASSERT(value == originalValue);
    TEST_ASSERT(value != swappedValue);
}

int main(int argc, char **argv)
{
    CHECK(testFourBytes);
    CHECK(testTwoBytes);
    CHECK(testEightBytes);
    return 0;
}
