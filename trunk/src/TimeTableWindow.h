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

///
/// \file TimeTableWindow.h
/// \brief editing half hour header
/// \author Lameire Alexis
///

#include <QDialog>
#include <QVector>
#include "KeyValue.h"
#include "ui_TimeTableWindow.h"
#include "TimeTable.h"

///
/// \class TimeTableWindow TimeTableWindow.h
/// \brief editing half hour header
///
class TimeTableWindow : public QDialog, private Ui::TimeTableWindow
{
	Q_OBJECT
	public:
		///
		/// \brief construct a TimTableWindow object with a parent
		/// \param parent parent object to link
		///
		TimeTableWindow(QWidget *parent = 0);
		///
		/// \brief set default data where veuwved when object is show
		/// \param data Timetable data collected in xml file with get_timetable_id
		/// \param lessons_list list of all lessons avalable
		///
                void set_content(Timetable &data, QVector<KeyValue> lessons_list);

        private:
                QVector<KeyValue> m_lessons_list;
};

#endif // TIMETABLEWINDOW_H
