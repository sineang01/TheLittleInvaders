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
#include "Size.h"

CSize::CSize():
    m_width(-1.),
    m_height(-1.)
{
}

CSize::CSize(const CSize &sz):
    m_width(sz.width()),
    m_height(sz.height())
{
}

CSize::CSize(double width, double height):
    m_width(width),
    m_height(height)
{
}

bool CSize::isNull() const
{
    return gIsNull(m_width) && gIsNull(m_height);
}

bool CSize::isEmpty() const
{
    return m_width <= 0. || m_height <= 0.;
}

bool CSize::isValid() const
{
    return m_width >= 0. && m_height >= 0.;
}

double CSize::width() const
{
    return m_width;
}

double CSize::height() const
{
    return m_height;
}

void CSize::setWidth(double width)
{
    m_width = width;
}

void CSize::setHeight(double height)
{
    m_height = height;
}

double &CSize::rwidth()
{
    return m_width;
}

double &CSize::rheight()
{
    return m_height;
}

CSize &CSize::operator+=(const CSize &s)
{
    m_width += s.m_width; m_height += s.m_height;
    return *this;
}

CSize &CSize::operator-=(const CSize &s)
{
    m_width -= s.m_width; m_height -= s.m_height;
    return *this;
}

CSize &CSize::operator*=(double c)
{
    m_width *= c; m_height *= c;
    return *this;
}

bool operator==(const CSize &s1, const CSize &s2)
{
    return gFuzzyCompare(s1.m_width, s2.m_width) && gFuzzyCompare(s1.m_height, s2.m_height);
}

bool operator!=(const CSize &s1, const CSize &s2)
{
    return !gFuzzyCompare(s1.m_width, s2.m_width) || !gFuzzyCompare(s1.m_height, s2.m_height);
}

const CSize operator+(const CSize & s1, const CSize & s2)
{
    return CSize(s1.m_width+s2.m_width, s1.m_height+s2.m_height);
}

const CSize operator-(const CSize &s1, const CSize &s2)
{
    return CSize(s1.m_width-s2.m_width, s1.m_height-s2.m_height);
}

const CSize operator*(const CSize &s, double c)
{
    return CSize(s.m_width*c, s.m_height*c);
}

const CSize operator*(double c, const CSize &s)
{
    return CSize(s.m_width*c, s.m_height*c);
}

CSize &CSize::operator/=(double c)
{
    assert(!gFuzzyIsNull(c));
    m_width = m_width/c; m_height = m_height/c;
    return *this;
}

const CSize operator/(const CSize &s, double c)
{
    assert(!gFuzzyIsNull(c));
    return CSize(s.m_width/c, s.m_height/c);
}

CSize CSize::expandedTo(const CSize & otherSize) const
{
    return CSize(std::max(m_width,otherSize.m_width), std::max(m_height,otherSize.m_height));
}

CSize CSize::boundedTo(const CSize & otherSize) const
{
    return CSize(std::min(m_width,otherSize.m_width), std::min(m_height,otherSize.m_height));
}
