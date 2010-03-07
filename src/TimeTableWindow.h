/*
 * ./TimeTableWindow.h
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
#ifndef TIMETABLEWINDOW_H
#define TIMETABLEWINDOW_H

#include <QDialog>
#include <QVector>
#include "KeyValue.h"
#include "ui_TimeTableWindow.h"
#include "TimeTable.h"

class TimeTableWindow : public QDialog, private Ui::TimeTableWindow
{
	Q_OBJECT
	public:
		TimeTableWindow(QWidget *parent = 0);
                void set_content(Timetable &data, QVector<KeyValue> lessons_list);

        private:
                QVector<KeyValue> m_lessons_list;
};

#endif // TIMETABLEWINDOW_H
