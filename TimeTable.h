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
	ALL_WEEK = 0,
};
enum Group
{
	ONE = 1,
	TWO = 2,
	ALL_GROUP = 0,
};

struct Timetable
{
	QString unparsed_date;
	QString classroom;
	int id_lesson;
	int ident;
	float begin_interval;
	float end_interval;
	Half_Day half_day;
	Week week;
	Group group;
};

#endif // TIMETABLE_H
