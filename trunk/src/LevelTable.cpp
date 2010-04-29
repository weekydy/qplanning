/*
 * ./LevelTable.cpp
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
///
/// \file LevelTable.cpp
/// \brief implemente the LevelTable methods
/// \author Lameire Alexis
///
#include "LevelTable.h"

LevelTable::LevelTable() : AbstractSqlTable(), m_id(0), m_name("")
{
        set_is_exist(false);
}

LevelTable::LevelTable(AdvencedKeyValue data) : AbstractSqlTable(), m_id(data.key), m_name(data.value)
{
        set_is_exist(data.is_exist);
}

QString LevelTable::add()
{
        if (is_valid())
        {
                QString query;
                QTextStream query_stream(&query);
                query_stream << "INSERT INTO level(name) VALUE('" << m_name << "')";
                query_stream << "SELECT id FROM level WHERE id=LAST_INSERTED_ROWID()";
                return query;
        }
        throw;
}

QString LevelTable::del()
{
        if (is_valid() && m_id != 0)
        {
                QString query;
                QTextStream query_stream(&query);
                query_stream << "DELETE FROM level WHERE id='" << m_id << "'";
                return query;
        }
        throw;
}

QString LevelTable::edit()
{
        if (!is_valid())
        {
                throw;
        }
        if (m_id == 0)
        {
                return add();
        }
        else
        {
                QString query;
                QTextStream query_stream(&query);
                query_stream << "UPDATE level SET name='" << m_name << "' WHERE id='" << m_id << "'";
                return query;
        }
}

bool LevelTable::is_valid()
{
        return m_name.isNull();
}

LevelTable& LevelTable::parse_statment(QSqlQuery& result) const
{
        LevelTable* data = new LevelTable;
        if (is_exist())
        {
                data->m_id = result.value(0).toUInt();
                data->m_name = result.value(1).toString();
                return *data;
        }
        else
        {
                data->m_id = result.value(0).toUInt();
                data->m_name = m_name;
                return *data;
        }
}
