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

class CPoint final
{
    public:
        CPoint();
        CPoint(double xpos, double ypos);

        bool isNull() const;

        inline double x() const noexcept { return m_x; }
        inline double y() const noexcept { return m_y; }
        inline void setX(double x) noexcept { m_x = x; }
        inline void setY(double y) noexcept { m_y = y; }

        inline double &rx() noexcept { return m_x; }
        inline double &ry() noexcept { return m_y; }

        inline CPoint &operator+=(const CPoint &p) noexcept;
        inline CPoint &operator-=(const CPoint &p) noexcept;
        inline CPoint &operator*=(double c) noexcept;
        inline CPoint &operator/=(double c) noexcept;

        friend bool operator==(const CPoint &, const CPoint &) noexcept;
        friend bool operator!=(const CPoint &, const CPoint &) noexcept;
        friend inline const CPoint operator+(const CPoint &, const CPoint &) noexcept;
        friend inline const CPoint operator-(const CPoint &, const CPoint &) noexcept;
        friend inline const CPoint operator*(double, const CPoint &) noexcept;
        friend inline const CPoint operator*(const CPoint &, double) noexcept;
        friend inline const CPoint operator+(const CPoint &) noexcept;
        friend inline const CPoint operator-(const CPoint &) noexcept;
        friend inline const CPoint operator/(const CPoint &, double) noexcept;

    private:
        double m_x;
        double m_y;
};

CPoint &CPoint::operator+=(const CPoint &p) noexcept
{
	m_x += p.m_x;
	m_y += p.m_y;
	return *this;
}

CPoint &CPoint::operator-=(const CPoint &p) noexcept
{
	m_x -= p.m_x;
	m_y -= p.m_y;
	return *this;
}

CPoint &CPoint::operator*=(double c) noexcept
{
	m_x *= c;
	m_y *= c;
	return *this;
}

CPoint &CPoint::operator/=(double divisor) noexcept
{
	m_x /= divisor;
	m_y /= divisor;
	return *this;
}

const CPoint operator+(const CPoint &p1, const CPoint &p2) noexcept
{
	return CPoint(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

const CPoint operator-(const CPoint &p1, const CPoint &p2) noexcept
{
	return CPoint(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

const CPoint operator*(const CPoint &p, double c) noexcept
{
	return CPoint(p.m_x*c, p.m_y*c);
}

const CPoint operator*(double c, const CPoint &p) noexcept
{
	return CPoint(p.m_x*c, p.m_y*c);
}

const CPoint operator+(const CPoint &p) noexcept
{
	return p;
}

const CPoint operator-(const CPoint &p) noexcept
{
	return CPoint(-p.m_x, -p.m_y);
}

const CPoint operator/(const CPoint &p, double divisor) noexcept
{
	return CPoint(p.m_x / divisor, p.m_y / divisor);
}
