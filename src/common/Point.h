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

#ifndef POINT_H
#define POINT_H

class CPoint
{
    public:
        CPoint();
        CPoint(double xpos, double ypos);
		~CPoint() {}

        bool isNull() const;

        double x() const;
        double y() const;
        void setX(double x);
        void setY(double y);

        double &rx();
        double &ry();

        CPoint &operator+=(const CPoint &p);
        CPoint &operator-=(const CPoint &p);
        CPoint &operator*=(double c);
        CPoint &operator/=(double c);

        friend bool operator==(const CPoint &, const CPoint &);
        friend bool operator!=(const CPoint &, const CPoint &);
        friend const CPoint operator+(const CPoint &, const CPoint &);
        friend const CPoint operator-(const CPoint &, const CPoint &);
        friend const CPoint operator*(double, const CPoint &);
        friend const CPoint operator*(const CPoint &, double);
        friend const CPoint operator+(const CPoint &);
        friend const CPoint operator-(const CPoint &);
        friend const CPoint operator/(const CPoint &, double);

    private:
        double m_x;
        double m_y;
};

#endif // POINT_H
