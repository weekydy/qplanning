/*
 * ./Control.h
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
#ifndef KEYVALUE_H
#define KEYVALUE_H
///
/// \file KeyValue.h
/// \brief couple of Key and Value
/// \author Lameire Alexis
///

#include <QString>

///
/// \struct KeyValue KeyValue.h
/// \brief couple of Key and Value
///

struct KeyValue
{
        unsigned int key; ///< key
        QString value; ///< text value associated to key
};

///
/// \struct AdvencedKeyValue KeyValue.h
/// \brief advended KeyValue structure that add exist constraint
///

struct AdvencedKeyValue
{
        unsigned int key; ///< key
        QString value; ///< text value associated to key
        bool is_exist; ///< exist constraint
};

#endif // KEYVALUE_H
