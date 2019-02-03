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
#include "IFramework.h"

namespace utils {

	struct IGameTimerListener
	{
		virtual void timeout() = 0;
	};

	class CGameTimer final : public CBaseListenerHandler<IGameTimerListener>, public interfaces::IFrameworkListener
	{
	public:
		CGameTimer(float interval = 0);
		~CGameTimer() { stop(); }
		CGameTimer(const CGameTimer &) = delete;
		CGameTimer &operator=(const CGameTimer &) = delete;

		inline float interval() const noexcept { return m_interval; }
		inline void setInterval(float interval) noexcept;

		inline bool isActive() const noexcept { return m_active; }

		inline bool isElapsed() const noexcept { return m_elapsedTime >= m_interval; }
		inline float elapsed() const noexcept { return m_elapsedTime; }

		void start();
		void stop();

	protected:
		// IGameTimerListener
		void timeout();
		// ~IGameTimerListener

	private:
		// IFrameworkListener
		void onUpdate(float deltaTime);
		void onInput(interfaces::CInputKey get_key, float deltaTime) {};
		// ~IFrameworkListener

		inline void reset() noexcept { m_elapsedTime = 0.0f; }

	private:
		float m_interval{ 0.0f };
		float m_elapsedTime{ 0.0f };
		bool m_active{ false };
	};

	void CGameTimer::setInterval(float interval) noexcept
	{
		m_interval = interval;
		reset();
	}

} // namespace utils
