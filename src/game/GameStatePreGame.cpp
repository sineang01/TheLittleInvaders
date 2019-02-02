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

#include "GameStatePreGame.h"
#include <IGraphicBitmap.h>
#include <IGraphicContainer.h>
#include <IGraphicTextfield.h>

#include "ISystemGlobalEnvironment.h"
extern SSystemGlobalEnvironment * gEnv;

CGameStatePreGame::CGameStatePreGame()
{
	m_pContainer = gEnv->pFramework->window()->addContainer();
	m_pContainer->setSize(gEnv->pFramework->window()->size());

	m_pContainer->addTextfield("THE LITTLE INVADERS")->setPosition(150, 130);

	m_pContainer->addTextfield("* score advanced table *")->setPosition(145, 215);
	
	m_pContainer->addBitmap(CGame::PICTURE_ALIEN_1)->setPosition(190, 240);
	IGraphicTextfield * pText1 = m_pContainer->addTextfield();
	pText1->setText(" = %d", gEnv->pFramework->variablesManager()->variable("g_killScoreSpecial")->value<unsigned int>());
	pText1->setPosition(220, 250);

	m_pContainer->addBitmap(CGame::PICTURE_ALIEN_2)->setPosition(190, 280);
	IGraphicTextfield * pText2 = m_pContainer->addTextfield();
	pText2->setText(" = %d", gEnv->pFramework->variablesManager()->variable("g_killScore")->value<unsigned int>());
	pText2->setPosition(220, 290);

	m_pContainer->addTextfield("* press FIRE to continue *")->setPosition(145, 500);
}

CGameStatePreGame::~CGameStatePreGame()
{
	gEnv->pFramework->window()->removeItem(m_pContainer);
}

void CGameStatePreGame::onInput(CInputKey get_key, float deltaTime)
{
	if (get_key.get_status() == CInputKey::key_status::press && get_key.get_key() == CInputKey::key::fire)
		gEnv->pGame->onEvent(SGameEvent(CGame::eGE_Exit));
}
