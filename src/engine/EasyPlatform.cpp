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

#include "EasyPlatform.h"
#include <cassert>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

static const char * platform_library_name = "EasyPlatform.dll";
static const char * platform_library_entry_point = "EasyPlatformFactory";

namespace engine {
    namespace platform {

        CEasyPlatform::CEasyPlatform() : CLibraryHandler(platform_library_name) { assert(init()); }

        CEasyPlatform::~CEasyPlatform()
        {
            if (m_interface != nullptr)
            {
                m_interface->destroy();
            }
        }

        bool CEasyPlatform::init()
        {
            if (!CLibraryHandler::init())
            {
                return false;
            }

            auto * factory =
                (utils::interfaces::IPlatform::TEntryFunction *)
                    GetProcAddress(libraryHandler(), platform_library_entry_point);
            m_interface = factory();
            assert(m_interface);

            return true;
        }

    } // namespace platform
} // namespace engine
