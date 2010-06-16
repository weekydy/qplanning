/*
 * ./SubjectTableh
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
#ifndef SUBJECTTABLE_H
#define SUBJECTTABLE_H
#include "AbstractSqlTable.h"
#include "debug_printf.h"

class SubjectTable : public AbstractSqlTable
{
        Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
                SubjectTable();
                ///
                /// \brief surcharged constructor that set all propertu
                ///
                SubjectTable(QString name, bool with_tp, unsigned int id = 0);
                ///
                /// \reimp
                ///
                QVector<QSqlQuery*> add();
                ///
                /// \reimp
                ///
                QVector<QSqlQuery*> del();
                ///
                /// \reimp
                ///
                QVector<QSqlQuery*> edit();
                ///
                /// \reimp
                ///
                bool is_valid();
                ///
                /// \reimp
                ///
                SubjectTable* parse_statment(QSqlQuery& result) const;
                ///
                /// \brief m_id acessor
                ///
                unsigned int get_id();
                ///
                /// \brief m_id setter
                ///
                void set_id(unsigned int id);
                ///
                /// \brief m_name acesseor
                ///
                QString get_name();
                ///
                /// \brief m_name setter
                ///
                void set_name(QString name);
                ///
                /// \brief m_with_tp acessor
                ///
                bool get_with_tp();
                ///
                /// \brief m_with_tp setter
                ///
                void set_with_tp(bool with_tp);
                ///
                /// \reimp
                ///
                QVariant at(unsigned int index) const;
                ///
                /// \reimp
                ///
                unsigned int number_of_row() const
                {return 3;}
                ///
                /// \reimp
                ///
                virtual QStringList data_filds() const;

        private:
                unsigned int m_id;
                QString m_name;
                bool m_with_tp;
};

#endif // SUBJECTTABLE_H
