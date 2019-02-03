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

#include "GameStatePostGame.h"
#include <IGraphicContainer.h>
#include <IGraphicTextfield.h>

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * gEnv;

namespace game {

	CGameStatePostGame::CGameStatePostGame(bool success, int score)
	{
		m_pContainer = gEnv->pFramework->window()->addContainer();
		m_pContainer->setSize(gEnv->pFramework->window()->size());

		if (success)
		{
			m_pContainer->addTextfield("WELL DONE EARTHLING")->setPosition(145, 130);
			m_pContainer->addTextfield("this time you win!")->setPosition(170, 160);
			m_pContainer->addTextfield("* press FIRE to continue *")->setPosition(145, 500);
		}
		else
		{
			m_pContainer->addTextfield("GAME OVER")->setPosition(185, 130);
			m_pContainer->addTextfield("earth is destroyed :(")->setPosition(160, 160);
			m_pContainer->addTextfield("* press FIRE to play again *")->setPosition(135, 500);
		}

		m_pContainer->addTextfield("You scored")->setPosition(160, 270);
		utils::interfaces::IGraphicTextfield * pTextScore = m_pContainer->addTextfield();
		pTextScore->setText("%d", score);
		pTextScore->setPosition(270, 280);
		m_pContainer->addTextfield("points")->setPosition(195, 290);
	}

	CGameStatePostGame::~CGameStatePostGame()
	{
		gEnv->pFramework->window()->removeItem(m_pContainer);
	}

	void CGameStatePostGame::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
	{
		if (get_key.get_status() == utils::interfaces::CInputKey::key_status::press && get_key.get_key() == utils::interfaces::CInputKey::key::fire)
			gEnv->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_exit));
	}

} // namespace game
