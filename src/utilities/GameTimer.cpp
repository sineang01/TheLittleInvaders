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

#include "GameTimer.h"
#include "ISystemGlobalEnvironment.h"

extern utils::interfaces::SSystemGlobalEnvironment * g_env;

namespace utils {

	CGameTimer::CGameTimer(float interval)
		:m_interval(interval)
	{
		reset();
	}

	void CGameTimer::onUpdate(float deltaTime)
	{
		if (!m_active) {
			return;
}

		m_elapsedTime += deltaTime;

		if (isElapsed()) {
			timeout();
}
	}

	void CGameTimer::start()
	{
		m_active = g_env->pFramework->addListener(this);
	}

	void CGameTimer::stop()
	{
		m_active = false;
		g_env->pFramework->removeListener(this);
	}

	void CGameTimer::timeout()
	{
		for (auto & m_listener : m_listeners) {
			m_listener->timeout();
}

		reset();
	}

} // namespace utils
