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

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <IFramework.h>
#include <IGame.h>
#include <IPlatform.h>
#include <IPlatformManager.h>

class CGraphicContainer;
struct ISprite;
class CVariablesManager;

class CFramework : public IFramework
{
	public:
		CFramework();
		~CFramework();

        /**
         * @brief Retrieves the platform manager
         */
		IPlatformManager * platformManager();

        /**
         * @brief Retreives the current platform instancated
         */
		IPlatform * platform();

        /**
         * @brief Schedules a sprite to be destroyed
         */
		void destroySprite(ISprite * pSprite);

    public:
        // IFramework
		bool init();
		int exec();
        float elapsedTime() const;
		IGraphicContainer * window() const;
        unsigned int random(unsigned int maxValue) const;
		const char * applicationPath() const;
		IVariablesManager * variablesManager() const;
        // ~IFramework

	protected:
		// IFrameworkListener
		void onUpdate(float deltaTime);
		void onInput(CInputKey key, float deltaTime);
		// ~IFrameworkListener

	private:
		void spriteDeferredDestruction();
		void makeApplicationPath();

		bool initVariables();

	private:
		CFramework(const CFramework &);
		CFramework &operator=(const CFramework &);

	private:
		IPlatformManager * m_pPlatformManager;
		CGraphicContainer * m_pWindow;
		CVariablesManager * m_pVariablesManager;

		typedef std::vector<ISprite *> TSprites;
		TSprites m_sprites;

		float m_time;

		CInputKey m_keyFire;
		CInputKey m_keyLeft;
		CInputKey m_keyRight;

		std::string m_applicationPath;
};

#endif // FRAMEWORK_H
