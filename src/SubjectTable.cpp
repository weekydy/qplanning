/*
 * ./SubjectTimeta&ble
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
#include "SubjectTable.h"

SubjectTable::SubjectTable() : AbstractSqlTable()
{
        set_is_exist(false);
}

SubjectTable::SubjectTable(QString name, bool with_tp, unsigned int id) : AbstractSqlTable()
{
        m_name = name;
        m_with_tp = with_tp;
        m_id = id;
        set_is_exist(m_id);
}

bool SubjectTable::is_valid()
{
        if (!m_name.isNull())
        {
                if ((!m_id && is_exist()) || (m_id && !is_exist()))
                {
                        return true;
                }
                else
                {
                        return false;
                }
        }
        return false;
}

QVector<QSqlQuery*> SubjectTable::add()
{
        debug_printf( Q_FUNC_INFO );
        if (is_valid())
        {
                QVector<QSqlQuery*> querys;
                bool error = true;
                querys.push_back(new QSqlQuery());
                error &= querys[0]->prepare("INSERT INTO subject(name, with_tp) VALUES(?, ?);");
                querys[0]->bindValue(0, m_name);
                querys[0]->bindValue(1, m_with_tp);
                querys.push_back(new QSqlQuery());
                error &= querys[1]->prepare("SELECT id FROM subject WHERE id=LAST_INSERT_ROWID();");

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

QVector<QSqlQuery*> SubjectTable::del()
{
        debug_printf( Q_FUNC_INFO );
        if (is_valid() && m_id != 0)
        {
                QVector<QSqlQuery*> query;
                query.push_back(new QSqlQuery);
                query[0]->prepare("DELETE FROM subject WHERE id=:id");
                query[0]->bindValue(":id", m_id);
                return query;
        }
        throw;
}

QVector<QSqlQuery*> SubjectTable::edit()
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
                query[0]->prepare("UPDATE subject SET name=:name, with_tp=:with_tp WHERE id=:id");
                query[0]->bindValue(":id", m_id);
                query[0]->bindValue(":name", m_name);
                query[0]->bindValue(":with_tp", m_with_tp);
                return query;
        }
}

SubjectTable* SubjectTable::parse_statment(QSqlQuery& result) const
{
        debug_printf( Q_FUNC_INFO );
        SubjectTable* data = new SubjectTable;
        if (is_exist())
        {
                data->m_id = result.value(0).toUInt();
                data->m_name = result.value(1).toString();
                data->m_with_tp = result.value(2).toBool();
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

unsigned int SubjectTable::get_id()
{
        return m_id;
}

void SubjectTable::set_id(unsigned int id)
{
        m_id = id;
}

QString SubjectTable::get_name()
{
        return m_name;
}

void SubjectTable::set_name(QString name)
{
        m_name = name;
}

bool SubjectTable::get_with_tp()
{
        return m_with_tp;
}

void SubjectTable::set_with_tp(bool with_tp)
{
        m_with_tp = with_tp;
}

QVariant SubjectTable::at(unsigned int index) const
{
        switch (index)
        {
                case 0:
                        return QVariant(m_id);
                        break;
                case 1:
                        return QVariant(m_name);
                        break;
                case 2:
                        return QVariant(m_with_tp);
                        break;
                default:
                        throw;
                        break;
        }
}

QStringList SubjectTable::data_filds() const
{
        QStringList return_value;
        return_value << tr("id")
                     << tr("name")
                     << tr("with tp");
        return return_value;
}
