/*
 * ./SqlModelGenerating.h
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
#ifndef SQLMODELGENERATING_H
#define SQLMODELGENERATING_H
///
/// \file SqlModelGenerating.h
/// \brief manage communication with sql database
/// \author Lameire Alexis
///
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTemporaryFile>
#include <QSqlError>
#include <QDir>
#include <QVector>
#include "KeyValue.h"
#include "AbstractSqlTable.h"

///
/// \class SqlModelGenerating SqlModelGenerating.h
/// \brief manage communication with sql database
///

class SqlModelGenerating : public QObject
{
        public:
               ///
               /// \brief default constructor
               ///
               SqlModelGenerating();
               ///
               /// \brief connect to the database
               /// \arg path path of the sqlite database
               ///
               void connect_db(QString path = QString());
               ///
               /// \brief add or update a lesson on the db
               ///
               void update_lesson(AdvencedKeyValue data);

        private:
               ///
               /// \brief create basic table content
               ///
               void _create_basic_shemas();

        private:
               QSqlDatabase m_sql_db;
               QString m_filepath;
               QTemporaryFile m_tmp_file;
};

template<class T>
///
/// \brief add data in databsae
/// \arg data : one of implementation of AbstractSqlTable
///
T& add(T& data)
{
        QSqlQuery query;
        query.prepare(data.add());

        QVector<T> items = _exec_query(query, data);
        Q_ASSERT(items.size() == 1);

        return items[0];
}

///
/// \brief execute and parse the result of a query
/// \arg QSqlQuery querry to execute
/// \arg data table used to parse data
///
template<class T>
QVector<T> _exec_query(QSqlQuery query, T &data)
{
        QVector<T> items;
        if (query.exec())
        {
                throw query.lastError().driverText();
        }

        while (query.next())
        {
                T item = data.parse_statment(query);
                items.push_back(item);
        }
        return items;
}

#endif // SQLMODELGENERATING_H
