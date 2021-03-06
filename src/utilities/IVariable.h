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
#include <string>

namespace utils {
	namespace interfaces {

		struct IVariable
		{
			template<typename T>
			T setValue(T value, bool * ok = nullptr) const
			{
				if (ok) *ok = false;

				CVariable<T> * pCVar = dynamic_cast<CVariable<T> *>(this);
				if (!pCVar) return;

				if (ok) *ok = true;
				pCVar->setValueInternal(value);
			}

			template<typename T>
			T value(bool * ok = nullptr) const
			{
				if (ok) *ok = false;

				const CVariable<T> * pCVar = dynamic_cast<const CVariable<T> *>(this);
				if (!pCVar) return T();

				if (ok) *ok = true;
				return pCVar->valueInternal();
			}

			virtual ~IVariable() {}
		};

		template <class T>
		class CVariable : public IVariable
		{
		public:
			CVariable() = default;
			inline CVariable(const char * value);
			CVariable(T value) :m_value(value) {}

			inline void setValueInternal(T value) { m_value = value; }
			inline T valueInternal() const { return m_value; }

		private:
			T m_value;
		};

		template<>
		inline CVariable<bool>::CVariable(const char * value)
		{
			m_value = strcmp(value, "false") == 0 ? false : true;
		}

		template<>
		inline CVariable<unsigned int>::CVariable(const char * value)
		{
			m_value = (unsigned int)std::strtoul(value, nullptr, 0);
		}

		template<>
		inline CVariable<int>::CVariable(const char * value)
		{
			m_value = atoi(value);
		}

		template<>
		inline CVariable<float>::CVariable(const char * value)
		{
			m_value = (float)atof(value);
		}

		template<>
		inline CVariable<double>::CVariable(const char * value)
		{
			m_value = atof(value);
		}

		template<>
		inline CVariable<std::string>::CVariable(const char * value)
		{
			m_value = value;
		}

	} // namespace interfaces
} // namespace utils
