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
#include "EasyPlatform.h"

static const char * PLATFORM_LIBRARY_NAME = "EasyPlatform.dll";
static const char * PLATFORM_LIBRARY_ENTRY_POINT = "EasyPlatformFactory";

CEasyPlatform::CEasyPlatform():
	CLibraryHandler(PLATFORM_LIBRARY_NAME),
	m_interface(nullptr)
{
	assert(init());
}

CEasyPlatform::~CEasyPlatform()
{
	if (m_interface)
		m_interface->destroy();
}

bool CEasyPlatform::init()
{
	if (!CLibraryHandler::init())
		return false;

	IPlatform::TEntryFunction* factory = (IPlatform::TEntryFunction*)GetProcAddress(libraryHandler(), PLATFORM_LIBRARY_ENTRY_POINT);
	m_interface = factory();
	assert(m_interface);

	return true;
}

IPlatform* CEasyPlatform::platform() const 
{
	return m_interface;
}
