#ifndef TIMETABLE_H
#define TIMETABLE_H
#include "KeyValue.h"
#include <QString>

enum Half_Day
{
	MORNING = 'M',
	AFTERNOON = 'A'
};
enum Week
{
	PEER = 1,
	UNPEER = 2,
	ALL_WEEK = 3,
};
enum Group
{
	ONE = 1,
	TWO = 2,
	ALL_GROUP = 3,
};

struct Timetable
{
	QString unparsed_date;
	QString classroom;
	unsigned int id_lesson;
	unsigned int ident;
	float begin_interval;
	float end_interval;
	Half_Day half_day;
	Week week;
	Group group;
};

#endif // TIMETABLE_H
