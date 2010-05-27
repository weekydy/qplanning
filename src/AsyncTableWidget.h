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
#include <QVector>
#include "debug_printf.h"
#include "AdvencedItemDelegate.h"

template<class T>
class AsyncTableWidget : public QTableWidget
{
        Q_OBJECY
        public:
                ///
                /// \brief default constructor
                ///
                AsyncTableWidget();

        private:
                AdvencedItemDelegate m_delegate;
                QVector<T> m_async_data;
};

#endif // ASYNCTABLEWIDGET_H
