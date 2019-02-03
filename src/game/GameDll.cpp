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

#include "Game.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "ISystemGlobalEnvironment.h"
utils::interfaces::SSystemGlobalEnvironment * g_env = nullptr;

extern "C"
{
    __declspec(dllexport) utils::interfaces::IGame * create_game(
        utils::interfaces::SSystemGlobalEnvironment * env)
    {
        g_env = env;
        g_env->pGame = new game::CGame();
        return g_env->pGame;
    }

    __declspec(dllexport) void destroy_game()
    {
        if (g_env->pGame != nullptr)
        {
            auto * p_game = static_cast<game::CGame *>(g_env->pGame);
            delete p_game;
            g_env->pGame = nullptr;
        }
    }
};

BOOL APIENTRY dllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}
