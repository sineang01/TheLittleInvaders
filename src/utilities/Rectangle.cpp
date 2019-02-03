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

#include "MathUtils.h"
#include "Rectangle.h"

namespace utils {

	CRectangle::CRectangle(double left, double top, double width, double height)
		:m_x(left)
		, m_y(top)
		, m_width(width)
		, m_height(height)
	{
	}

	CRectangle::CRectangle(const CPoint &topLeft, const CSize &size)
		:m_x(topLeft.x())
		, m_y(topLeft.y())
		, m_width(size.width())
		, m_height(size.height())
	{
	}

	CRectangle::CRectangle(const CPoint &topLeft, const CPoint &bottomRight)
		:m_x(topLeft.x())
		, m_y(topLeft.y())
		, m_width(bottomRight.x() - topLeft.x())
		, m_height(bottomRight.y() - topLeft.y())
	{
	}

	bool CRectangle::contains(const CRectangle &r) const noexcept
	{
		if (!isValid()) {
			return false;
}

		if (r.m_x < m_x || (r.m_x + r.m_width) >(m_x + m_width)) {
			return false;
}

		if (r.m_y < m_y || (r.m_y + r.m_height) >(m_y + m_height)) {
			return false;
}

		return true;
	}

	bool CRectangle::intersects(const CRectangle &r) const noexcept
	{
		if (!isValid()) {
			return false;
}

		if (m_x >= (r.m_x + r.m_width) || r.m_x >= (m_x + m_width)) {
			return false;
}

		if (m_y >= (r.m_y + r.m_height) || r.m_y >= (m_y + m_height)) {
			return false;
}

		return true;
	}

	bool operator==(const CRectangle &r1, const CRectangle &r2) noexcept
	{
		return math::gFuzzyCompare(r1.m_x, r2.m_x) && math::gFuzzyCompare(r1.m_y, r2.m_y)
			&& math::gFuzzyCompare(r1.m_width, r2.m_width) && math::gFuzzyCompare(r1.m_height, r2.m_height);
	}

	bool operator!=(const CRectangle &r1, const CRectangle &r2) noexcept
	{
		return !math::gFuzzyCompare(r1.m_x, r2.m_x) || !math::gFuzzyCompare(r1.m_y, r2.m_y)
			|| !math::gFuzzyCompare(r1.m_width, r2.m_width) || !math::gFuzzyCompare(r1.m_height, r2.m_height);
	}

} // namespace utils
