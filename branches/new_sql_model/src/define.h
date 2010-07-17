/*
 * ./define.h
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
#ifndef DEFINE_H
#define DEFINE_H
///
/// \file define.h
/// \brief some usefull constants
/// \author Lameire Alexis
///

#include "define_cmake.h"
///
/// \brief name of xml shemas
///
#define XSD_FILENAME PROGRAMME_DIR_PREFIX + "/XmlSpec.xsd"



///
/// \brief default name of a new lesson
///
#define DEFAULT_ID_NAME "default"

/*************************************
 *          draw constants           *
 *************************************/

#define TOP_PER_MIL 150
#define LEFT_PER_MIL 45
#define RIGHT_PER_MIL 45
#define BOTTOM_PER_MIL 50
#define ROW_PREMITIVE_PER_MIL 80
#define COLLUM_PREMITIVE_PER_MIL 70
#define HEIGHT 1000
#define LENGTH 1000

#endif
