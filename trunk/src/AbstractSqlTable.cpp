/*
 * ./AbstractSqlTable.cpp
 * Copyright (C) 2010 Lameire Alexis
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "AbstractSqlTable.h"
#include "LevelTable.h"
#include "SubjectTable.h"
///
/// \file AbstractSqlTable.cpp
/// \brief implement acesser and constructor of AbstractSqlTable
/// \author Lameire Alexis
///

AbstractSqlTable::AbstractSqlTable() : m_is_exist(false)
{
}

bool AbstractSqlTable::is_exist() const
{
        return m_is_exist;
}

void AbstractSqlTable::set_is_exist(bool is_exist)
{
        m_is_exist = is_exist;
}

AbstractSqlTable* AbstractSqlTable::create_element_from_type(Subtype type)
{
        switch (type)
        {
                case LevelTable_class:
                        return new LevelTable;
                        break;
                case SubjectTable_class:
                        return new SubjectTable;
                        break;
                default:
                        throw;
                        break;
        }
}
