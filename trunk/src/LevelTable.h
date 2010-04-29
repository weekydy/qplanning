
/*
 * ./LevelTable.h
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
#ifndef LEVELTABLE_H
#define LEVELTABLE_H
///
/// \file LevelTable
/// \brief describte the level table (see dia diagram)
/// \author Lameire Alexis
///
#include "AbstractSqlTable.h"
#include "KeyValue.h"
#include <QTextStream>

///
/// \class LevelTable LevelTable.h
/// \brief describle the level table on the sql model
///
class LevelTable : public AbstractSqlTable
{
        public:
                ///
                /// \brief default constructor
                ///
                LevelTable();
                ///
                /// \brief surcharged constructor
                ///
                LevelTable(AdvencedKeyValue data);
                ///
                /// \reimp
                ///
                QString add();
                ///
                /// \reimp
                ///
                QString del();
                ///
                /// \reimp
                ///
                QString edit();
                ///
                /// \reimp
                ///
                bool is_valid();
                ///
                ///  \reimp
                ///
                LevelTable& parse_statment(QSqlQuery& result) const;

        private:
                unsigned int m_id;
                QString m_name;
};

#endif // LEVELTABLE_H
