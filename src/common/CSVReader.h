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
#include <fstream>
#include <string>
#include <vector>

class CCSVReader
{
	public:
		typedef std::string TCell;
		typedef std::vector<TCell> TRow;
		typedef std::vector<TRow> TContent;

	public:
		CCSVReader(const char * filePath);
		~CCSVReader() {};

        bool isNull() const;
        bool isEmpty() const;
		bool isValid() const;

		const char * file() const;
		void setFile(const char * filePath);

		bool readAll(TContent & ret);

	private: 
		CCSVReader();
		CCSVReader(const CCSVReader &);
		CCSVReader &operator=(const CCSVReader &);

	private:
		bool open();
		void close();

		TRow readNextLine();

	private:
		std::string m_filePath;
		std::ifstream m_file;
};
