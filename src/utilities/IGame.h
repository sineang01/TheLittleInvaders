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

namespace utils {
	namespace interfaces {

		struct IFramework;
		struct SSystemGlobalEnvironment;

		struct SGameEvent
		{
			unsigned int eventType;
			int eventValue;

			SGameEvent(unsigned int _eventType) :eventType(_eventType), eventValue(0) {}
			SGameEvent(unsigned int _eventType, int _eventValue) :eventType(_eventType), eventValue(_eventValue) {}

		private:
			SGameEvent() {}
		};

		struct IGame
		{
			typedef IGame *(*TEntryFunctionCreate)(SSystemGlobalEnvironment*);
			typedef void(*TEntryFunctionDestroy)();

			virtual bool init() = 0;
			virtual bool refresh() = 0;

			virtual void onEvent(SGameEvent e) = 0;
		};

	} // namespace interfaces
} // namespace utils
