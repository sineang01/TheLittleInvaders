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

#include "stdafx.h"
#include "GameTimer.h"

CGameTimer::CGameTimer(float interval):
	m_interval(interval),
	m_elapsedTime(0.0f),
	m_active(false)
{
	reset();
}

CGameTimer::~CGameTimer()
{
	stop();
}

float CGameTimer::interval() const
{
	return m_interval;
}

void CGameTimer::setInterval(float interval)
{
	m_interval = interval;
	reset();
}

bool CGameTimer::isActive() const
{
	return m_active;
}

bool CGameTimer::isElapsed() const
{
	return m_elapsedTime >= m_interval;
}

float CGameTimer::elapsed() const
{
	return m_elapsedTime;
}

void CGameTimer::onUpdate(float deltaTime)
{
	if (!m_active)
		return;

	m_elapsedTime += deltaTime;

	if (isElapsed())
		timeout();
}

void CGameTimer::start()
{
	m_active = gEnv->pFramework->addListener(this);
}

void CGameTimer::stop()
{
	m_active = false;
	gEnv->pFramework->removeListener(this);
}

void CGameTimer::timeout()
{
	for(TListeners::iterator it = m_listeners.begin(), itEnd = m_listeners.end(); it != itEnd; ++it)
		(*it)->timeout();

	reset();
}

void CGameTimer::reset()
{
	m_elapsedTime = 0.0f;
}