/*
 * ./SqlModelGenerating.cpp
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

#include "SqlModelGenerating.h"
///
/// \file SqlModelGenerating.cpp
/// \brief manage communication with sql database
/// \author Lameire Alexis
///


SqlModelGenerating::SqlModelGenerating() :
    m_sql_db(QSqlDatabase::addDatabase("QSQLITE")),
    m_tmp_file(QDir::tempPath() + "/QPlanning_XXXXXX.db", this)
{
        qDebug( Q_FUNC_INFO );
        connect_db();
        if (m_filepath.isNull())
        {
                _create_basic_shemas();
        }
}


void SqlModelGenerating::connect_db(QString path)
{
        qDebug(Q_FUNC_INFO);
        m_sql_db.setHostName("localhost");
        m_sql_db.setUserName("root");
        m_sql_db.setPassword("");
        m_filepath = path;
        m_tmp_file.open();
        qDebug(qPrintable(m_tmp_file.fileName()));
        m_tmp_file.close();

        if (!m_filepath.isNull())
        {
                QFile::copy(m_filepath, m_tmp_file.fileName());
        }
        m_sql_db.setDatabaseName(m_tmp_file.fileName());
        if (!m_sql_db.open())
        {
                qDebug("can't open database");
                qDebug(qPrintable(m_sql_db.lastError().driverText()));
                throw;
        }
}


void SqlModelGenerating::_create_basic_shemas()
{
        qDebug(Q_FUNC_INFO);
        QSqlQuery query;
        QStringList query_str;
        query_str << "PRAGMA foreign_keys = ON;"
                  << "CREATE TABLE level"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        name VARCHAR(64) NOT NULL"
                     ");"
                  << "CREATE TABLE subject"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        name VARCHAR(64) NOT NULL,"
                     "        with_tp BOOLEAN"
                     ");"
                  << "CREATE TABLE class"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        name VARCHAR(64) NOT NULL,"
                     "        id_level INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_level) REFERENCES level(id)"
                     ");"
                  << "CREATE TABLE hour_by_level"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_level INTEGER NOT NULL,"
                     "        id_subject INTEGER NOT NULL,"
                     "        number_of_hour INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_level) REFERENCES level(id),"
                     "        FOREIGN KEY(id_subject) REFERENCES subject(id)"
                     ");"
                  << "CREATE TABLE option"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_level INTEGER NOT NULL,"
                     "        id_subject INTEGER NOT NULL,"
                     "        number_of_hour INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_level) REFERENCES level(id),"
                     "        FOREIGN KEY(id_subject) REFERENCES subject(id)"
                     ");"
                  << "CREATE TABLE teacher"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        name VARCHAR(64) NOT NULL,"
                     "        hour_of_work INTEGER NOT NULL,"
                     "        id_subject INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_subject) REFERENCES subject(id)"
                     ");"
                  << "CREATE TABLE timetable"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        name VARCHAR(64) NOT NULL,"
                     "        id_level INTEGER NOT NULL,"
                     "        referent_teacher INTEGER,"
                     "        FOREIGN KEY(id_level) REFERENCES level(id),"
                     "        FOREIGN KEY(referent_teacher) REFERENCES teacher(id)"
                     ");"
                  << "CREATE TABLE class_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_teacher INTEGER NOT NULL,"
                     "        id_class INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_teacher) REFERENCES teacher(id),"
                     "        FOREIGN KEY(id_class) REFERENCES class(id)"
                     ");"
                  << "CREATE TABLE teacher_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_teacher INTEGER NOT NULL,"
                     "        id_timetable INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_teacher) REFERENCES teacher(id),"
                     "        FOREIGN KEY(id_timetable) REFERENCES timetable(id)"
                     ");"
                  << "CREATE TABLE hour_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_timetable INTEGER NOT NULL,"
                     "        day INTEGER NOT NULL,"
                     "        morning BOOLEAN,"
                     "        begin_interval NUMERIC(2,1),"
                     "        end_interval NUMERIC(2,1),"
                     "        forced BOOLEAN,"
                     "        denied BOOLEAN,"
                     "        FOREIGN KEY(id_timetable) REFERENCES timetable(id),"
                     "        CHECK(NOT (forced AND denied)),"
                     "        CHECK(NOT (NOT forced AND NOT denied))"
                     "        CHECK(begin_interval < end_interval),"
                     "        CHECK(begin_interval <= 4),"
                     "        CHECK(begin_interval >= 0),"
                     "        CHECK(end_interval <= 4),"
                     "        CHECK(end_interval >= 0),"
                     "        CHECK((begin_interval % 1) == 0 OR (begin_interval % 1) == 0.5),"
                     "        CHECK((end_interval % 1) == 0 OR (end_interval % 1) == 0.5),"
                     "        CHECK(day <= 6),"
                     "        CHECK(day >= 1),"
                     "        CHECK(day == 6 AND NOT morning)"
                     ");"
                  << "CREATE TABLE subject_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_subject INTEGER NOT NULL,"
                     "        id_level INTEGER NOT NULL,"
                     "        number_of_hour_by_tp UNSIGNED INTEGER NOT NULL,"
                     "        number_of_tp UNSIGNED INTEGER DEFAULT 1,"
                     "        FOREIGN KEY(id_subject) REFERENCES suject(id),"
                     "        FOREIGN KEY(id_level) REFERENCES level(id)"
                     ");"
                  << "CREATE TABLE group_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_level INTEGER NOT NULL,"
                     "        id_subject INTEGER NOT NULL,"
                     "        number_of_hour UNSIGNED DOUBLE(2, 1) NOT NULL,"
                     "        FOREIGN KEY(id_level) REFERENCES level(id),"
                     "        FOREIGN KEY(id_subject) REFERENCES subject(id),"
                     "        CHECK((number_of_hour % 1) == 0.5 OR (number_of_hour % 1) == 0)"
                     ");"
                  << "CREATE TABLE opt_constraint"
                     "("
                     "        id INTEGER PRIMARY KEY,"
                     "        id_opt_1 INTEGER NOT NULL,"
                     "        id_opt_2 INTEGER NOT NULL,"
                     "        FOREIGN KEY(id_opt_1) REFERENCES option(id),"
                     "        FOREIGN KEY(id_opt_2) REFERENCES option(id),"
                     "        CHECK(id_opt_1 != id_opt_2)"
                     ");";
        for (int i = 0; i != query_str.size(); i++)
        {
                if (!query.exec(query_str.at(i)))
                {
                        qDebug(qPrintable(query.lastError().driverText()));

                        throw;
                }
                qDebug(qPrintable(query.lastQuery()));
        }
}
