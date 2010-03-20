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

///
/// \file TimeTableWindow.cpp
/// \brief editing a half time
/// \author Lameire Alexis
///
#include "TimeTableWindow.h"

TimeTableWindow::TimeTableWindow(QWidget* parent) : QDialog(parent)
{
        setupUi(this);
}

void TimeTableWindow::set_content(Timetable& data, QVector<KeyValue> lessons_list)
{
        qDebug( Q_FUNC_INFO );
        qDebug("%u", data.id_lesson);

        class_edit->setText(data.classroom);
        week_edit->setCurrentIndex(data.week - 1);
        group_edit->setCurrentIndex(data.group - 1);
        begin_edit->setCurrentIndex(data.begin_interval * 2);
        subject_edit->clear();
        end_edit->setCurrentIndex(data.end_interval * 2);
        switch (data.half_day)
        {
                case MORNING:
                        part_day_edit->setCurrentIndex(0);
                        break;
                case AFTERNOON:
                        part_day_edit->setCurrentIndex(1);
                        break;
        }

        for (int i = 0; i != lessons_list.size(); i++)
        {
                subject_edit->addItem(lessons_list[i].value);
                if (lessons_list[i].key == data.id_lesson)
                {
                        qDebug("id found");
                        subject_edit->setCurrentIndex(i);
                }
        }
        if (data.id_lesson == UINT_MAX)
        {
                subject_edit->setCurrentIndex(-1);
        }


        m_lessons_list = lessons_list;
        m_id = data.ident;
}

Timetable TimeTableWindow::get_content()
{
        Timetable data;

        data.classroom = class_edit->text();
        data.week = (Week) (week_edit->currentIndex() + 1);
        data.group = (Group) (group_edit->currentIndex() + 1);
        data.begin_interval = (float) begin_edit->currentIndex() / (float) 2;
        data.end_interval = (float) end_edit->currentIndex() / (float) 2;
        data.ident = m_id;
        data.id_lesson = m_lessons_list[subject_edit->currentIndex()].key;

        int part_day = part_day_edit->currentIndex();
        switch (part_day)
        {
                case 0:
                        data.half_day = MORNING;
                        break;
                case 1:
                        data.half_day = AFTERNOON;
                        break;
        }
        data.unparsed_date.sprintf("%c%.1f-%c%.1f", data.half_day, data.begin_interval, data.half_day, data.end_interval);
        return data;
}
