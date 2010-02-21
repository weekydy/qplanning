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
#include <QString>

struct SubjectData
{
	QString name;
	QString teacher;
	int red_background;
	int green_background;
	int blue_background;
	int red_text;
	int green_text;
	int blue_text;
	int id;
	bool is_exist;
};

#endif // SUBJECTDATA_H
