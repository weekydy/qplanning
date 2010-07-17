/*
 * ./FullTimetable.h
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
#ifndef FULLTIMETABLE_H
#define FULLTIMETABLE_H
#include "TimeTable.h"
#include "SubjectData.h"
///
/// \file FullTimetable.h
/// \brief provide the full timetable structure
/// \author Lameire Alexis
///

///
/// \struct FullTimetable FullTimetable.h
/// \brief associate a timetable with this subject is usefull to XmlPlanning and Drowtimetable
///
struct FullTimetable
{
        Timetable timetable;
        SubjectData subject_associated;
};

#endif // FULLTIMETABLE_H
