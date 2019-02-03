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

namespace utils {
	namespace interfaces {
		struct ISprite;
	}
}

namespace engine {

	class CVariablesManager;

	namespace graphic {
		class CGraphicContainer;
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
		bool init() override;
		int exec() override;
		utils::interfaces::IGraphicContainer * window() const override;
		inline float elapsedTime() const override { return m_time; }
		inline unsigned int random(size_t maxValue) const override { return rand() % maxValue; }
		inline const char * applicationPath() const override { return m_applicationPath.c_str(); }
		utils::interfaces::IVariablesManager * variablesManager() const override;
		// ~IFramework

	protected:
		// IFrameworkListener
		void onUpdate(float deltaTime) override;
		void onInput(utils::interfaces::CInputKey get_key, float deltaTime) override;
		// ~IFrameworkListener

	private:
		void spriteDeferredDestruction();
		void makeApplicationPath();

		bool initVariables();

	private:
		utils::interfaces::IPlatformManager * m_pPlatformManager{ nullptr };
		graphic::CGraphicContainer * m_pWindow{ nullptr };
		CVariablesManager * m_pVariablesManager{ nullptr };

		typedef std::vector<utils::interfaces::ISprite *> TSprites;
		TSprites m_sprites;

		float m_time{ 0.0f };

		utils::interfaces::CInputKey m_keyFire{ utils::interfaces::CInputKey::key::fire };
		utils::interfaces::CInputKey m_keyLeft{ utils::interfaces::CInputKey::key::left };
		utils::interfaces::CInputKey m_keyRight{ utils::interfaces::CInputKey::key::right };

		std::string m_applicationPath;
	};

} // namespace engine
