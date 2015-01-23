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

#ifndef BASELISTENERHANDLER_H
#define BASELISTENERHANDLER_H

#include <vector>

template <class T>
class CBaseListenerHandler : protected T
{
	public:
		bool addListener(T * pListener)
		{
			return gPushBackUnique(m_listeners, pListener);
		}

		bool removeListener(T * pListener)
		{
			return gFindAndErase(m_listeners, pListener);
		}

		CBaseListenerHandler() {}
		virtual ~CBaseListenerHandler() {}

	protected:
		typedef std::vector<T*> TListeners;
		TListeners m_listeners;
};

#endif // BASELISTENERHANDLER_H