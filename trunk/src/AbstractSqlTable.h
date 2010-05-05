/*
 * ./AbstractSqlTable.h
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
#ifndef ABSTRACTSQLTABLE_H
#define ABSTRACTSQLTABLE_H

///
/// \file AbstractrSqlTable.h
/// \brief interface to define each sql table
/// \name Lameire Alexis
///
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>

///
/// \class AbstractSqlTable AbstractSqlTable.h
/// \brief interface to define each sql table
///
class AbstractSqlTable
{
        public:
                ///
                /// \brief default constructor that only set is_exist
                ///
                AbstractSqlTable();
                ///
                /// \brief generate sql request to add the element referenced
                ///
                virtual QVector<QSqlQuery*> add() = 0;
                ///
                /// \brief generate sql request to del the element referenced
                ///
                virtual QVector<QSqlQuery*> del() = 0;
                ///
                /// \brief generate sql requesto to edit the element referenced
                ///
                virtual QVector<QSqlQuery*> edit() = 0;
                ///
                /// \brief verify if all data is been present to exectue all subcited method
                ///
                virtual bool is_valid() = 0;
                ///
                /// \brief get if element are been referenced on db
                /// \return it's return the result : true if exist, else false.
                ///
                bool is_exist() const;
                ///
                /// \brief change referenced statut of element
                /// \arg is_exist value to pass on is_exist
                ///
                void set_is_exist(bool is_exist = false);
                ///
                /// \brief parse each row of sql result to store on db
                /// this method must generaly not ne call outdor of the SqlModelGenerating
                /// when this method is reimplementad on the subclass of this model it's most return
                /// the child type and not mother typpe
                /// \arg result sql result to parse
                /// \return an implementation of this class
                ///
                virtual AbstractSqlTable* parse_statment(QSqlQuery& result) const = 0;

        private:
                bool m_is_exist;
};

#endif // ABSTRACTSQLTABLE_H
