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

#include "LibraryHandler.h"
#include <cassert>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include <windows.h>

CLibraryHandler::CLibraryHandler(const char * library):
	m_libraryHandler(nullptr)
{
	assert(library && library[0]);
	m_libraryName = library;
}

CLibraryHandler::~CLibraryHandler()
{
	if (m_libraryHandler)
	{
		FreeLibrary(m_libraryHandler);
	}
}

bool CLibraryHandler::init()
{
	if (m_libraryHandler)
	{
		std::cerr << "[ERROR] Library " << m_libraryName.c_str() << " is already open" << std::endl;
		return false;
	}

	m_libraryHandler = LoadLibraryA(m_libraryName.c_str());
	if (!m_libraryHandler)
	{
		std::cerr << "[ERROR] Failed to open the DLL " << m_libraryName.c_str() << std::endl;
		return false;
	}

	return true;
}

HMODULE CLibraryHandler::libraryHandler() const
{
	return m_libraryHandler;
}

const char * CLibraryHandler::libraryName() const
{
	return m_libraryName.c_str();
}
