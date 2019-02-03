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
#include "GameStateCommon.h"
#include <IGraphicItem.h>

namespace utils {
	namespace interfaces {
		struct IGraphicContainer;
	}
}

namespace game {

	class CGameStatePostGame final : public CGameStateCommon
	{
	public:
		CGameStatePostGame(bool success, int score);
		~CGameStatePostGame();
		CGameStatePostGame(const CGameStatePostGame &) = delete;
		CGameStatePostGame &operator=(const CGameStatePostGame &) = delete;

		bool init() { return true; }

		void onUpdate(float deltaTime) {};
		void onInput(utils::interfaces::CInputKey get_key, float deltaTime);

	private:
		utils::interfaces::IGraphicContainer * m_pContainer;
	};

} // namespace game
