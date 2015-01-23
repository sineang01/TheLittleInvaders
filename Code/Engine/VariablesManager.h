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

#ifndef VARIABLESMANAGER_H
#define VARIABLESMANAGER_H

#include <vector>
#include <map>
#include <IVariablesManager.h>

class CVariablesManager : public IVariablesManager
{
	public:
		CVariablesManager();
		~CVariablesManager();

	public:
		// IVariablesManager
		bool loadConfig(const char * filePath);

		IVariable * variable(const char * name) const;

		IVariable * registerVariable(const char * name, unsigned int defaultValue);
		IVariable * registerVariable(const char * name, int defaultValue);
		IVariable * registerVariable(const char * name, float defaultValue);
		IVariable * registerVariable(const char * name, double defaultValue);
		IVariable * registerVariable(const char * name, bool defaultValue);
		IVariable * registerVariable(const char * name, std::string defaultValue);
		// ~IVariablesManager

	private:
		std::string getLower(const char * value) const;

		template <typename T>
		IVariable * registerVariable(const char * name, T defaultValue)
		{
			std::string nameStr = getLower(name);

			if (gMemberFind(m_variables, nameStr))
				return NULL;

			IVariable * pVariable = new CVariable<T>(defaultValue);
			m_variables.insert(TVariableMapPair(nameStr, pVariable));
			return pVariable;
		}

	private:
		typedef std::map<std::string, IVariable *> TVariables;
		typedef std::pair<std::string, IVariable *> TVariableMapPair;
		TVariables m_variables;
};

#endif // VARIABLESMANAGER_H