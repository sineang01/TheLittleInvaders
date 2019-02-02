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
#include <algorithm>

class CSize
{
    public:
		CSize() = default;
        CSize(const CSize &sz);
        CSize(double width, double height);

        bool isNull() const;
        inline bool isEmpty() const noexcept { return m_width <= 0. || m_height <= 0.; }
        inline bool isValid() const noexcept { return m_width >= 0. && m_height >= 0.; }

        inline double width() const noexcept { return m_width; }
        inline double height() const noexcept { return m_height; }
        inline void setWidth(double width) noexcept { m_width = width; }
        inline void setHeight(double height) noexcept { m_height = height; }

        inline CSize expandedTo(const CSize &) const noexcept;
        inline CSize boundedTo(const CSize &) const noexcept;

        inline double &rwidth() noexcept { return m_width; }
        inline double &rheight() noexcept { return m_height; }

        inline CSize &operator+=(const CSize &) noexcept;
        inline CSize &operator-=(const CSize &) noexcept;
        inline CSize &operator*=(double c) noexcept;
        CSize &operator/=(double c) noexcept;

        friend bool operator==(const CSize &, const CSize &) noexcept;
        friend bool operator!=(const CSize &, const CSize &) noexcept;
        friend inline const CSize operator+(const CSize &, const CSize &) noexcept;
        friend inline const CSize operator-(const CSize &, const CSize &) noexcept;
        friend inline const CSize operator*(const CSize &, double) noexcept;
        friend inline const CSize operator*(double, const CSize &) noexcept;
        friend const CSize operator/(const CSize &, double) noexcept;

    private:
		double m_width{-1.0};
		double m_height{-1.0};
};

CSize &CSize::operator+=(const CSize &s) noexcept
{
	m_width += s.m_width; m_height += s.m_height;
	return *this;
}

CSize &CSize::operator-=(const CSize &s) noexcept
{
	m_width -= s.m_width; m_height -= s.m_height;
	return *this;
}

CSize &CSize::operator*=(double c) noexcept
{
	m_width *= c; m_height *= c;
	return *this;
}

const CSize operator+(const CSize & s1, const CSize & s2) noexcept
{
	return CSize(s1.m_width + s2.m_width, s1.m_height + s2.m_height);
}

const CSize operator-(const CSize &s1, const CSize &s2) noexcept
{
	return CSize(s1.m_width - s2.m_width, s1.m_height - s2.m_height);
}

const CSize operator*(const CSize &s, double c) noexcept
{
	return CSize(s.m_width*c, s.m_height*c);
}

const CSize operator*(double c, const CSize &s) noexcept
{
	return CSize(s.m_width*c, s.m_height*c);
}

CSize CSize::expandedTo(const CSize & otherSize) const noexcept
{
	return CSize(std::max(m_width, otherSize.m_width), std::max(m_height, otherSize.m_height));
}

CSize CSize::boundedTo(const CSize & otherSize) const noexcept
{
	return CSize(std::min(m_width, otherSize.m_width), std::min(m_height, otherSize.m_height));
}
