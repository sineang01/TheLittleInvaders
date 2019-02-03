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

#include "GameStateInGame.h"
#include <ContainersUtils.h>
#include <IGraphicBitmap.h>
#include <IGraphicContainer.h>
#include <IGraphicTextfield.h>
#include <cassert>

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * g_env;

namespace game {

    static const int difficuly_mult = 5;

    CGameStateInGame::CGameStateInGame()
        : m_pVariables(g_env->pFramework->variablesManager())
        // VARIABLE VALUES - optimization to avoid retrieving the same value every cycle
        , VAR_ALIEN_ROWS_VALUE(m_pVariables->variable("g_AlienRows")->value<unsigned int>())
        , VAR_ALIEN_COLUMNS_VALUE(m_pVariables->variable("g_AlienColumns")->value<unsigned int>())
        , VAR_PLAYER_SPEED_VALUE(m_pVariables->variable("g_PlayerSpeedPxSec")->value<float>())
        , VAR_ALIEN_SPEED_VALUE(m_pVariables->variable("g_AlienSpeedPxSec")->value<float>())
        , VAR_ROCKET_SPEED_VALUE(m_pVariables->variable("g_RocketSpeedPxSec")->value<float>())
        , VAR_BOMB_SPEED_VALUE(m_pVariables->variable("g_BombSpeedPxSec")->value<float>())
        , VAR_BOMB_MAX_ON_SCREEN_VALUE(
              m_pVariables->variable("g_BombMaxOnScreen")->value<unsigned int>())
        , VAR_BOMB_PROBABILITY_VALUE(
              m_pVariables->variable("g_BombProbablityPercentage")->value<unsigned int>())
        , VAR_HEALTH_DAMAGE_VALUE(m_pVariables->variable("g_healthDamage")->value<unsigned int>())
        , VAR_KILL_SCORE_VALUE(m_pVariables->variable("g_killScore")->value<unsigned int>())
        , VAR_KILL_SCORE_SPECIAL_VALUE(
              m_pVariables->variable("g_killScoreSpecial")->value<unsigned int>())
    {
        m_pContainer = g_env->pFramework->window()->addContainer();
        m_pContainer->setSize(g_env->pFramework->window()->size());

        const int area_h_mult = m_pVariables->variable("g_GameAreaHMult")->value<unsigned int>();
        const int area_v_mult = m_pVariables->variable("g_GameAreaVMult")->value<unsigned int>();

        m_pGameArea = m_pContainer->addContainer();
        m_pGameArea->setSize(CGame::picture_alien_2.size().width() * area_h_mult,
                             CGame::picture_alien_2.size().height() * area_v_mult);
        m_pGameArea->setPosition((m_pContainer->size().width() - m_pGameArea->size().width()) / 2,
                                 (m_pContainer->size().height() - m_pGameArea->size().height()) /
                                     2);

        m_aliens.reserve(VAR_ALIEN_COLUMNS_VALUE * VAR_ALIEN_ROWS_VALUE);
        for (int column = 0; column < VAR_ALIEN_COLUMNS_VALUE; ++column)
        {
            for (int row = 0; row < VAR_ALIEN_ROWS_VALUE; ++row)
            {
                utils::interfaces::IGraphicBitmap * p_alien =
                    m_pGameArea->addBitmap(CGame::picture_alien_2);
                m_aliens.push_back(p_alien);
                p_alien->setPosition(column * CGame::picture_alien_2.size().width(),
                                    row * CGame::picture_alien_2.size().height());
            }
        }

        m_pPlayer = m_pGameArea->addBitmap(CGame::picture_player);
        m_pPlayer->setPosition(m_pGameArea->size().width() / 2,
                               m_pGameArea->size().height() -
                                   CGame::picture_player.size().height());

        m_pScoreTextField = m_pContainer->addTextfield();
        m_pScoreTextField->setPosition(m_pGameArea->position().x(), 19);

        m_pHealthTextField = m_pContainer->addTextfield();
        m_pHealthTextField->setPosition(m_pGameArea->position().x(),
                                        m_pContainer->size().height() - 35);
    }

    CGameStateInGame::~CGameStateInGame()
    {
        m_timer.removeListener(this);
        g_env->pFramework->window()->removeItem(m_pContainer);
    }

