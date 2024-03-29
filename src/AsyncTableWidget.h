/*
 * ./AsyncTableWidget.h
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
#ifndef ASYNCTABLEWIDGET_H
#define ASYNCTABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVector>
#include <QHeaderView>
#include <QItemEditorCreatorBase>
#include "debug_printf.h"
#include "AdvencedItemDelegate.h"
#include "AbstractSqlTable.h"

class AsyncTableWidget : public QTableWidget
{
        Q_OBJECT
        public:
                ///
                /// \brief default constructor
                /// \arg sype subtype of AbstractSqlElement to use
                ///
                AsyncTableWidget(Subtype type);
                ///
                /// \brief add items to model
                ///
                void addItem(AbstractSqlTable* item);

        public slots:
                void addItem();

        private:
                AdvencedItemDelegate m_delegate;

                QVector<AbstractSqlTable*> m_async_data;
                AbstractSqlTable* m_constant;
                Subtype m_type;
};

#endif // ASYNCTABLEWIDGET_H
