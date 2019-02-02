/****************************************************************************************
** Copyright (C) 2015 Simone Angeloni
** This file is part of The Little Invaders.
**
** The Little Invaders is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** The Little Invaders is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with The Little Invaders. If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************************/

#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Exclude annoying mix-max defines provided from Windows
#define NOMINMAX 

// Disable 'inheritance by dominance' warning
#pragma warning( disable : 4250 )

#include "ISystemGlobalEnvironment.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <windows.h>

extern SSystemGlobalEnvironment * gEnv;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);   (p)=nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p)=nullptr; } }
#endif

#define G_INT64_C(c) static_cast<long long>(c ## LL)			/* signed 64 bit constant */
#define G_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */

/**
 * @brief Rounds value to the nearest integer (7.5 => 8, -7.5 => 7)
 */
inline int gRound(double d)
{
    return d >= 0.0 ? int(d + 0.5) : int(d - double(int(d-1)) + 0.5) + int(d-1);
}

/**
 * @brief Rounds value to the nearest integer (7.5 => 8, -7.5 => 7)
 */
inline int gRound(float d)
{
    return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d-1)) + 0.5f) + int(d-1);
}

/**
 * @brief Compares the floating point value p1 and p2 and returns true if they are considered equal, otherwise false. The two numbers are compared in a relative way, where the exactness is stronger the smaller the numbers are.
 * @return true if p1 is equal to p2, otherwise false
 */
static inline bool gFuzzyCompare(double p1, double p2)
{
    return (std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2)));
}

/**
 * @brief Compares the floating point value p1 and p2 and returns true if they are considered equal, otherwise false. The two numbers are compared in a relative way, where the exactness is stronger the smaller the numbers are.
 * @return true if p1 is equal to p2, otherwise false
 */
static inline bool gFuzzyCompare(float p1, float p2)
{
    return (std::abs(p1 - p2) * 100000.f <= std::min(std::abs(p1), std::abs(p2)));
}

static inline bool gFuzzyIsNull(float f)
{
    return std::abs(f) <= 0.00001f;
}

static inline bool gFuzzyIsNull(double d)
{
    return std::abs(d) <= 0.000000000001;
}

static inline bool gIsNull(double d)
{
    union U {
        double d;
        unsigned long long u;
    };

    U val;
    val.d = d;
    return (val.u & G_UINT64_C(0x7fffffffffffffff)) == 0;
}

static inline bool gIsNull(float f)
{
    union U {
        float f;
        unsigned int u;
    };

    U val;
    val.f = f;
    return (val.u & 0x7fffffff) == 0;
}

/**
 * @brief Push back to container unique element
 * @return true if item added, false overwise
 */
template <class Container,class Value>
inline bool gPushBackUnique( Container& container,const Value &value )
{
	if (std::find(container.begin(),container.end(),value) == container.end())
	{
		container.push_back( value );
		return true;
	}
	return false;
}

/**
 * @brief Find element in container.
 * @return true if item found
 */
template <class Container,class Value>
inline bool gFind( Container& container,const Value &value )
{
	return std::find(container.begin(),container.end(),value) != container.end();
}

/**
 * @brief Find element in map.
 * @return true if item found
 */
template <class Container,class Key>
inline bool gMemberFind( Container& container,const Key &key )
{
	return container.find(key) != container.end();
}

/**
 * @brief Find and replace element from container.
 * @return true if item was find and replaced with the new one, false if item not found
 */
template <class Container,class Value>
inline bool gFindAndReplace( Container& container,const Value &value,const Value &replace )
{
	typename Container::iterator it = std::find( container.begin(),container.end(),value );
	if (it != container.end())
	{
		*it = replace;
		return true;
	}
	return false;
}

/**
 * @brief Find and erase element from container.
 * @return true if item was find and erased, false if item not found
 */
template <class Container,class Value>
inline bool gFindAndErase( Container& container,const Value &value )
{
	typename Container::iterator it = std::find( container.begin(),container.end(),value );
	if (it != container.end())
	{
		container.erase( it );
		return true;
	}
	return false;
}

/**
 * @brief Find and erase all elements matching value from container. Assume that this will invalidate any exiting iterators
 */
template <class Container>
inline void gFindAndEraseAll(Container& container, const typename Container::value_type&value)
{
	// Shuffles all elements != value to the front and returns the start of the removed elements.
	typename Container::iterator endIter(container.end());
	typename Container::iterator newEndIter(std::remove(container.begin(), endIter, value));

	// Delete the removed range at the back of the container (low-cost for vector).
	container.erase(newEndIter, endIter);
}
