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

    static const int variable_csv_cells = 3;
    static const char * variable_type_bool = "boolean";
    static const char * variable_type_uint = "uint";
    static const char * variable_type_int = "int";
    static const char * variable_type_float = "float";
    static const char * variable_type_double = "double";
    static const char * variable_type_string = "string";

    CVariablesManager::~CVariablesManager()
    {
        if (m_variables.empty())
        {
            return;
        }

        for (auto it = m_variables.begin(); it != m_variables.end(); ++it)
        {
            delete it->second;
        }

        m_variables.clear();
    }

    bool CVariablesManager::loadConfig(const char * filePath)
    {
        assert(filePath && filePath[0]);

        utils::CCSVReader cvs_reader(filePath);
        utils::CCSVReader::TContent csv_content;
        if (!cvs_reader.readAll(csv_content))
        {
            return false;
        }

        const size_t size = csv_content.size();
        for (size_t line = 0; line < size; ++line)
        {
            const utils::CCSVReader::TRow & csv_row = csv_content[line];

            if (csv_row.size() != 3)
            {
                std::cerr << "[ERROR] Variable at line " << line << " doesn't have "
                          << variable_csv_cells << " elements" << std::endl;
                return false;
            }

            std::string name = csv_row[0];
            if (name.empty())
            {
                std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid name"
                          << std::endl;
                return false;
            }

            name = getLower(name.c_str());
            const char * name_s = name.c_str();

            if (m_variables.find(name) != m_variables.end())
            {
                std::cerr << "[ERROR] Variable " << name_s << " at line " << line
                          << " already exists" << std::endl;
                return false;
            }

            std::string type = csv_row[1];
            if (type.empty())
            {
                std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid type"
                          << std::endl;
                return false;
            }

            std::string value = csv_row[2];
            if (value.empty())
            {
                std::cerr << "[ERROR] Variable at line " << line << " doesn't have a valid value"
                          << std::endl;
                return false;
            }

            const char * value_s = value.c_str();

            if (type == variable_type_bool)
            {
                m_variables.insert(
                    TVariableMapPair(name, new utils::interfaces::CVariable<bool>(value_s)));
            }
            else if (type == variable_type_uint)
            {
                m_variables.insert(
                    TVariableMapPair(name,
                                     new utils::interfaces::CVariable<unsigned int>(value_s)));
            }
            else if (type == variable_type_int)
            {
                m_variables.insert(
                    TVariableMapPair(name, new utils::interfaces::CVariable<int>(value_s)));
            }
            else if (type == variable_type_float)
            {
                m_variables.insert(
                    TVariableMapPair(name, new utils::interfaces::CVariable<float>(value_s)));
            }
            else if (type == variable_type_double)
            {
                m_variables.insert(
                    TVariableMapPair(name, new utils::interfaces::CVariable<double>(value_s)));
            }
            else if (type == variable_type_string)
            {
                m_variables.insert(
                    TVariableMapPair(name, new utils::interfaces::CVariable<std::string>(value_s)));
            }
            else
            {
                std::cerr << "[ERROR] Variable " << name_s << " at line " << line
                          << " doesn't use any allowed type" << std::endl;
                return false;
            }
        }

        return true;
    }

    utils::interfaces::IVariable * CVariablesManager::variable(const char * name) const
    {
        std::string name_str = getLower(name);

        auto it = m_variables.find(name_str);
        if (it == m_variables.end())
        {
            return nullptr;
        }

        return it->second;
    }

    std::string CVariablesManager::getLower(const char * value) const
    {
        if ((value == nullptr) || (value[0] == 0))
        {
            return std::string("");
        }

        std::string value_str(value);
        std::transform(value_str.begin(), value_str.end(), value_str.begin(), ::tolower);

        return value_str;
    }

} // namespace engine
