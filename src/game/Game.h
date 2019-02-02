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

#ifndef GAME_H
#define GAME_H

#include <Picture.h>
#include <IGame.h>
#include <IFramework.h>

class CGraphicContainer;
class CGameStateCommon;

class CGame : public IGame, private IFrameworkListener
{
	public:
		enum EGameEvent 
		{
			eGE_Exit = 0,
			eGE_Score,
			eGE_Health
		};

		enum EGameState
		{
			eGS_Invalid = -1,
			eGS_PreGame = 0,
			eGS_InGame,
			eGS_PostGame
		};

	public:
		CGame();
		virtual ~CGame();

		int lifes() const;
		int score() const;

	public:
		static const CPicture PICTURE_ALIEN_1;
		static const CPicture PICTURE_ALIEN_2;
		static const CPicture PICTURE_PLAYER;
		static const CPicture PICTURE_ROCKET;
		static const CPicture PICTURE_BOMB;

    public:
        // IGame
        bool init();
		bool refresh();
		void onEvent(SGameEvent eventId);
        // ~IGame

	private:
		// IFrameworkListener
		void onUpdate(float deltaTime);
		void onInput(CInputKey key, float deltaTime);
		// ~IFrameworkListener

		bool setGameState(EGameState state);
		void resetGame();

	private:
		CGame(const CGame &);
		CGame &operator=(const CGame &);

	private:
		CGameStateCommon * m_pState;
		EGameState m_gameState;
        EGameState m_deferredState; /* Memorizes the game state to set it at the end of the frame */

		int m_lifes;
		int m_score;
		bool m_succeded;
};

#endif // GAME_H
