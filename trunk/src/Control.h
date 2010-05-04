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
///
/// \file Control.h
/// \brief manage communication bitwin veuws and models
/// \author Lameire Alexis
///

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QTransform>
#include "MainWindow.h"
#include "XmlPlanning.h"
#include "SubjectDataWindow.h"
#include "TimeTableWindow.h"
#include "TimeTable.h"
#include "DrawTimetable.h"
#include "FullTimetable.h"
#include "SqlModelGenerating.h"
#include "define.h"
#include "LevelTable.h"

///
/// \class Control Control.h
/// \brief manage communication between veuw and models
///

class Control : public QObject
{
                Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
                Control();

        private:
                ///
                /// \brief tell to user if he would like save is fale and save it
                ///
                void save_before_changing();
                ///
                /// \brief collect all timetable and put his associeted id
                ///
                QVector<FullTimetable> create_full_timetable();
                ///
                /// \brief update veuw when needed;
                ///
                void _update_all_veuw();
        private:
                bool m_is_modified;
                MainWindow m_windows;
                SubjectDataWindow m_config_subject;
                TimeTableWindow m_config_timetable;
                XmlPlanning m_xml_config;
                SqlModelGenerating m_sql_config;
                DrawTimetable m_timetable_veuw;

        public slots:
                ///
                /// \brief tell to view to begin editing a subject
                /// \arg subject id to edit
                ///
                void show_subject(KeyValue subject);
                ///
                /// \brief tell to view to begin editing a timetable
                /// \arg timetable id to edit
                ///
                void show_timetable(KeyValue timetable);
                ///
                /// \brief create a new subject and tell to view to edit it
                ///
                void add_subject();
                ///
                /// \brief create a newx timetable and tell to view to edit it
                ///
                void add_timetable();
                ///
                /// \brief delete the current selected timetable.
                /// \arg timetable timetable need to be delete
                ///
                void del_timetable(KeyValue timetable);
                ///
                /// \brief delete the current selected subject
                /// \arg subject subject need to be delete
                ///
                void del_subject(KeyValue subject);
                ///
                /// \brief managing opening a new file
                /// \arg timetable id and text to deleate
                ///
                void manage_open_file();
                ///
                /// \brief managing create a new file
                ///
                void manage_create_file();
                ///
                /// \brief manazging save current file
                ///
                void manage_save_file();
                ///
                /// \brief managing save as the current file
                ///
                void manage_save_as_file();
                ///
                /// \brief quitting safely the application
                ///
                void manage_quit();
                ///
                /// \brief update xml after editing subject
                ///
                void update_subject();
                ///
                /// \brief update timetable after editing subject
                ///
                void update_timetable();
                ///
                /// \brief print timetable
                ///
                void print_timetable();
                ///
                /// \brief add data on model
                /// \arg data data to store
                /// \arg index index to show
                ///
                void update_level(AdvencedKeyValue data, unsigned int index);
};
#endif
