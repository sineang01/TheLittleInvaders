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

#include "Point.h"

#include "MathUtils.h"

CPoint::CPoint()
    :m_x(0)
    ,m_y(0)
{
}

CPoint::CPoint(double xpos, double ypos)
    :m_x(xpos)
    ,m_y(ypos)
{
}

bool CPoint::isNull() const
{
    return math::gIsNull(m_x) && math::gIsNull(m_y);
}

bool operator==(const CPoint &p1, const CPoint &p2) noexcept
{
    return math::gFuzzyIsNull(p1.m_x - p2.m_x) && math::gFuzzyIsNull(p1.m_y - p2.m_y);
}

bool operator!=(const CPoint &p1, const CPoint &p2) noexcept
{
    return !math::gFuzzyIsNull(p1.m_x - p2.m_x) || !math::gFuzzyIsNull(p1.m_y - p2.m_y);
}
