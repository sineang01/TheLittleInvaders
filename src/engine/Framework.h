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
#include <IFramework.h>
#include <IGame.h>
#include <IPlatform.h>
#include <IPlatformManager.h>

class CGraphicContainer;
class CVariablesManager;

namespace utils {
	namespace interfaces {
		struct ISprite;
	}
}

class CFramework final : public utils::interfaces::IFramework
{
public:
	CFramework();
	~CFramework();
	CFramework(const CFramework &) = delete;
	CFramework &operator=(const CFramework &) = delete;

	/**
	* @brief Retrieves the platform manager
	*/
	utils::interfaces::IPlatformManager * platformManager();

	/**
	* @brief Retreives the current platform instancated
	*/
	utils::interfaces::IPlatform * platform();

	/**
	* @brief Schedules a sprite to be destroyed
	*/
	void destroySprite(utils::interfaces::ISprite * pSprite);

public:
	// IFramework
	bool init();
	int exec();
	float elapsedTime() const;
	utils::interfaces::IGraphicContainer * window() const;
	unsigned int random(size_t maxValue) const;
	const char * applicationPath() const;
	utils::interfaces::IVariablesManager * variablesManager() const;
	// ~IFramework

protected:
	// IFrameworkListener
	void onUpdate(float deltaTime);
	void onInput(utils::interfaces::CInputKey get_key, float deltaTime);
	// ~IFrameworkListener

private:
	void spriteDeferredDestruction();
	void makeApplicationPath();

	bool initVariables();

private:
	utils::interfaces::IPlatformManager * m_pPlatformManager;
	CGraphicContainer * m_pWindow;
	CVariablesManager * m_pVariablesManager;

	typedef std::vector<utils::interfaces::ISprite *> TSprites;
	TSprites m_sprites;

	float m_time;

	utils::interfaces::CInputKey m_keyFire;
	utils::interfaces::CInputKey m_keyLeft;
	utils::interfaces::CInputKey m_keyRight;

	std::string m_applicationPath;
};
