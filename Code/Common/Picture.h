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

#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include "Rectangle.h"

class CPicture
{
	public:
		CPicture() {};
		CPicture(const char * imagePath);
		CPicture(const char * imagePath, const CRectangle & shape);
		~CPicture() {};

        bool isNull() const;
        bool isEmpty() const;
        bool isValid() const;

		const char * image() const;
		void setImage(const char * imagePath);

		CSize size () const;
		void setSize(const CSize & size);

		CRectangle shape() const;
		void setShape(const CRectangle& shape);

		CRectangle rectangle() const;

	private:
		bool readImage();

	private:
		std::string m_imagePath;
		CSize m_size;
		CRectangle m_shape;
};

#endif // PICTURE_H