    bool CGameStateInGame::init()
    {
        m_timer.addListener(this);
        m_timer.start();

        return true;
    }

    void CGameStateInGame::timeout()
    {
        checkCollisionsWithBorder();
        checkCollisionsWithPlayer();
        checkCollisionsWithRockets();

        moveAliens(m_timer.elapsed());
        moveRockets(m_timer.elapsed());
        moveBombs(m_timer.elapsed());

        spawnAliens();
        spawnBombs();

        updateScore();
        updateHealth();

        checkVictoryConditions();
    }

    void CGameStateInGame::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
    {
        assert(m_pPlayer);
        assert(m_pGameArea);

        if (get_key.get_status() == utils::interfaces::CInputKey::key_status::inactive)
        {
            return;
        }

        switch (get_key.get_key())
        {
            case utils::interfaces::CInputKey::key::fire:
            {
                if (get_key.get_status() == utils::interfaces::CInputKey::key_status::press)
                {
                    assert(m_pGameArea);
                    utils::interfaces::IGraphicBitmap * p_rocket =
                        m_pGameArea->addBitmap(CGame::picture_rocket);
                    m_rockets.push_back(p_rocket);
                    utils::CPoint pos = m_pPlayer->position();
                    pos.ry() -= m_pPlayer->size().height();
                    p_rocket->setPosition(pos);
                }
            }
            break;

            case utils::interfaces::CInputKey::key::left:
            {
                utils::CPoint pos = m_pPlayer->position();
                pos.rx() -= (deltaTime * VAR_PLAYER_SPEED_VALUE);
                pos.rx() = std::max(0., pos.x());
                m_pPlayer->setPosition(pos);
            }
            break;

            case utils::interfaces::CInputKey::key::right:
            {
                utils::CPoint pos = m_pPlayer->position();
                pos.rx() += (deltaTime * VAR_PLAYER_SPEED_VALUE);
                pos.rx() =
                    std::min(pos.x(),
                             m_pGameArea->size().width() - CGame::picture_player.size().width());
                m_pPlayer->setPosition(pos);
            }
            break;
        }
    }

    void CGameStateInGame::checkCollisionsWithBorder()
    {
        assert(m_pGameArea);
        m_aliensMoveDown = false;

        utils::interfaces::IGraphicItem::TGraphicItems collidingitems = m_pGameArea->collidingItems(
            m_pGameArea, utils::interfaces::IGraphicItem::collision_mode::intersect_not_contain);

        auto it_end = collidingitems.end();
        for (auto it = collidingitems.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_item = (*it);

            if (isAlien(p_item))
            {
                m_aliensMoveLeft = !m_aliensMoveLeft;
                m_aliensMoveDown = true;
                return; // One alien reaching the borders is enough to say that aliens have to move
                        // down
            }

            if (isSuperAlien(p_item))
            {
                delete m_pSuperAlien;
                m_pSuperAlien = nullptr;
            }
            else if (isRocket(p_item))
            {
                utils::containers::gFindAndErase(m_rockets, p_item);
                delete p_item;
            }
            else if (isBomb(p_item))
            {
                utils::containers::gFindAndErase(m_bombs, p_item);
                m_pContainer->removeItem(p_item);
            }
        }
    }

    void CGameStateInGame::checkCollisionsWithPlayer()
    {
        assert(m_pGameArea && m_pPlayer);

        utils::interfaces::IGraphicItem::TGraphicItems collidingitems =
            m_pGameArea->collidingItems(m_pPlayer,
                                        utils::interfaces::IGraphicItem::collision_mode::intersect);

        auto it_end = collidingitems.end();
        for (auto it = collidingitems.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_item = (*it);

            if (isAlien(p_item))
            {
                // Aliens vector simulates a bydimentional array of type aliens[ROWS][COLUMNS] so
                // the size is kept unchanged to retrieves aliens position at wish
                utils::containers::gFindAndReplace(m_aliens,
                                                   p_item,
                                                   (utils::interfaces::IGraphicItem *)nullptr);
                delete p_item;
            }
            else if (isBomb(p_item))
            {
                utils::containers::gFindAndErase(m_bombs, p_item);
                delete p_item;
            }

            g_env->pGame->onEvent(
                utils::interfaces::SGameEvent(CGame::gameevent_health, VAR_HEALTH_DAMAGE_VALUE));
        }
    }

