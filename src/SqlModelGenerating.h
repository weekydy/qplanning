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

///
/// \class SqlModelGenerating SqlModelGenerating.h
/// \brief manage communication with sql database
///
class SqlModelGenerating : public QObject
{
        Q_OBJECT
        public:
               ///
               /// \brief default constructor
               ///
               SqlModelGenerating(QObject *parent = 0);
               ///
               /// \brief connect to the database
               /// \arg path path of the sqlite database
               ///
               void connect_db(QString path = QString());
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

#endif // SQLMODELGENERATING_H
