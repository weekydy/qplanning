/*
 * ./MyCheckBox.h
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
#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H
///
/// \file MyCheckBox.h
/// \brief add a user property to standart QCheckBox
/// \author Lameire Alexis
///

#include <QCheckBox>
///
/// \class MyCheckBox MyCheckBox.h
/// \brief add a user property to standart QCheckBox
///
class MyCheckBox : public QCheckBox
{
        Q_OBJECT
        Q_PROPERTY(bool Value READ get_value WRITE set_value USER true)
        public:
                ///
                /// \brief default constructor
                ///
                explicit MyCheckBox(QWidget *parent = 0);
                ///
                /// \brief get the content of the checkbox
                ///
                bool get_value();
                ///
                /// \brief set the content of the checkbox
                ///
                void set_value(bool value);
};

#endif // MYCHECKBOX_H
