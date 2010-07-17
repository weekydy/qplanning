/*
 * ./AdvencedItemDelegate.h
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
#ifndef ADVENCEDITEMDELEGATE_H
#define ADVENCEDITEMDELEGATE_H
///
/// \file AdvencedItemDelegate.h
/// \brief definition of class AdvencedItemDelegate
/// \author Lameire Alexis
///
#include <QItemDelegate>
#include <QModelIndex>
#include <QCheckBox>
#include "debug_printf.h"
///
/// \class AdvencedItemDegelate AdvencedItemDelegate
/// \brief reimplementation of QT QItemdelegate to emit signal when the edition of item is finis
///
class AdvencedItemDelegate : public QItemDelegate
{
        Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
                AdvencedItemDelegate(QObject* parent = 0);
                ///
                /// \brief surcharged close_editor method : place to emit signal
                ///
                void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

        signals:
                ///
                /// \brief signal emited when editing an item is fionished
                ///
                void editingFinished(const QModelIndex& index);
};

#endif // ADVENCEDITEMDELEGATE_H
