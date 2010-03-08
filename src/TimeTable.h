#ifndef TIMETABLE_H
#define TIMETABLE_H
#include "KeyValue.h"
#include <QString>

///
/// \file TimeTable.h
/// \brief timetable structure to comunicate with TimeTableWindow
/// \author Lameire Alexis
///

/// \enum Half_Day
/// \brief stock if is morning or afternoon
enum Half_Day
{
	MORNING = 'M', ///< morning plage
	AFTERNOON = 'A' ///< afternoon plage
};

/// \enum Week
/// \brief stock if is Peer week, unpeer week or all week
enum Week
{
	PEER = 1, ///< first weeks
	UNPEER = 2, ///< second weeks
	ALL_WEEK = 3, ///< all weeks
};

/// \enum Group
/// \brief stock if is first group, second group or all group
enum Group
{
	ONE = 1, ///< first group
	TWO = 2, ///< second group
	ALL_GROUP = 3, ///< all group
};

///
/// \struct Timetable TimeTable.h
/// \brief timetable structure to comunicate with TimeTableWindow
///

struct Timetable
{
	QString unparsed_date;  ///< unparced timetable data
	QString classroom; ///< classroom where the lesse do
	unsigned int id_lesson; ///< lesson associated with this data
	unsigned int ident; ///< id associated with this data
	float begin_interval; ///< begin time intervall [0 - 4]
	float end_interval; ///< end time intervall [0 - 4]
	Half_Day half_day; ///< half day period
	Week week; ///< week concerned by this lesson
	Group group; ///< group concerned by this lesson
};

#endif // TIMETABLE_H
