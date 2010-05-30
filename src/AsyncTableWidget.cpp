/*
 * ./AsyncTableWidget.cpp
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

#include "AsyncTableWidget.h"

AsyncTableWidget::AsyncTableWidget(Subtype type)
{
        debug_printf( Q_FUNC_INFO );
        setItemDelegate(&m_delegate);
        //QObject::connect(&m_delegate, SIGNAL(editingFinished(const QModelIndex&)),
        //                 this, SLOT(update_data(const QModelIndex&)));
        m_constant =  AbstractSqlTable::create_element_from_type(type);
        setColumnCount(m_constant->number_of_row() - 1);

        QStringList collum_head = m_constant->data_filds();
        QStringList collum_real_head;
        for (int i = 1; i != m_constant->number_of_row(); i++)
        {
                collum_real_head << collum_head[i];
        }
        setHorizontalHeaderLabels(collum_real_head);
}

void AsyncTableWidget::addItem(AbstractSqlTable* item)
{
        m_async_data.push_back(item);
        for (int i = 0; i != item->number_of_row(); i++)
        {
                QTableWidgetItem widget_item;
                widget_item.setData(Qt::EditRole, item->at(i));
                setItem(m_async_data.size() - 1,
                        i,
                        &widget_item);
        }
}
