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

class CRectangle
{
	public:
        CRectangle();
		CRectangle(const CPoint &topleft, const CSize &size);
		CRectangle(const CPoint &topleft, const CPoint &bottomRight);
		CRectangle(double left, double top, double width, double height);
		~CRectangle() {}

		bool isNull() const;
		bool isEmpty() const;
		bool isValid() const;

		double x() const;
		double y() const;
		void setX(double pos);
		void setY(double pos);

		void setPosition(double x, double y);
		void setPosition(const CPoint &p);
		CPoint position() const;

		CRectangle translated(double dx, double dy) const;
		CRectangle translated(const CPoint &p) const;

		CSize size() const;
		double width() const;
		double height() const;
        void setWidth(double width);
        void setHeight(double height);
		void setSize(const CSize &s);

		bool contains(const CRectangle &r) const;
		bool intersects(const CRectangle &r) const;

		friend bool operator==(const CRectangle &, const CRectangle &);
		friend bool operator!=(const CRectangle &, const CRectangle &);

	private:
        double m_x;
        double m_y;
        double m_width;
        double m_height;
};

bool operator==(const CRectangle &, const CRectangle &);
bool operator!=(const CRectangle &, const CRectangle &);
