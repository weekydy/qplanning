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
