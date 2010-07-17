/*
 * ./SqlTable.h
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
#ifndef SQLTABLE_H
#define SQLTABLE_H

///
/// \file SqlTable.h
/// \brief singleton class to define each sql table
/// \name Lameire Alexis
///
#include <QSqlRelationalTableModel>
#include <QObject>

///
/// \enum subtype
/// \brief define the subtype of this structure
///

///
/// \class SqlTable SqlTable.h
/// \brief singleton class to define each sql table.
///
class SqlTable : public QObject
{
        Q_OBJECT
        public:
                static QSqlRelationalTableModel& subject_table();
                static QSqlRelationalTableModel& level_table();

        private:
                SqlTable();

};

#endif // SQLTABLE_H
