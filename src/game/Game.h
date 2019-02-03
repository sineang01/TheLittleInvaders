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
#include <IFramework.h>
#include <IGame.h>
#include <Picture.h>

class CGraphicContainer;

namespace game {

	class CGameStateCommon;

	class CGame final : public utils::interfaces::IGame, private utils::interfaces::IFrameworkListener
	{
	public:
		enum game_event
		{
			gameevent_exit = 0,
			gameevent_score,
			gameevent_health
		};

		enum class game_state
		{
			invalid = -1,
			pregame = 0,
			ingame,
			postgame
		};

	public:
		CGame();
		virtual ~CGame();
		CGame(const CGame &) = delete;
		CGame &operator=(const CGame &) = delete;

		int lifes() const;
		int score() const;

	public:
		static const utils::CPicture PICTURE_ALIEN_1;
		static const utils::CPicture PICTURE_ALIEN_2;
		static const utils::CPicture PICTURE_PLAYER;
		static const utils::CPicture PICTURE_ROCKET;
		static const utils::CPicture PICTURE_BOMB;

	public:
		// IGame
		bool init();
		bool refresh();
		void onEvent(utils::interfaces::SGameEvent eventId);
		// ~IGame

	private:
		// IFrameworkListener
		void onUpdate(float deltaTime);
		void onInput(utils::interfaces::CInputKey get_key, float deltaTime);
		// ~IFrameworkListener

		bool setGameState(game_state state);
		void resetGame();

	private:
		CGameStateCommon * m_pState;
		game_state m_gameState;
		game_state m_deferredState; /* Memorizes the game state to set it at the end of the frame */

		int m_lifes;
		int m_score;
		bool m_succeded;
	};

} // namespace game
