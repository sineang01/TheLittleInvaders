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

#include <IFramework.h>
#include <LibraryHandler.h>
#include <iostream>

#include "ISystemGlobalEnvironment.h"
utils::interfaces::SSystemGlobalEnvironment * gEnv = nullptr;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include <windows.h>

static const char * ENGINE_LIBRARY_NAME = "Engine.dll";
static const char * ENGINE_LIBRARY_ENTRY_POINT_CREATE = "CreateEngine";
static const char * ENGINE_LIBRARY_ENTRY_POINT_DESTROY = "DestroyEngine";

int main(int argc, char ** argv)
{
	utils::CLibraryHandler engineDll(ENGINE_LIBRARY_NAME);
	if (!engineDll.init())
		return -1;

	utils::interfaces::IFramework::TEntryFunctionCreate CreateEngine = (utils::interfaces::IFramework::TEntryFunctionCreate)GetProcAddress(engineDll.libraryHandler(), ENGINE_LIBRARY_ENTRY_POINT_CREATE);
	if (!CreateEngine)
	{
		std::cerr << "[ERROR] Specified " << engineDll.libraryName() << " doesn't have a valid CreateEngine entry point" << std::endl;
		return -1;
	}

	gEnv = new utils::interfaces::SSystemGlobalEnvironment();

	utils::interfaces::IFramework * pFramework = CreateEngine(gEnv);
	if (!pFramework)
	{
		std::cerr << "[ERROR] Failed to create the framework interface" << std::endl;
		return -1;
	}

    if (!pFramework->init())
	{
		std::cerr << "[ERROR] Failed to initialize the framework interface" << std::endl;
		return -1;
	}
		
	int ret_value = pFramework->exec();

	utils::interfaces::IFramework::TEntryFunctionDestroy DestroyEngine = (utils::interfaces::IFramework::TEntryFunctionDestroy)GetProcAddress(engineDll.libraryHandler(), ENGINE_LIBRARY_ENTRY_POINT_DESTROY);
	if (!DestroyEngine)
	{
		std::cerr << "[ERROR] Specified " << engineDll.libraryName() << " doesn't have a valid DestroyEngine entry point" << std::endl;
		return -1;
	}

	DestroyEngine();
	delete gEnv;

	return ret_value;
}

