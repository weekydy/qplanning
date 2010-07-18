/*
 * ./SqlTable.cpp
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
#include "SqlTable.h"
#include "debug_printf.h"

///
/// \file SqlTable.cpp
/// \brief implement singleton class to create each table
/// \author Lameire Alexis
///

SqlTable::SqlTable()
{
}

QSqlRelationalTableModel& SqlTable::subject_table()
{
        debug_printf( Q_FUNC_INFO );
        static QSqlRelationalTableModel subject_table(0, QSqlDatabase::database());
        static bool is_edited = false;

        if (!is_edited)
        {
                debug_printf("initializing struct");
                subject_table.setTable("subject");
                subject_table.setEditStrategy(QSqlTableModel::OnFieldChange);
                subject_table.removeColumn(0);
                subject_table.setHeaderData(0, Qt::Horizontal, tr("name"));
                subject_table.setHeaderData(1, Qt::Horizontal, tr("with tp"));
                Q_ASSERT(subject_table.select());
                is_edited = true;
        }
        return subject_table;
}

QSqlRelationalTableModel& SqlTable::level_table()
{
        static QSqlRelationalTableModel level_table(0, QSqlDatabase::database());
        static bool is_edited = false;

        if (!is_edited)
        {
                level_table.setTable("level");
                level_table.setEditStrategy(QSqlTableModel::OnFieldChange);
                level_table.select();
                level_table.removeColumn(0);
                level_table.setHeaderData(0, Qt::Horizontal, "name");
                is_edited = true;
        }
        return level_table;
}
