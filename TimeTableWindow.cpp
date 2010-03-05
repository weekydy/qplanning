/*
 * ./TimeTableWinow.cpp
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
#include "TimeTableWindow.h"

TimeTableWindow::TimeTableWindow(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

void TimeTableWindow::set_content(Timetable &data)
{
	class_edit->setText(data.classroom);
	week_edit->setCurrentIndex(data.week);
	group_edit->setCurrentIndex(data.group);
	begin_edit->setCurrentIndex(data.begin_interval * 2);
	end_edit->setCurrentIndex(data.end_interval * 2);
	part_day_edit->setCurrentIndex(data.half_day);
}

