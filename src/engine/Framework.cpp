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

#include "Framework.h"
#include "GraphicContainer.h"
#include "LibraryHandler.h"
#include "PlatformFactory.h"
#include "VariablesManager.h"
#include <ContainersUtils.h>
#include <Path.h>
#include <cassert>
#include <ctime>
#include <iostream>

#include "ISystemGlobalEnvironment.h"
extern utils::interfaces::SSystemGlobalEnvironment * g_env;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

namespace engine {

    static const char * game_library_name = "Game.dll";
    static const char * game_library_entry_point_create = "create_game";
    static const char * game_library_entry_point_destroy = "destroy_game";

    CFramework::CFramework() { makeApplicationPath(); }

    CFramework::~CFramework()
    {
        spriteDeferredDestruction();
        delete m_pPlatformManager;
        delete m_pVariablesManager;
    }

    void CFramework::makeApplicationPath()
    {
        char buffer[MAX_PATH];
        GetModuleFileName(nullptr, buffer, MAX_PATH);

        std::string buffer_string(buffer);
        std::string::size_type pos = buffer_string.find_last_of("\\/");
        m_applicationPath = buffer_string.substr(0, pos + 1);
    }

    bool CFramework::init()
    {
        srand((unsigned int)time(nullptr));

        if (!initVariables())
        {
            return false;
        }

        m_pPlatformManager = platform::CPlatformFactory::make(
            m_pVariablesManager->variable("sys_platform")->value<std::string>().c_str());
        if (m_pPlatformManager == nullptr)
        {
            std::cerr << "[ERROR] Platform manager cannot be initialized" << std::endl;
            return false;
        }

        utils::interfaces::IPlatform * p_platform = m_pPlatformManager->platform();
        if (p_platform == nullptr)
        {
            std::cerr << "[ERROR] Platform cannot be retrieved" << std::endl;
            return false;
        }

        const int width = m_pVariablesManager->variable("sys_width")->value<unsigned int>();
        const int height = m_pVariablesManager->variable("sys_height")->value<unsigned int>();
        if (!p_platform->init(width, height))
        {
            std::cerr << "[ERROR] Platform cannot initialize" << std::endl;
            return false;
        }

        m_pWindow = new graphic::CGraphicContainer();
        m_pWindow->setSize(width, height);

        return true;
    }

    int CFramework::exec()
    {
        if (m_pPlatformManager == nullptr)
        {
            std::cerr << "[ERROR] Platform manager not initialized" << std::endl;
            return -1;
        }

        utils::interfaces::IPlatform * p_platform = m_pPlatformManager->platform();
        if (p_platform == nullptr)
        {
            std::cerr << "[ERROR] Platform not initialized" << std::endl;
            return -1;
        }

        utils::CLibraryHandler game_dll(game_library_name);
        if (!game_dll.init())
        {
            return -1;
        }

        auto create_game = (utils::interfaces::IGame::TEntryFunctionCreate)
            GetProcAddress(game_dll.libraryHandler(), game_library_entry_point_create);
        if (create_game == nullptr)
        {
            std::cerr << "[ERROR] Specified " << game_dll.libraryName() << " doesn't have a valid "
                      << game_library_entry_point_create << " entry point" << std::endl;

            return -1;
        }

        utils::interfaces::IGame * p_game = create_game(g_env);
        if (p_game == nullptr)
        {
            std::cerr << "[ERROR] Failed to create the game interface" << std::endl;
            return -1;
        }

        if (!p_game->init())
        {
            std::cerr << "[ERROR] Game not initialized" << std::endl;
            return -1;
        }

        while (p_platform->update())
        {
            float time = p_platform->getElapsedTime();
            float delta = time - m_time;

            m_pWindow->paint();

            onUpdate(delta);

            utils::interfaces::IPlatform::key_status keys;
            p_platform->getKeyStatus(keys);

            m_keyFire.set_status(
                keys.fire
                    ? (m_keyFire.get_status() == utils::interfaces::CInputKey::key_status::inactive
                           ? utils::interfaces::CInputKey::key_status::press
                           : utils::interfaces::CInputKey::key_status::on_hold)
                    : utils::interfaces::CInputKey::key_status::inactive);
            onInput(m_keyFire, delta);

            m_keyLeft.set_status(
                keys.left
                    ? (m_keyLeft.get_status() == utils::interfaces::CInputKey::key_status::inactive
                           ? utils::interfaces::CInputKey::key_status::press
                           : utils::interfaces::CInputKey::key_status::on_hold)
                    : utils::interfaces::CInputKey::key_status::inactive);
            onInput(m_keyLeft, delta);

            m_keyRight.set_status(
                keys.right
                    ? (m_keyRight.get_status() == utils::interfaces::CInputKey::key_status::inactive
                           ? utils::interfaces::CInputKey::key_status::press
                           : utils::interfaces::CInputKey::key_status::on_hold)
                    : utils::interfaces::CInputKey::key_status::inactive);
            onInput(m_keyRight, delta);

            if (!p_game->refresh())
            {
                std::cerr << "[ERROR] Game can't refresh" << std::endl;
                break;
            }

            m_time = time;
        }

        spriteDeferredDestruction();
        p_platform->destroy();

        auto destroy_game = (utils::interfaces::IGame::TEntryFunctionDestroy)
            GetProcAddress(game_dll.libraryHandler(), game_library_entry_point_destroy);
        if (destroy_game == nullptr)
        {
            std::cerr << "[ERROR] Specified " << game_dll.libraryName() << " doesn't have a valid "
                      << game_library_entry_point_destroy << " entry point" << std::endl;

            return -1;
        }

        destroy_game();

        return 0;
    }

    utils::interfaces::IPlatformManager * CFramework::platformManager()
    {
        return m_pPlatformManager;
    }

    utils::interfaces::IPlatform * CFramework::platform()
    {
        if (m_pPlatformManager == nullptr)
        {
            return nullptr;
        }

        return m_pPlatformManager->platform();
    }

    utils::interfaces::IGraphicContainer * CFramework::window() const { return m_pWindow; }

    void CFramework::destroySprite(utils::interfaces::ISprite * pSprite)
    {
        assert(pSprite);
        utils::containers::gPushBackUnique(m_sprites, pSprite);
    }

    utils::interfaces::IVariablesManager * CFramework::variablesManager() const
    {
        return m_pVariablesManager;
    }

    void CFramework::spriteDeferredDestruction()
    {
        auto it_end = m_sprites.end();
        for (auto it = m_sprites.begin(); it != it_end; ++it)
        {
            (*it)->destroy();
        }

        m_sprites.clear();
    }

    void CFramework::onUpdate(float deltaTime)
    {
        for (auto & m_listener : m_listeners)
        {
            m_listener->onUpdate(deltaTime);
        }
    }

    void CFramework::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
    {
        for (auto & m_listener : m_listeners)
        {
            m_listener->onInput(get_key, deltaTime);
        }
    }

    bool CFramework::initVariables()
    {
        m_pVariablesManager = new CVariablesManager();

        std::string system_file = utils::path_utils::executablePath() + "\\system.csv";
        if (!m_pVariablesManager->loadConfig(system_file.c_str()))
        {
            std::cerr << "[ERROR] Variables manager cannot load file " << system_file.c_str()
                      << std::endl;
            return false;
        }

        std::string variables_file = utils::path_utils::executablePath() + "\\variables.csv";
        if (!m_pVariablesManager->loadConfig(variables_file.c_str()))
        {
            std::cerr << "[ERROR] Variables manager cannot load file " << variables_file.c_str()
                      << std::endl;
            return false;
        }

        return true;
    }

} // namespace engine
