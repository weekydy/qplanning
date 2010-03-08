/*
 * ./SubjectData.h
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

#ifndef SUBJECTDATA_H
#define SUBJECTDATA_H
///
/// \file SubjectData.h
/// \brief commincation structure with SubjectDataWindow.h
/// \author Lameire Alexis
///

#include <QString>

///
/// \struct SubjectData SubjectData.h
/// \brief commincation structure with SubjectDataWindow.h
///
struct SubjectData
{
	QString name; ///< name of lesson
	QString teacher; ///< teacher that teach lesson
	int red_background; ///< red rgb color to background
	int green_background; ///< green rgb color to background
	int blue_background; ///< blue rgb color to background
	int red_text; ///< red rgb text color
	int green_text; ///< green rgb text color
	int blue_text; ///< blue rgb text color
	unsigned int id; ///< id associated with this data
	bool is_exist; ///< this id are they exist ?
};

#endif // SUBJECTDATA_H