    void CGameStateInGame::checkCollisionsWithRockets()
    {
        assert(m_pGameArea);

        auto it_rocket_end = m_rockets.end();
        for (auto it_rocket = m_rockets.begin(); it_rocket != it_rocket_end; ++it_rocket)
        {
            utils::interfaces::IGraphicItem * p_rocket = (*it_rocket);
            utils::interfaces::IGraphicItem::TGraphicItems collidingitems =
                m_pGameArea
                    ->collidingItems(p_rocket,
                                     utils::interfaces::IGraphicItem::collision_mode::intersect);

            if (collidingitems.empty())
            {
                continue;
            }

            // Forcing rocket to collide with maximum 1 alien :))
            utils::interfaces::IGraphicItem * p_item = collidingitems.at(0);

            if (isAlien(p_item))
            {
                utils::containers::gFindAndReplace(m_aliens,
                                                   p_item,
                                                   (utils::interfaces::IGraphicItem *)nullptr);
                delete p_item;

                (*it_rocket) = nullptr;
                delete p_rocket;

                g_env->pGame->onEvent(
                    utils::interfaces::SGameEvent(CGame::gameevent_score, VAR_KILL_SCORE_VALUE));
            }
            else if (isSuperAlien(p_item))
            {
                delete m_pSuperAlien;
                m_pSuperAlien = nullptr;

                (*it_rocket) = nullptr;
                delete p_rocket;

                g_env->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_score,
                                                                   VAR_KILL_SCORE_SPECIAL_VALUE));
            }
        }

        utils::containers::gFindAndEraseAll(m_rockets, (utils::interfaces::IGraphicItem *)nullptr);
    }

    void CGameStateInGame::checkVictoryConditions()
    {
        if (aliveAliens().empty())
        {
            g_env->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_exit, 1));
        }

        if (static_cast<CGame *>(g_env->pGame)->lifes() <= 0)
        {
            g_env->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_exit, 0));
        }

        if (isAnyAlienBypassed())
        {
            g_env->pGame->onEvent(utils::interfaces::SGameEvent(CGame::gameevent_exit, 0));
        }
    }

    void CGameStateInGame::moveAliens(float deltaTime)
    {
        const float move = deltaTime * (VAR_ALIEN_SPEED_VALUE + m_difficulty);

        auto it_end = m_aliens.end();
        for (auto it = m_aliens.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_alien = (*it);
            if (p_alien == nullptr)
            {
                continue;
            }

            utils::CPoint pos = p_alien->position();
            if (m_aliensMoveDown)
            {
                pos.ry() += CGame::picture_alien_2.size().height();
                pos.rx() += m_aliensMoveLeft
                                ? -1
                                : 1; // Makes sure aliens do not collide with borders on next frame
            }
            else
            {
                pos.rx() += m_aliensMoveLeft ? -move : move;
            }
            p_alien->setPosition(pos);
        }

        if (m_aliensMoveDown)
        {
            m_difficulty += difficuly_mult;
            m_aliensMoveDown = false;
        }

        if (m_pSuperAlien != nullptr)
        {
            utils::CPoint pos = m_pSuperAlien->position();
            pos.rx() += move;
            m_pSuperAlien->setPosition(pos);
        }
    }

    void CGameStateInGame::moveRockets(float deltaTime)
    {
        const float move = deltaTime * VAR_ROCKET_SPEED_VALUE;

        auto it_end = m_rockets.end();
        for (auto it = m_rockets.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_rocket = (*it);

            utils::CPoint pos = p_rocket->position();
            pos.ry() -= move;
            p_rocket->setPosition(pos);
        }
    }

    void CGameStateInGame::moveBombs(float deltaTime)
    {
        const float move = deltaTime * VAR_BOMB_SPEED_VALUE;

        auto it_end = m_bombs.end();
        for (auto it = m_bombs.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_bomb = (*it);

            utils::CPoint pos = p_bomb->position();
            pos.ry() += move;
            p_bomb->setPosition(pos);
        }
    }

    void CGameStateInGame::spawnBombs()
    {
        assert(m_pGameArea);

        if (m_bombs.size() >= VAR_BOMB_MAX_ON_SCREEN_VALUE)
        {
            return;
        }

        utils::interfaces::IGraphicItem::TGraphicItems aliens = freeAliens();
        const size_t alien_size = aliens.size();

        if (aliens.empty())
        {
            return;
        }

        int random_alien = g_env->pFramework->random(alien_size);
        utils::interfaces::IGraphicItem * p_alien = aliens.at(random_alien);

        if (g_env->pFramework->random(500) >= VAR_BOMB_PROBABILITY_VALUE * 5)
        {
            return;
        }

        utils::interfaces::IGraphicBitmap * p_bomb = m_pGameArea->addBitmap(CGame::picture_bomb);
        m_bombs.push_back(p_bomb);

        utils::CPoint pos = p_alien->position();
        pos.ry() += p_alien->size().height();
        p_bomb->setPosition(pos);
    }

    void CGameStateInGame::spawnAliens()
    {
        // For now takes care to spawn superAlien only

        assert(m_pGameArea);

        if (m_pSuperAlien != nullptr)
        {
            return;
        }

        if (g_env->pFramework->random(2500) != 1)
        {
            return;
        }

        // Verifies if there is any alien in the top row where the superAlien is spawned
        if (!m_pGameArea
                 ->collidingItems(utils::CRectangle(0,
                                                    0,
                                                    m_pGameArea->size().width(),
                                                    CGame::picture_alien_2.size().height()),
                                  utils::interfaces::IGraphicItem::collision_mode::intersect)
                 .empty())
        {
            return;
        }

        m_pSuperAlien = m_pGameArea->addBitmap(CGame::picture_alien_1);
    }

    void CGameStateInGame::updateScore()
    {
        assert(m_pScoreTextField);
        m_pScoreTextField->setText("SCORE: %d", static_cast<CGame *>(g_env->pGame)->score());
    }

    void CGameStateInGame::updateHealth()
    {
        assert(m_pHealthTextField);
        m_pHealthTextField->setText("HEALTH: %d", static_cast<CGame *>(g_env->pGame)->lifes());
    }

    bool CGameStateInGame::isSuperAlien(utils::interfaces::IGraphicItem * pItem) const
    {
        return pItem == m_pSuperAlien;
    }

    bool CGameStateInGame::isPlayer(utils::interfaces::IGraphicItem * pItem) const
    {
        return pItem == m_pPlayer;
    }

    utils::interfaces::IGraphicItem::TGraphicItems CGameStateInGame::aliveAliens() const
    {
        utils::interfaces::IGraphicItem::TGraphicItems aliens;

        auto it_end = m_aliens.end();
        for (auto it = m_aliens.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_alien = (*it);
            if (p_alien != nullptr)
            {
                aliens.push_back(p_alien);
            }
        }

        return aliens;
    }

    bool CGameStateInGame::isAnyAlienBypassed() const
    {
        auto it_end = m_aliens.end();
        for (auto it = m_aliens.begin(); it != it_end; ++it)
        {
            utils::interfaces::IGraphicItem * p_alien = (*it);
            if ((p_alien != nullptr) && p_alien->position().y() > m_pPlayer->position().y())
            {
                return true;
            }
        }

        return false;
    }

    utils::interfaces::IGraphicItem::TGraphicItems CGameStateInGame::freeAliens() const
    {
        utils::interfaces::IGraphicItem::TGraphicItems aliens;

        // From "bottom" to "top" retrieves the aliens able to shoot
        for (int column = 0; column < VAR_ALIEN_COLUMNS_VALUE; ++column)
        {
            utils::interfaces::IGraphicItem * p_alien = nullptr;

            for (int row = VAR_ALIEN_ROWS_VALUE - 1; row >= 0; --row)
            {
                p_alien = m_aliens.at(row + (column * VAR_ALIEN_ROWS_VALUE));
                if (p_alien != nullptr)
                {
                    break;
                }
            }

            if (p_alien != nullptr)
            {
                aliens.push_back(p_alien);
                continue;
            }
        }

        return aliens;
    }

} // namespace game
