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

#ifndef GAMESTATEPREGAME_H
#define GAMESTATEPREGAME_H

#include <IGraphicItem.h>
#include "GameStateCommon.h"

struct IGraphicContainer;

class CGameStatePreGame : public CGameStateCommon
{
	public:
		CGameStatePreGame();
        ~CGameStatePreGame();

		bool init() { return true; }

		void onUpdate(float deltaTime) {};
		void onInput(CInputKey key, float deltaTime);

	private:
		CGameStatePreGame(const CGameStatePreGame &);
		CGameStatePreGame &operator=(const CGameStatePreGame &);

	private:
		IGraphicContainer * m_pContainer;
};

#endif // GAMESTATEPREGAME_H
