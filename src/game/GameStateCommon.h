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
#include "Game.h"

namespace game {

	class CGameStateCommon
	{
	public:
		CGameStateCommon() {}
		virtual ~CGameStateCommon() {}
		CGameStateCommon(const CGameStateCommon &) = delete;
		CGameStateCommon &operator=(const CGameStateCommon &) = delete;

		virtual bool init() = 0;

		/**
		 * @brief Propagates frame events to the game state
		 */
		virtual void onUpdate(float deltaTime) = 0;

		/**
		 * @brief Propagates input events to the game state
		 */
		virtual void onInput(utils::interfaces::CInputKey get_key, float deltaTime) = 0;
	};

} // namespace game
