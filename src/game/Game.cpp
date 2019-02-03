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
#include "GameStateInGame.h"
#include "GameStatePostGame.h"
#include "GameStatePreGame.h"

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * gEnv;

namespace game {

	const utils::CPicture CGame::PICTURE_ALIEN_1 = utils::CPicture("images\\enemy1.bmp", utils::CRectangle(4, 5, 24, 22));
	const utils::CPicture CGame::PICTURE_ALIEN_2 = utils::CPicture("images\\enemy2.bmp", utils::CRectangle(1, 5, 30, 22));
	const utils::CPicture CGame::PICTURE_PLAYER = utils::CPicture("images\\player.bmp", utils::CRectangle(2, 7, 28, 17));
	const utils::CPicture CGame::PICTURE_ROCKET = utils::CPicture("images\\rocket.bmp", utils::CRectangle(14, 7, 4, 19));
	const utils::CPicture CGame::PICTURE_BOMB = utils::CPicture("images\\bomb.bmp", utils::CRectangle(12, 8, 8, 16));

	CGame::CGame() :
		m_pState(nullptr),
		m_gameState(game_state::invalid),
		m_deferredState(game_state::invalid)
	{
		resetGame();
	}

	CGame::~CGame()
	{
		gEnv->pFramework->removeListener(this);
	}

	bool CGame::init()
	{
		if (!gEnv->pFramework->addListener(this))
			return false;

		if (!setGameState(game_state::pregame))
			return false;

		return true;
	}

	bool CGame::refresh()
	{
		if (!setGameState(m_deferredState))
			return false;

		return true;
	}

	void CGame::resetGame()
	{
		m_lifes = gEnv->pFramework->variablesManager()->variable("g_lifes")->value<unsigned int>();
		m_score = 0;
		m_succeded = false;
	}

	bool CGame::setGameState(game_state state)
	{
		if (state == m_gameState)
			return true;

		delete m_pState;
		m_pState = nullptr;

		switch (state)
		{
		case game_state::ingame:
			m_pState = new CGameStateInGame();
			break;

		case game_state::pregame:
			m_pState = new CGameStatePreGame();
			break;

		case game_state::postgame:
			m_pState = new CGameStatePostGame(m_succeded, m_score);
			break;
		}

		if (!m_pState->init())
			return false;

		m_gameState = state;
		m_deferredState = state;
		return true;
	}

	void CGame::onEvent(utils::interfaces::SGameEvent e)
	{
		switch (e.eventType)
		{
		case gameevent_exit:
		{
			if (m_gameState == game_state::pregame) { m_deferredState = game_state::ingame; }
			else if (m_gameState == game_state::ingame) { m_succeded = e.eventValue != 0; m_deferredState = game_state::postgame; }
			else if (m_gameState == game_state::postgame) { m_deferredState = game_state::ingame; if (!m_succeded) resetGame(); }
		}
		break;

		case gameevent_health:
		{
			m_lifes -= e.eventValue;
		}
		break;

		case gameevent_score:
			m_score += e.eventValue;
			break;
		}
	}

	void CGame::onUpdate(float deltaTime)
	{
		if (m_pState)
			m_pState->onUpdate(deltaTime);
	}

	void CGame::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
	{
		if (m_pState)
			m_pState->onInput(get_key, deltaTime);
	}

	int CGame::lifes() const
	{
		return m_lifes;
	}

	int CGame::score() const
	{
		return m_score;
	}

} // namespace game
