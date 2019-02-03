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

namespace utils {
	namespace interfaces {
		struct IVariablesManager;
		struct IGraphicContainer;
		struct IGraphicBitmap;
		struct IGraphicTextfield;
	}
}

namespace game {

	class CGameStateInGame final : public CGameStateCommon, public utils::IGameTimerListener
	{
	public:
		CGameStateInGame();
		~CGameStateInGame() override;
		CGameStateInGame(const CGameStateInGame &) = delete;
		CGameStateInGame &operator=(const CGameStateInGame &) = delete;

		bool init() override;

		void onUpdate(float deltaTime) override {};
		void onInput(utils::interfaces::CInputKey get_key, float deltaTime) override;

	protected:
		// IGameTimerListener
		void timeout() override;
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

		inline bool isAlien(utils::interfaces::IGraphicItem * pItem) const { return utils::containers::gFind(m_aliens, pItem); }
		inline bool isSuperAlien(utils::interfaces::IGraphicItem * pItem) const;
		inline bool isPlayer(utils::interfaces::IGraphicItem * pItem) const;
		inline bool isRocket(utils::interfaces::IGraphicItem * pItem) const { return utils::containers::gFind(m_rockets, pItem); }
		inline bool isBomb(utils::interfaces::IGraphicItem * pItem) const { return utils::containers::gFind(m_bombs, pItem); }

		/**
		 * @brief Retreives a list of aliens able to shoot bombs
		 */
		utils::interfaces::IGraphicItem::TGraphicItems freeAliens() const;

		/**
		 * @brief Retreives a list of alive aliens
		 */
		utils::interfaces::IGraphicItem::TGraphicItems aliveAliens() const;

		/**
		 * @brief Checks if at least one alien bypassed the player (is lower than the player position)
		 * @return true if aliens bypassed player, otherwise false
		 */
		bool isAnyAlienBypassed() const;

	private:
		utils::interfaces::IGraphicContainer * m_pContainer{ nullptr };
		utils::interfaces::IGraphicContainer * m_pGameArea{ nullptr };

		utils::interfaces::IGraphicBitmap * m_pPlayer{ nullptr };

		utils::interfaces::IGraphicItem::TGraphicItems m_aliens; /* The vector behaves like a bydimentional array. Aliens deleted are set to nullptr, but not removed from array */
		bool m_aliensMoveLeft{ false };
		bool m_aliensMoveDown{ false };

		utils::interfaces::IGraphicBitmap * m_pSuperAlien{ nullptr };

		utils::interfaces::IGraphicItem::TGraphicItems m_rockets;
		utils::interfaces::IGraphicItem::TGraphicItems m_bombs;

		utils::interfaces::IGraphicTextfield * m_pScoreTextField{ nullptr };
		utils::interfaces::IGraphicTextfield * m_pHealthTextField{ nullptr };

		int m_difficulty{ 1 };

		utils::CGameTimer m_timer{ 1 / 60.0f }; // 60 fps

		utils::interfaces::IVariablesManager * m_pVariables{ nullptr };

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

} // namespace game
