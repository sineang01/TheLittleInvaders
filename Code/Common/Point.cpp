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

#include "stdafx.h"
#include "Point.h"

CPoint::CPoint():
    m_x(0),
    m_y(0)
{
}

CPoint::CPoint(double xpos, double ypos):
    m_x(xpos),
    m_y(ypos)
{
}

bool CPoint::isNull() const
{
    return gIsNull(m_x) && gIsNull(m_y);
}

double CPoint::x() const
{
    return m_x;
}

double CPoint::y() const
{
    return m_y;
}

void CPoint::setX(double xpos)
{
    m_x = xpos;
}

void CPoint::setY(double ypos)
{
    m_y = ypos;
}

double &CPoint::rx()
{
    return m_x;
}

double &CPoint::ry()
{
    return m_y;
}

CPoint &CPoint::operator+=(const CPoint &p)
{
    m_x+=p.m_x;
    m_y+=p.m_y;
    return *this;
}

CPoint &CPoint::operator-=(const CPoint &p)
{
    m_x-=p.m_x; m_y-=p.m_y;
    return *this;
}

CPoint &CPoint::operator*=(double c)
{
    m_x*=c; m_y*=c;
    return *this;
}

bool operator==(const CPoint &p1, const CPoint &p2)
{
    return gFuzzyIsNull(p1.m_x - p2.m_x) && gFuzzyIsNull(p1.m_y - p2.m_y);
}

bool operator!=(const CPoint &p1, const CPoint &p2)
{
    return !gFuzzyIsNull(p1.m_x - p2.m_x) || !gFuzzyIsNull(p1.m_y - p2.m_y);
}

const CPoint operator+(const CPoint &p1, const CPoint &p2)
{
    return CPoint(p1.m_x+p2.m_x, p1.m_y+p2.m_y);
}

const CPoint operator-(const CPoint &p1, const CPoint &p2)
{
    return CPoint(p1.m_x-p2.m_x, p1.m_y-p2.m_y);
}

const CPoint operator*(const CPoint &p, double c)
{
    return CPoint(p.m_x*c, p.m_y*c);
}

const CPoint operator*(double c, const CPoint &p)
{
    return CPoint(p.m_x*c, p.m_y*c);
}

const CPoint operator+(const CPoint &p)
{
    return p;
}

const CPoint operator-(const CPoint &p)
{
    return CPoint(-p.m_x, -p.m_y);
}

CPoint &CPoint::operator/=(double divisor)
{
    m_x/=divisor;
    m_y/=divisor;
    return *this;
}

const CPoint operator/(const CPoint &p, double divisor)
{
    return CPoint(p.m_x/divisor, p.m_y/divisor);
}