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

#include "CSVReader.h"
#include <cassert>
#include <sstream>

CCSVReader::CCSVReader(const char * filePath):
	m_filePath(filePath)
{
}

bool CCSVReader::open()
{
	m_file.open(m_filePath.c_str(), std::ios::in | std::ios::binary);
	if (m_file.is_open())
		return true;

	return false;
}

void CCSVReader::setFile(const char * filePath)
{
	assert(filePath && filePath[0]);
	m_filePath = filePath;
}

bool CCSVReader::readAll(TContent & ret)
{
	ret.clear();

	if (!open())
		return false;

	while(m_file.good())
	{
		ret.push_back(readNextLine());
	}
		 
	close();
	return true;
}

CCSVReader::TRow CCSVReader::readNextLine()
{
	assert(m_file.good());

	TRow ret;

	std::string line;
	std::getline(m_file, line);

	if (line[line.size() - 1] == '\r')
		line.resize(line.size() - 1);

	std::stringstream lineStream(line);
	std::string cell;

	//doesn't care about escaping comma and newline, can't embed comma and newline in quotes
	while(std::getline(lineStream, cell, ';'))
	{
		ret.push_back(cell);
	}

	return ret;
}
