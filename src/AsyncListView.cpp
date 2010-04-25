/*
 * ./AsyncListView.cpp
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

///
/// \file AsyncListView.cpp
/// \brief advenced QListWidget
/// \author Lameire Alexis
///

#include "AsyncListView.h"

AsyncListView::AsyncListView(QWidget* parent) : QListWidget(parent)
{
        qDebug( Q_FUNC_INFO );
        setItemDelegate(&m_delegate);
        QObject::connect(&m_delegate, SIGNAL(editingFinished(const QModelIndex&)),
                         this, SIGNAL(editing_finished(const QModelIndex&)));
}

void AsyncListView::addItem(unsigned int id, QString value, bool is_exist, bool is_editable)
{
        AdvencedKeyValue item;
        item.key = id;
        item.value = value;
        item.is_exist = is_exist;
        addItem(item, is_editable);
}

void AsyncListView::addItem(AdvencedKeyValue item, bool is_editable)
{
        m_async_data.push_back(item);

        QListWidget::addItem(item.value);
        setCurrentRow(count() - 1);

        QListWidgetItem* item_to_edit = this->item(currentRow());
        if (is_editable)
        {
                item_to_edit->setFlags(item_to_edit->flags() | Qt::ItemIsEditable);
        }
        edit(currentIndex());
}
