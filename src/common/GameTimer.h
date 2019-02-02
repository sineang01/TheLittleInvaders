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

struct IGameTimerListener
{
	virtual void timeout() = 0;
};

class CGameTimer : public CBaseListenerHandler<IGameTimerListener>, public IFrameworkListener
{
	public:
		CGameTimer(float interval = 0);
		~CGameTimer();

		float interval() const;
		void setInterval(float interval);

		bool isActive() const;

		bool isElapsed() const;
		float elapsed() const;

		void start();
		void stop();

	protected:
		// IGameTimerListener
		void timeout();
		// ~IGameTimerListener

	private:
		// IFrameworkListener
		void onUpdate(float deltaTime);
		void onInput(CInputKey get_key, float deltaTime) {};
		// ~IFrameworkListener

		void reset();

	private:
		CGameTimer(const CGameTimer &);
		CGameTimer &operator=(const CGameTimer &);

	private:
		float m_interval;
		float m_elapsedTime;
		bool m_active;
};
