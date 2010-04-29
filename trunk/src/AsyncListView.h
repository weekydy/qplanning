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
#include <QListWidgetItem>
#include <QVector>
#include "AdvencedItemDelegate.h"
#include "KeyValue.h"
#include "define.h"

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
                ///
                /// \brief add an item
                /// \arg item item to store
                /// \arg is_editable
                ///
                void addItem(AdvencedKeyValue item, bool is_editable = true);
                AdvencedKeyValue operator[](unsigned int index);

        private:
                AdvencedItemDelegate m_delegate;
                QVector<AdvencedKeyValue> m_async_data;

        signals:
                ///
                /// \brief signal emit when an tab is finis to edit
                ///
                void editing_finished(const QModelIndex& model);

        public slots:
                ///
                /// \brief add an item
                /// \arg id id in model
                /// \arg value texte to show
                /// \arg is_exist precise if item exist in view
                /// \arg is_editable precise if item is editable
                ///
                void addItem(unsigned int id = 0, QString value = DEFAULT_ID_NAME, bool is_exist = false, bool is_editable = true);
};

#endif // ASYNCLISTVIEW_H
