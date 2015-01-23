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
#include "Game.h"

#include "ISystemGlobalEnvironment.h"
SSystemGlobalEnvironment * gEnv = NULL;

extern "C"
{
	__declspec(dllexport) IGame * CreateGame(SSystemGlobalEnvironment * env)
	{
		gEnv = env;
		gEnv->pGame = new CGame();
		return gEnv->pGame;
	}

	__declspec(dllexport) void DestroyGame()
	{
		if (gEnv->pGame)
		{
			CGame * pGame = static_cast<CGame*>(gEnv->pGame);
			SAFE_DELETE(pGame);
			gEnv->pGame = NULL;
		}
	}
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
} 