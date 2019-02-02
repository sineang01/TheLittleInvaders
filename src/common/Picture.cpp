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
#include <fstream>
#include "Picture.h"
#include "Path.h"

CPicture::CPicture(const char * imagePath)
{
	setImage(imagePath);
}

CPicture::CPicture(const char * imagePath, const CRectangle & shape):
	m_shape(shape)
{
	setImage(imagePath);
}

bool CPicture::isNull() const
{
	return m_imagePath.empty();
}

bool CPicture::isEmpty() const
{
	return m_imagePath.empty();
}

bool CPicture::isValid() const
{
	return !m_imagePath.empty() && rectangle().contains(m_shape);
}

const char * CPicture::image() const
{
	return m_imagePath.c_str();
}

void CPicture::setImage(const char * imagePath)
{
	assert(imagePath && imagePath[0]);
	m_imagePath = imagePath;

	//m_size = CSize(32, 32);
	assert(readImage());
}

CSize CPicture::size() const
{
	return m_size;
}

void CPicture::setSize(const CSize & size)
{
	m_size = size;
}

CRectangle CPicture::shape() const
{
	return m_shape;
}

void CPicture::setShape(const CRectangle& shape)
{
	m_shape = shape;
}

CRectangle CPicture::rectangle() const
{
	return CRectangle(0, 0, m_size.width(), m_size.height());
}

bool CPicture::readImage()
{
	std::string path = PathUtils::executablePath();
	path += "\\";
	path += m_imagePath;

	std::ifstream fileInput(path.c_str(), std::ios::in | std::ios::binary);
	if (!fileInput.is_open())
		return false;

	static const int FORMAT_SIZE = 2;
	char fileFormat[FORMAT_SIZE+1] = {'\0'};
	fileInput.read(fileFormat, FORMAT_SIZE);
	if (strncmp(fileFormat, "BM", FORMAT_SIZE) != 0)
		return false;

	fileInput.seekg(0x12, std::ios::beg);
	unsigned int width = 0;
	fileInput.read((char*)&width, sizeof(unsigned int));

	unsigned int height = 0;
	fileInput.read((char*)&height, sizeof(unsigned int));

	m_size = CSize(width, height);
	fileInput.close();

	return true;
}
