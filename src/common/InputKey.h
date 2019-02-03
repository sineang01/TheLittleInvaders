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

		/**
		 * @brief The CInputKey struct is an helper for the key handling
		 */
		class CInputKey
		{
		public:
			enum class key
			{
				fire = 0,
				left,
				right,
			};

			enum class key_status
			{
				inactive = 0,
				press,
				on_hold
			};

			inline key get_key() const noexcept { return m_key; }

			inline key_status get_status() const noexcept { return m_status; }
			inline void set_status(key_status s) noexcept { m_status = s; }

		public:
			CInputKey() = delete;
			CInputKey(key _key) :m_key(_key) {}
			CInputKey(key _key, key_status _status) :m_key(_key), m_status(_status) {}

		private:
			key m_key;
			key_status m_status{ key_status::inactive };
		};

	} // namespace interfaces
} // namespace utils
