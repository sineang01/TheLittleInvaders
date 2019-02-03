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
extern utils::interfaces::SSystemGlobalEnvironment * gEnv;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include <windows.h>

static const char * GAME_LIBRARY_NAME = "Game.dll";
static const char * GAME_LIBRARY_ENTRY_POINT_CREATE = "CreateGame";
static const char * GAME_LIBRARY_ENTRY_POINT_DESTROY = "DestroyGame";

CFramework::CFramework():
	m_pPlatformManager(nullptr),
	m_pWindow(nullptr),
	m_pVariablesManager(nullptr),
	m_time(0.0f),
	m_keyFire(utils::interfaces::CInputKey::key::fire),
	m_keyLeft(utils::interfaces::CInputKey::key::left),
	m_keyRight(utils::interfaces::CInputKey::key::right)
{
	makeApplicationPath();
}

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

	std::string bufferString(buffer);
    std::string::size_type pos = bufferString.find_last_of( "\\/" );
	m_applicationPath = bufferString.substr(0, pos + 1);
}

bool CFramework::init()
{
	srand((unsigned int)time(nullptr));

	if (!initVariables())
		return false;

	m_pPlatformManager = CPlatformFactory::make(m_pVariablesManager->variable("sys_platform")->value<std::string>().c_str());
	if (!m_pPlatformManager)
	{
        std::cerr << "[ERROR] Platform manager cannot be initialized" << std::endl;
		return false;
	}

	utils::interfaces::IPlatform* pPlatform = m_pPlatformManager->platform();
	if (!pPlatform)
	{
        std::cerr << "[ERROR] Platform cannot be retrieved" << std::endl;
		return false;
	}

	const int width = m_pVariablesManager->variable("sys_width")->value<unsigned int>();
	const int height = m_pVariablesManager->variable("sys_height")->value<unsigned int>();
	if (!pPlatform->init(width, height))
	{
        std::cerr << "[ERROR] Platform cannot initialize" << std::endl;
		return false;
	}

	m_pWindow = new CGraphicContainer();
	m_pWindow->setSize(width, height);

	return true;
}

int CFramework::exec()
{
	if (!m_pPlatformManager)
	{
        std::cerr << "[ERROR] Platform manager not initialized" << std::endl;
		return -1;
	}

	utils::interfaces::IPlatform* pPlatform = m_pPlatformManager->platform();
	if (!pPlatform)
	{
        std::cerr << "[ERROR] Platform not initialized" << std::endl;
		return -1;
	}

	utils::CLibraryHandler gameDLL(GAME_LIBRARY_NAME);
	if (!gameDLL.init())
		return -1;

	utils::interfaces::IGame::TEntryFunctionCreate CreateGame = (utils::interfaces::IGame::TEntryFunctionCreate)GetProcAddress(gameDLL.libraryHandler(), GAME_LIBRARY_ENTRY_POINT_CREATE);
	if (!CreateGame)
	{
		std::cerr << "[ERROR] Specified " << gameDLL.libraryName() << " doesn't have a valid CreateGame entry point" << std::endl;
		return -1;
	}

	utils::interfaces::IGame * pGame = CreateGame(gEnv);
	if (!pGame)
	{
		std::cerr << "[ERROR] Failed to create the game interface" << std::endl;
		return -1;
	}

	if (!pGame->init())
	{
        std::cerr << "[ERROR] Game not initialized" << std::endl;
		return -1;
	}

	while (pPlatform->update())
	{
		float time = pPlatform->getElapsedTime();
		float delta = time - m_time;

		m_pWindow->paint();

		onUpdate(delta);
		
		utils::interfaces::IPlatform::key_status keys;
		pPlatform->getKeyStatus(keys);

		m_keyFire.set_status( keys.fire ? (m_keyFire.get_status() == utils::interfaces::CInputKey::key_status::inactive ? utils::interfaces::CInputKey::key_status::press : utils::interfaces::CInputKey::key_status::on_hold) : utils::interfaces::CInputKey::key_status::inactive );
		onInput(m_keyFire, delta);

		m_keyLeft.set_status( keys.left ? (m_keyLeft.get_status() == utils::interfaces::CInputKey::key_status::inactive ? utils::interfaces::CInputKey::key_status::press : utils::interfaces::CInputKey::key_status::on_hold) : utils::interfaces::CInputKey::key_status::inactive );
		onInput(m_keyLeft, delta);

		m_keyRight.set_status( keys.right ? (m_keyRight.get_status() == utils::interfaces::CInputKey::key_status::inactive ? utils::interfaces::CInputKey::key_status::press : utils::interfaces::CInputKey::key_status::on_hold) : utils::interfaces::CInputKey::key_status::inactive );
		onInput(m_keyRight, delta);

		if (!pGame->refresh())
		{
			std::cerr << "[ERROR] Game can't refresh" << std::endl;
			break;
		}

		m_time = time;
	}

	spriteDeferredDestruction();
	pPlatform->destroy();

	utils::interfaces::IGame::TEntryFunctionDestroy DestroyGame = (utils::interfaces::IGame::TEntryFunctionDestroy)GetProcAddress(gameDLL.libraryHandler(), GAME_LIBRARY_ENTRY_POINT_DESTROY);
	if (!DestroyGame)
	{
		std::cerr << "[ERROR] Specified " << gameDLL.libraryName() << " doesn't have a valid DestroyGame entry point" << std::endl;
		return -1;
	}

	DestroyGame();

	return 0;
}

utils::interfaces::IPlatformManager * CFramework::platformManager()
{
	return m_pPlatformManager;
}

utils::interfaces::IPlatform * CFramework::platform()
{
	if (!m_pPlatformManager)
		return nullptr;

	return m_pPlatformManager->platform();
}

float CFramework::elapsedTime() const
{
	return m_time;
}

utils::interfaces::IGraphicContainer * CFramework::window() const
{
	return m_pWindow;
}

unsigned int CFramework::random(size_t maxValue) const
{
	return rand() % maxValue;
}

void CFramework::destroySprite(utils::interfaces::ISprite * pSprite)
{
	assert(pSprite);
	utils::containers::gPushBackUnique(m_sprites, pSprite);
}

const char * CFramework::applicationPath() const
{
	return m_applicationPath.c_str();
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
	for(auto it = m_listeners.begin(), itEnd = m_listeners.end(); it != itEnd; ++it)
		(*it)->onUpdate(deltaTime);
}

void CFramework::onInput(utils::interfaces::CInputKey get_key, float deltaTime)
{
	for(auto it = m_listeners.begin(), itEnd = m_listeners.end(); it != itEnd; ++it)
		(*it)->onInput(get_key, deltaTime);
}

bool CFramework::initVariables()
{
	m_pVariablesManager = new CVariablesManager();

	std::string systemFile = utils::PathUtils::executablePath() + "\\system.csv";
	if (!m_pVariablesManager->loadConfig(systemFile.c_str()))
	{
        std::cerr << "[ERROR] Variables manager cannot load file " << systemFile.c_str() << std::endl;
		return false;
	}

	std::string variablesFile = utils::PathUtils::executablePath() + "\\variables.csv";
	if (!m_pVariablesManager->loadConfig(variablesFile.c_str()))
	{
        std::cerr << "[ERROR] Variables manager cannot load file " << variablesFile.c_str() << std::endl;
		return false;
	}

	return true;
}
