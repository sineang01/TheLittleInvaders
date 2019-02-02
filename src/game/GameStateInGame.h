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
#include "GameTimer.h"
#include <IGraphicItem.h>

struct IVariablesManager;
struct IGraphicContainer;
struct IGraphicBitmap;
struct IGraphicTextfield;

class CGameStateInGame final : public CGameStateCommon, public IGameTimerListener
{
	public:
		CGameStateInGame();
        ~CGameStateInGame();

		bool init();

		void onUpdate(float deltaTime) {};
		void onInput(CInputKey get_key, float deltaTime);

	private:
		CGameStateInGame(const CGameStateInGame &);
		CGameStateInGame &operator=(const CGameStateInGame &);

	protected:
		// IGameTimerListener
		void timeout();
		// ~IGameTimerListener

	private:
		void checkCollisionsWithBorder();
		void checkCollisionsWithPlayer();
        void checkCollisionsWithRockets();

		void checkVictoryConditions();

		void moveAliens(float deltaTime);
		void moveRockets(float deltaTime);
		void moveBombs(float deltaTime);

		void spawnAliens();
		void spawnBombs();

		void updateScore();
		void updateHealth();

		bool isAlien(IGraphicItem * pItem) const;
		bool isSuperAlien(IGraphicItem * pItem) const;
		bool isPlayer(IGraphicItem * pItem) const;
		bool isRocket(IGraphicItem * pItem) const;
		bool isBomb(IGraphicItem * pItem) const;

        /**
         * @brief Retreives a list of aliens able to shoot bombs
         */
		IGraphicItem::TGraphicItems freeAliens() const;

        /**
         * @brief Retreives a list of alive aliens
         */
		IGraphicItem::TGraphicItems aliveAliens() const;

        /**
         * @brief Checks if at least one alien bypassed the player (is lower than the player position)
         * @return true if aliens bypassed player, otherwise false
         */
		bool isAnyAlienBypassed() const;

	private:
		IGraphicContainer * m_pContainer;
		IGraphicContainer * m_pGameArea;

		IGraphicBitmap * m_pPlayer;

        IGraphicItem::TGraphicItems m_aliens; /* The vector behaves like a bydimentional array. Aliens deleted are set to nullptr, but not removed from array */
		bool m_aliensMoveLeft;
		bool m_aliensMoveDown;

		IGraphicBitmap * m_pSuperAlien;

		IGraphicItem::TGraphicItems m_rockets;
		IGraphicItem::TGraphicItems m_bombs;

		IGraphicTextfield * m_pScoreTextField;
		IGraphicTextfield * m_pHealthTextField;

		int m_difficulty;

		CGameTimer m_timer;

		IVariablesManager * m_pVariables;

		const int VAR_ALIEN_ROWS_VALUE;
		const int VAR_ALIEN_COLUMNS_VALUE;
		const float VAR_PLAYER_SPEED_VALUE;
		const float VAR_ALIEN_SPEED_VALUE;
		const float VAR_ROCKET_SPEED_VALUE;
		const float VAR_BOMB_SPEED_VALUE;
		const unsigned int VAR_BOMB_MAX_ON_SCREEN_VALUE;
		const unsigned int VAR_BOMB_PROBABILITY_VALUE;
		const int VAR_HEALTH_DAMAGE_VALUE;
		const int VAR_KILL_SCORE_VALUE;
		const int VAR_KILL_SCORE_SPECIAL_VALUE;
};
