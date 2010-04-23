/*
 * ./AsyncListView.h
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
#ifndef ASYNCLISTVIEW_H
#define ASYNCLISTVIEW_H
///
/// \file AsyncListView.h
/// \brief advenced QListWidget
/// \author Lameire Alexis
///
#include <QListWidget>
#include "AdvencedItemDelegate.h"

///
/// \class AsyncListView AsyncListView.h
/// \brief advencd QlistWiget that alow to store data end emit custom signals
///
class AsyncListView : public QListWidget
{
        Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
                AsyncListView(QWidget* parent = 0);

        private:
                AdvencedItemDelegate m_delegate;

        signals:
                ///
                /// \brief signal emit when an tab is finis to edit
                ///
                void editing_finished(const QModelIndex& model);
};

#endif // ASYNCLISTVIEW_H
