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
#include "Point.h"
#include "Size.h"

class CRectangle final
{
	public:
		CRectangle() = default;
		CRectangle(const CPoint &topleft, const CSize &size);
		CRectangle(const CPoint &topleft, const CPoint &bottomRight);
		CRectangle(double left, double top, double width, double height);

		inline bool isNull() const noexcept { return m_width == 0. && m_height == 0.; }
		inline bool isEmpty() const noexcept { return m_width <= 0. || m_height <= 0.; }
		inline bool isValid() const noexcept { return m_width > 0. && m_height > 0.; }

		inline double x() const noexcept { return m_x; }
		inline double y() const noexcept { return m_y; }

		inline void setX(double pos) noexcept { m_x = pos; }
		inline void setY(double pos) noexcept { m_y = pos; }

		inline void setPosition(double x, double y) noexcept;
		inline void setPosition(const CPoint &p) noexcept;
		CPoint position() const noexcept { return CPoint(m_x, m_y); }

		inline CRectangle translated(double dx, double dy) const noexcept { return CRectangle(m_x + dx, m_y + dy, m_width, m_height); }
		inline CRectangle translated(const CPoint &p) const noexcept { return CRectangle(m_x + p.x(), m_y + p.y(), m_width, m_height); }

		inline CSize size() const noexcept { return CSize(m_width, m_height); }
		inline double width() const noexcept  { return m_width; }
		inline double height() const noexcept { return m_height; }
        inline void setWidth(double width) noexcept { m_width = width; }
		inline void setHeight(double height) noexcept { m_height = height; }
		inline void setSize(const CSize &s) noexcept;

		bool contains(const CRectangle &r) const noexcept;
		bool intersects(const CRectangle &r) const noexcept;

		friend bool operator==(const CRectangle &, const CRectangle &) noexcept;
		friend bool operator!=(const CRectangle &, const CRectangle &) noexcept;

	private:
		double m_x{0};
        double m_y{ 0 };
        double m_width{ 0 };
        double m_height{ 0 };
};

bool operator==(const CRectangle &, const CRectangle &) noexcept;
bool operator!=(const CRectangle &, const CRectangle &) noexcept;

void CRectangle::setPosition(const CPoint &p) noexcept
{
	setX(p.x());
	setY(p.y());
}

void CRectangle::setPosition(double x, double y) noexcept
{
	setX(x);
	setY(y);
}

void CRectangle::setSize(const CSize &s) noexcept
{
	m_width = s.width();
	m_height = s.height();
}
