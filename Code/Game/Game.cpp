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
#include "GameStateInGame.h"
#include "GameStatePreGame.h"
#include "GameStatePostGame.h"

const CPicture CGame::PICTURE_ALIEN_1 = CPicture("data\\enemy1.bmp", CRectangle(4, 5, 24, 22));
const CPicture CGame::PICTURE_ALIEN_2 = CPicture("data\\enemy2.bmp", CRectangle(1, 5, 30, 22));
const CPicture CGame::PICTURE_PLAYER = CPicture("data\\player.bmp", CRectangle(2, 7, 28, 17));
const CPicture CGame::PICTURE_ROCKET = CPicture("data\\rocket.bmp", CRectangle(14, 7, 4, 19));
const CPicture CGame::PICTURE_BOMB = CPicture("data\\bomb.bmp", CRectangle(12, 8, 8, 16));

CGame::CGame():
	m_pState(NULL),
	m_gameState(eGS_Invalid),
	m_deferredState(eGS_Invalid)
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

	if (!setGameState(eGS_PreGame))
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

bool CGame::setGameState(EGameState state)
{
	if (state == m_gameState)
		return true;

	SAFE_DELETE(m_pState);

	switch (state)
	{
		case eGS_InGame:
			m_pState = new CGameStateInGame();
			break;

		case eGS_PreGame:
			m_pState = new CGameStatePreGame();
			break;

		case eGS_PostGame:
			m_pState = new CGameStatePostGame(m_succeded, m_score);
			break;
	}

	if (!m_pState->init())
		return false;

	m_gameState = state;
	m_deferredState = state;
	return true;
}

void CGame::onEvent(SGameEvent e)
{
	switch (e.eventType)
	{
		case eGE_Exit:
			{
				if (m_gameState == eGS_PreGame) { m_deferredState = eGS_InGame; }
				else if (m_gameState == eGS_InGame) { m_succeded = e.eventValue != 0; m_deferredState = eGS_PostGame; }
				else if (m_gameState == eGS_PostGame) { m_deferredState = eGS_InGame; if (!m_succeded) resetGame(); }
			}
			break;

		case eGE_Health:
			{
				m_lifes -= e.eventValue;
			}
			break;

		case eGE_Score:
			m_score += e.eventValue;
			break;
	}
}

void CGame::onUpdate(float deltaTime)
{
	if (m_pState)
		m_pState->onUpdate(deltaTime);
}

void CGame::onInput(CInputKey key, float deltaTime)
{
	if (m_pState)
		m_pState->onInput(key, deltaTime);
}

int CGame::lifes() const
{
	return m_lifes;
}

int CGame::score() const
{
	return m_score;
}