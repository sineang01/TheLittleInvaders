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
#include "Rectangle.h"
#include <string>

class CPicture
{
	public:
		CPicture() = default;
		CPicture(const char * imagePath);
		CPicture(const char * imagePath, const CRectangle & shape);

        inline bool isNull() const { return m_imagePath.empty(); }
        inline bool isEmpty() const { return m_imagePath.empty(); }
        inline bool isValid() const { return !m_imagePath.empty() && rectangle().contains(m_shape); }

		inline const char * image() const { return m_imagePath.c_str(); }
		inline void setImage(const char * imagePath);

		inline const CSize & size() const noexcept { return m_size; }
		inline void setSize(const CSize & size) noexcept { m_size = size; }

		inline const CRectangle & shape() const noexcept { return m_shape; }
		inline void setShape(const CRectangle& shape) noexcept { m_shape = shape; }

		inline CRectangle rectangle() const noexcept { return CRectangle(0, 0, m_size.width(), m_size.height()); }

	private:
		bool readImage();

	private:
		std::string m_imagePath;
		CSize m_size;
		CRectangle m_shape;
};
