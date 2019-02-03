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
extern utils::interfaces::SSystemGlobalEnvironment * g_env;

namespace game {

    CGameStatePreGame::CGameStatePreGame()
    {
        m_pContainer = g_env->pFramework->window()->addContainer();
        m_pContainer->setSize(g_env->pFramework->window()->size());

        m_pContainer->addTextfield("THE LITTLE INVADERS")->setPosition(150, 130);

        m_pContainer->addTextfield("* score advanced table *")->setPosition(145, 215);

        m_pContainer->addBitmap(CGame::picture_alien_1)->setPosition(190, 240);
        utils::interfaces::IGraphicTextfield * p_text1 = m_pContainer->addTextfield();
        p_text1->setText(" = %d",
                        g_env->pFramework->variablesManager()
                            ->variable("g_killScoreSpecial")
                            ->value<unsigned int>());

        p_text1->setPosition(220, 250);

        m_pContainer->addBitmap(CGame::picture_alien_2)->setPosition(190, 280);
        utils::interfaces::IGraphicTextfield * p_text2 = m_pContainer->addTextfield();
        p_text2->setText(" = %d",
                        g_env->pFramework->variablesManager()
                            ->variable("g_killScore")
                            ->value<unsigned int>());

        p_text2->setPosition(220, 290);

        m_pContainer->addTextfield("* press FIRE to continue *")->setPosition(145, 500);
    }

    CGameStatePreGame::~CGameStatePreGame()
    {
        g_env->pFramework->window()->removeItem(m_pContainer);
    }

    void CGameStatePreGame::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
    {
        if (get_key.get_status() == utils::interfaces::CInputKey::key_status::press &&
            get_key.get_key() == utils::interfaces::CInputKey::key::fire)
        {
            g_env->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_exit));
        }
    }

} // namespace game
