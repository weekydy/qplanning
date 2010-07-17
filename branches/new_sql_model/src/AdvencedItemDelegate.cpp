/*
 * ./AdvencedItemDelegate.cpp
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
#include "AdvencedItemDelegate.h"
///
/// \file AdvencedItemDelegate.cpp
/// \brief implementation of class AdvencedItemDelegate
/// \author Lameire Alexis
///

AdvencedItemDelegate::AdvencedItemDelegate(QObject *parent) : QItemDelegate(parent)
{
}

void AdvencedItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
        debug_printf( Q_FUNC_INFO );
        QItemDelegate::setModelData(editor, model, index);
        emit const_cast<AdvencedItemDelegate*>(this)->editingFinished(index);
}
