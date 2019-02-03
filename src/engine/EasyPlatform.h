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
#include <IPlatform.h>
#include <IPlatformManager.h>
#include <LibraryHandler.h>

namespace engine {
	namespace platform {

		class CEasyPlatform final : public utils::interfaces::IPlatformManager, public utils::CLibraryHandler
		{
		public:
			CEasyPlatform();
			virtual ~CEasyPlatform();
			CEasyPlatform(const CEasyPlatform &) = delete;
			CEasyPlatform &operator=(const CEasyPlatform &) = delete;

			bool init();

			// IPlatformManager
			utils::interfaces::IPlatform* platform() const;
			// ~IPlatformManager

		private:
			utils::interfaces::IPlatform * m_interface;
		};

	} // namespace platform
} // namespace engine
