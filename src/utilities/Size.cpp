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

#include "Size.h"

#include "MathUtils.h"
#include <cassert>

namespace utils {

	CSize::CSize(const CSize &sz)
		:m_width(sz.width())
		, m_height(sz.height())
	{
	}

	CSize::CSize(double width, double height)
		: m_width(width)
		, m_height(height)
	{
	}

	bool CSize::isNull() const
	{
		return math::gIsNull(m_width) && math::gIsNull(m_height);
	}

	bool operator==(const CSize &s1, const CSize &s2) noexcept
	{
		return math::gFuzzyCompare(s1.m_width, s2.m_width) && math::gFuzzyCompare(s1.m_height, s2.m_height);
	}

	bool operator!=(const CSize &s1, const CSize &s2) noexcept
	{
		return !math::gFuzzyCompare(s1.m_width, s2.m_width) || !math::gFuzzyCompare(s1.m_height, s2.m_height);
	}

	CSize &CSize::operator/=(double c) noexcept
	{
		assert(!math::gFuzzyIsNull(c));
		m_width = m_width / c; m_height = m_height / c;
		return *this;
	}

	const CSize operator/(const CSize &s, double c) noexcept
	{
		assert(!math::gFuzzyIsNull(c));
		return CSize(s.m_width / c, s.m_height / c);
	}

} // namespace utils
