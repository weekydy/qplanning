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

QVector<QSqlQuery*> LevelTable::add()
{
        debug_printf( Q_FUNC_INFO );
        if (is_valid())
        {
                QVector<QSqlQuery*> querys;
                bool error = true;
                querys.push_back(new QSqlQuery());
                error &= querys[0]->prepare("INSERT INTO level(name) VALUES(?);");
                querys[0]->bindValue(0, m_name);
                querys.push_back(new QSqlQuery());
                error &= querys[1]->prepare("SELECT id FROM level WHERE id=LAST_INSERT_ROWID();");

                debug_printf(qPrintable(querys[0]->lastQuery()));
                debug_printf(qPrintable(querys[1]->lastQuery()));
                if (!error)
                {
                        debug_printf("error in querry");
                        throw;
                }
                return querys;
        }
        throw;
}

QVector<QSqlQuery*> LevelTable::del()
{
        debug_printf( Q_FUNC_INFO );
        if (is_valid() && m_id != 0)
        {
                QVector<QSqlQuery*> query;
                query.push_back(new QSqlQuery);
                query[0]->prepare("DELETE FROM level WHERE id=:id");
                query[0]->bindValue(":id", m_id);
                return query;
        }
        throw;
}

QVector<QSqlQuery*> LevelTable::edit()
{
        if (!is_valid())
        {
                throw;
        }
        if (!is_exist())
        {
                return add();
        }
        else
        {
                QVector<QSqlQuery*> query;
                query.push_back(new QSqlQuery);
                query[0]->prepare("UPDATE level SET name=:name WHERE id=:id");
                query[0]->bindValue(":id", m_id);
                query[0]->bindValue(":name", m_name);
                return query;
        }
}

bool LevelTable::is_valid()
{
        return !m_name.isNull();
}

LevelTable* LevelTable::parse_statment(QSqlQuery& result) const
{
        debug_printf( Q_FUNC_INFO );
        LevelTable* data = new LevelTable;
        if (is_exist())
        {
                data->m_id = result.value(0).toUInt();
                data->m_name = result.value(1).toString();
                data->set_is_exist(true);
                return data;
        }
        else
        {
                data->m_id = result.value(0).toUInt();
                debug_printf("data->m_id = %u", data->m_id);
                data->m_name = m_name;
                return data;
        }
}

unsigned int LevelTable::get_id()
{
        return m_id;
}

QString LevelTable::get_name()
{
        return m_name;
}

QVariant LevelTable::at(unsigned int index) const
{
        switch (index)
        {
                case 0:
                        return QVariant(m_id);
                        break;
                case 1:
                        return QVariant(m_name);
                        break;
                default:
                        throw;
                        break;
        }
}

QStringList LevelTable::data_filds() const
{
        QStringList return_value;
        return_value << tr("id")
                     << tr("name");
}
