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

#include "Framework.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "ISystemGlobalEnvironment.h"
utils::interfaces::SSystemGlobalEnvironment * g_env = nullptr;

extern "C"
{
    __declspec(dllexport) utils::interfaces::IFramework * create_engine(
        utils::interfaces::SSystemGlobalEnvironment * env)
    {
        g_env = env;
        g_env->pFramework = new engine::CFramework();
        return g_env->pFramework;
    }

    __declspec(dllexport) void destroy_engine()
    {
        if (g_env->pFramework != nullptr)
        {
            auto * p_framework = static_cast<engine::CFramework *>(g_env->pFramework);
            delete p_framework;
            g_env->pFramework = nullptr;
        }
    }
};

BOOL APIENTRY dllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}
