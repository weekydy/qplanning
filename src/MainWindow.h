/*
 * ./MainWindow.h
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
///
/// \file MainWindow.h
/// \brief header of main window of Qplanning
/// \author Lameire Alexis
///

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QTableView>
#include <QTabWidget>
#include <QListWidget>
#include <QString>
#include <QStringList>
#include <QGraphicsView>
#include <QVector>
#include "KeyValue.h"

///
/// \class MainWindow MainWindow.h
/// \brief main window of qplanning
///
class MainWindow : public QMainWindow
{
                Q_OBJECT;
        public:
                ///
                /// \brief default constructor of MainWindow
                ///
                MainWindow();

                ///
                /// \brief connect the scean veuw to his content
                /// \arg scean sceane to set
                ///
                void set_scean(QGraphicsScene* scene);

        protected:
                ///
                /// \brief reemplemented resizeEvent of QWidget to add capability to rescale m_widget_1_1
                /// \arg event event sended by Qt
                ///
                void resizeEvent(QResizeEvent* event);

        private:
                QWidget* m_main;
                QMenu* m_file_menu;
                QToolBar* m_toolbar;
                QAction* m_file_menu_new;
                QAction* m_file_menu_open;
                QAction* m_file_menu_save;
                QAction* m_file_menu_save_as;
                QAction* m_file_menu_quit;
                QStatusBar* m_statusbar;
                QPushButton* m_add_lesson;
                QPushButton* m_delete_lesson;
                QPushButton* m_modify_lesson;
                QHBoxLayout* m_layout_1;
                QVBoxLayout* m_layout_1_2;
                QGraphicsView* m_widget_1_1;
                QHBoxLayout* m_layout_1_2_1;
                QListWidget* m_subjects;
                int m_subjects_id;
                QListWidget* m_timetable;
                int m_timetable_id;
                QTabWidget* m_layout_1_2_2;
                QVector<KeyValue> m_subject_items;
                QVector<KeyValue> m_timetable_items;

        public slots:
                ///
                /// \brief update the list of lessons vewved
                /// \param subjects list of lessons to show
                ///
                void update_all_lessons(QVector<KeyValue> subjects);
                ///
                /// \brief update the list of timetable vewved
                /// \param timetable list of timetable to show
                ///
                void update_all_timetable(QVector<KeyValue> timetable);
                ///
                /// \brief slot to emit the god signal when modify button is pressed
                ///
                void modify_pressed();
                ///
                /// \brief slot to emit the god signal when add button is pressed
                ///
                void add_pressed();

        signals:
                ///
                /// \brief signal emit when subject need to be edit
                /// \param subject subject data to edit
                ///
                void modify_subject(KeyValue subject);
                ///
                /// \brief signal emit when timetable need to be edit
                /// \param timetable timetable data to edit
                ///
                void modify_timetable(KeyValue timetable);
                ///
                /// \brief signal emit when subject need to be add
                ///
                void add_subject();
                ///
                /// \brief signal emit when timetable need to be edit
                ///
                void add_timetable();
                ///
                /// \brief signal emit when file need to be open
                ///
                void open_file();
                ///
                /// \brief signal emit when file need to be create
                ///
                void create_file();
                ///
                /// \brief signal emit when file need to be save
                ///
                void save_file();
                ///
                /// \brief signal emit when file need to be save as
                ///
                void save_as_file();
                ///
                /// \brief signal emit when programm must be quit
                ///
                void quit();
};
#endif
