
/*
 * ./MyCheckBox.cpp
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
/// \file MyCheckBox.cpp
/// \brief add a user property to standart QCheckBox
/// \author Lameire Alexis
///

#include "MyCheckBox.h"
MyCheckBox::MyCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
}

bool MyCheckBox::get_value()
{
        switch (checkState())
        {
                case Qt::Unchecked:
                        return false;
                        break;
                case Qt::Checked:
                        return true;
                        break;
                default:
                        throw;
        }
}

void MyCheckBox::set_value(bool value)
{
        setCheckState((value) ? Qt::Checked : Qt::Unchecked);
}
