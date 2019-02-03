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
utils::interfaces::SSystemGlobalEnvironment * g_env = nullptr;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

static const char * engine_library_name = "Engine.dll";
static const char * engine_library_entry_point_create = "create_engine";
static const char * engine_library_entry_point_destroy = "destroy_engine";

int main(int argc, char ** argv)
{
    utils::CLibraryHandler engine_dll(engine_library_name);
    if (!engine_dll.init())
    {
        return -1;
    }

    auto create_engine = (utils::interfaces::IFramework::TEntryFunctionCreate)
        GetProcAddress(engine_dll.libraryHandler(), engine_library_entry_point_create);
    if (create_engine == nullptr)
    {
        std::cerr << "[ERROR] Specified " << engine_dll.libraryName() << " doesn't have a valid "
                  << engine_library_entry_point_create << " entry point" << std::endl;

        return -1;
    }

    g_env = new utils::interfaces::SSystemGlobalEnvironment();

    utils::interfaces::IFramework * p_framework = create_engine(g_env);
    if (p_framework == nullptr)
    {
        std::cerr << "[ERROR] Failed to create the framework interface" << std::endl;
        return -1;
    }

    if (!p_framework->init())
    {
        std::cerr << "[ERROR] Failed to initialize the framework interface" << std::endl;
        return -1;
    }

    int ret_value = p_framework->exec();

    auto destroy_engine = (utils::interfaces::IFramework::TEntryFunctionDestroy)
        GetProcAddress(engine_dll.libraryHandler(), engine_library_entry_point_destroy);
    if (destroy_engine == nullptr)
    {
        std::cerr << "[ERROR] Specified " << engine_dll.libraryName() << " doesn't have a valid "
                  << engine_library_entry_point_destroy << " entry point" << std::endl;

        return -1;
    }

    destroy_engine();
    delete g_env;

    return ret_value;
}
