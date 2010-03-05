/*
 * ./Control.h
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
#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "MainWindow.h"
#include "XmlPlanning.h"
#include "SubjectDataWindow.h"
#include "TimeTableWindow.h"
#include "TimeTable.h"
#include "define.h"

class Control : public QObject
{
	Q_OBJECT
        public:
        Control();

	private:
	void save_before_changing();

        private:
	bool m_is_modified;
	MainWindow m_windows;
	SubjectDataWindow m_config_subject;
	TimeTableWindow m_config_timetable;
	XmlPlanning m_config;

	public slots:
	void show_subject(KeyValue subject);
	void show_timetable(KeyValue timetable);
	void add_subject();
	void manage_open_file();
        void manage_create_file();
	void manage_save_file();
	void manage_save_as_file();
	void update_xml();
};
#endif
