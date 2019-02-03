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

#include "VariablesManager.h"
#include <CSVReader.h>
#include <algorithm>
#include <cassert>
#include <iostream>

namespace engine {

	static const int VARIABLE_CSV_CELLS = 3;
	static const char * VARIABLE_TYPE_BOOL = "boolean";
	static const char * VARIABLE_TYPE_UINT = "uint";
	static const char * VARIABLE_TYPE_INT = "int";
	static const char * VARIABLE_TYPE_FLOAT = "float";
	static const char * VARIABLE_TYPE_DOUBLE = "double";
	static const char * VARIABLE_TYPE_STRING = "string";

	CVariablesManager::CVariablesManager()
	{
	}

	CVariablesManager::~CVariablesManager()
	{
		if (m_variables.empty())
			return;

		for (auto it = m_variables.begin(); it != m_variables.end(); ++it)
		{
			delete it->second;
		}

		m_variables.clear();
	}

	bool CVariablesManager::loadConfig(const char * filePath)
	{
		assert(filePath && filePath[0]);

		utils::CCSVReader cvsReader(filePath);
		utils::CCSVReader::TContent csvContent;
		if (!cvsReader.readAll(csvContent))
			return false;

		const size_t size = csvContent.size();
		for (size_t line = 0; line < size; ++line)
		{
			const utils::CCSVReader::TRow & csvRow = csvContent[line];

			if (csvRow.size() != 3)
			{
				std::cerr << "[ERROR] Variable at line " << line << " doesn't have " << VARIABLE_CSV_CELLS << " elements" << std::endl;
				return false;
			}

			std::string name = csvRow[0];
			if (name.empty())
			{
				std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid name" << std::endl;
				return false;
			}

			name = getLower(name.c_str());
			const char * name_s = name.c_str();

			if (m_variables.find(name) != m_variables.end())
			{
				std::cerr << "[ERROR] Variable " << name_s << " at line " << line << " already exists" << std::endl;
				return nullptr;
			}

			std::string type = csvRow[1];
			if (type.empty())
			{
				std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid type" << std::endl;
				return false;
			}

			std::string value = csvRow[2];
			if (value.empty())
			{
				std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid value" << std::endl;
				return false;
			}

			const char * value_s = value.c_str();

			if (type.compare(VARIABLE_TYPE_BOOL) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<bool>(value_s)));
			else if (type.compare(VARIABLE_TYPE_UINT) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<unsigned int>(value_s)));
			else if (type.compare(VARIABLE_TYPE_INT) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<int>(value_s)));
			else if (type.compare(VARIABLE_TYPE_FLOAT) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<float>(value_s)));
			else if (type.compare(VARIABLE_TYPE_DOUBLE) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<double>(value_s)));
			else if (type.compare(VARIABLE_TYPE_STRING) == 0)
				m_variables.insert(TVariableMapPair(name, new utils::interfaces::CVariable<std::string>(value_s)));
			else
			{
				std::cerr << "[ERROR] Variable " << name_s << " at line " << line << " doesn't use any allowed type" << std::endl;
				return false;
			}
		}

		return true;
	}

	utils::interfaces::IVariable * CVariablesManager::variable(const char * name) const
	{
		std::string nameStr = getLower(name);

		auto it = m_variables.find(nameStr);
		if (it == m_variables.end())
			return nullptr;

		return it->second;
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, unsigned int defaultValue)
	{
		return registerVariable<unsigned int>(name, defaultValue);
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, int defaultValue)
	{
		return registerVariable<int>(name, defaultValue);
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, float defaultValue)
	{
		return registerVariable<float>(name, defaultValue);
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, double defaultValue)
	{
		return registerVariable<double>(name, defaultValue);
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, bool defaultValue)
	{
		return registerVariable<bool>(name, defaultValue);
	}

	utils::interfaces::IVariable * CVariablesManager::registerVariable(const char * name, std::string defaultValue)
	{
		return registerVariable<std::string>(name, defaultValue);
	}

	std::string CVariablesManager::getLower(const char * value) const
	{
		if (!value && !value[0])
			return std::string("");

		std::string valueStr(value);
		std::transform(valueStr.begin(), valueStr.end(), valueStr.begin(), ::tolower);

		return valueStr;
	}

} // namespace engine
