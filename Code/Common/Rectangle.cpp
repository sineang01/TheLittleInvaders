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
#include "Rectangle.h"

CRectangle::CRectangle():
    m_x(0.),
    m_y(0.),
    m_width(0.),
    m_height(0.)
{
}

CRectangle::CRectangle(double left, double top, double width, double height):
    m_x(left),
    m_y(top),
    m_width(width),
    m_height(height)
{
}

CRectangle::CRectangle(const CPoint &topLeft, const CSize &size):
    m_x(topLeft.x()),
    m_y(topLeft.y()),
    m_width(size.width()),
    m_height(size.height())
{
}

CRectangle::CRectangle(const CPoint &topLeft, const CPoint &bottomRight):
    m_x(topLeft.x()),
    m_y(topLeft.y()),
    m_width(bottomRight.x() - topLeft.x()),
    m_height(bottomRight.y() - topLeft.y())
{
}

bool CRectangle::isNull() const
{
    return m_width == 0. && m_height == 0.;
}

bool CRectangle::isEmpty() const
{
    return m_width <= 0. || m_height <= 0.;
}

bool CRectangle::isValid() const
{
    return m_width > 0. && m_height > 0.;
}

double CRectangle::x() const
{
    return m_x;
}

double CRectangle::y() const
{
    return m_y;
}

void CRectangle::setX(double pos) 
{
    m_x = pos;
}

void CRectangle::setY(double pos)
{ 
    m_y = pos;
}

void CRectangle::setPosition(const CPoint &p)
{
	setX(p.x()); 
	setY(p.y());
}

void CRectangle::setPosition(double x, double y)
{
	setX(x); 
	setY(y);
}

CPoint CRectangle::position() const
{
	return CPoint(m_x, m_y);
}

double CRectangle::width() const
{ 
    return m_width;
}

double CRectangle::height() const
{ 
    return m_height;
}

CSize CRectangle::size() const
{ 
    return CSize(m_width, m_height);
}

CRectangle CRectangle::translated(double dx, double dy) const
{ 
    return CRectangle(m_x + dx, m_y + dy, m_width, m_height);
}

CRectangle CRectangle::translated(const CPoint &p) const
{ 
    return CRectangle(m_x + p.x(), m_y + p.y(), m_width, m_height);
}

void CRectangle::setWidth(double width)
{ 
    m_width = width;
}

void CRectangle::setHeight(double height)
{ 
    m_height = height;
}

void CRectangle::setSize(const CSize &s)
{
    m_width = s.width();
    m_height = s.height();
}

bool CRectangle::contains(const CRectangle &r) const
{
	if (!isValid())
		return false;

    if (r.m_x < m_x || (r.m_x + r.m_width) > (m_x + m_width))
        return false;

    if (r.m_y < m_y || (r.m_y + r.m_height) > (m_y + m_height))
        return false;

    return true;
}

bool CRectangle::intersects(const CRectangle &r) const
{
	if (!isValid())
		return false;

    if (m_x >= (r.m_x + r.m_width) || r.m_x >= (m_x + m_width))
        return false;

    if (m_y >= (r.m_y + r.m_height) || r.m_y >= (m_y + m_height))
        return false;

    return true;
}

bool operator==(const CRectangle &r1, const CRectangle &r2)
{
    return gFuzzyCompare(r1.m_x, r2.m_x) && gFuzzyCompare(r1.m_y, r2.m_y)
           && gFuzzyCompare(r1.m_width, r2.m_width) && gFuzzyCompare(r1.m_height, r2.m_height);
}

bool operator!=(const CRectangle &r1, const CRectangle &r2)
{
    return !gFuzzyCompare(r1.m_x, r2.m_x) || !gFuzzyCompare(r1.m_y, r2.m_y)
           || !gFuzzyCompare(r1.m_width, r2.m_width) || !gFuzzyCompare(r1.m_height, r2.m_height);
}
