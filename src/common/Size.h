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

#ifndef SIZE_H
#define SIZE_H

class CSize
{
    public:
        CSize();
        CSize(const CSize &sz);
        CSize(double width, double height);
		~CSize() {}

        bool isNull() const;
        bool isEmpty() const;
        bool isValid() const;

        double width() const;
        double height() const;
        void setWidth(double width);
        void setHeight(double height);

        CSize expandedTo(const CSize &) const;
        CSize boundedTo(const CSize &) const;

        double &rwidth();
        double &rheight();

        CSize &operator+=(const CSize &);
        CSize &operator-=(const CSize &);
        CSize &operator*=(double c);
        CSize &operator/=(double c);

        friend bool operator==(const CSize &, const CSize &);
        friend bool operator!=(const CSize &, const CSize &);
        friend const CSize operator+(const CSize &, const CSize &);
        friend const CSize operator-(const CSize &, const CSize &);
        friend const CSize operator*(const CSize &, double);
        friend const CSize operator*(double, const CSize &);
        friend const CSize operator/(const CSize &, double);

    private:
        double m_width;
        double m_height;
};

#endif // SIZE_H
