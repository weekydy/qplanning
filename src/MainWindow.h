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
#include <QResizeEvent>
#include <QCloseEvent>
#include <QShowEvent>
#include <QSizePolicy>
#include <QLabel>
#include "KeyValue.h"
#include "define.h"
#include "AsyncListView.h"

///
/// \class MainWindow MainWindow.h
/// \brief main window of qplanning
///
class MainWindow : public QMainWindow
{
                Q_OBJECT
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
                ///
                /// \brief update a intem on the level list
                ///
                void update_index_level(AdvencedKeyValue item, unsigned int index);

        protected:
                ///
                /// \brief reemplemented resizeEvent of QWidget to add capability to rescale m_widget_1_1
                /// \arg event event sended by Qt
                ///
                void resizeEvent(QResizeEvent* event);
                ///
                /// \brief eneable capability to don't quit windows
                /// \arg event event infos
                ///
                void closeEvent(QCloseEvent* event);
                ///
                /// \brief same usage of resizeEvent but it's solve it in the first veuw
                /// \arg event event info
                ///
                void showEvent(QShowEvent* event);

        private:
                ///
                /// \brief calcule and aplie the scale factor in function of space area avalable
                ///
                void calcule_scale_factor();

        private:
                QWidget* m_main_edit_timetable;
                QWidget* m_main_generate_timetable;
                QMenu* m_file_menu;
                QToolBar* m_toolbar;
                QAction* m_file_menu_new;
                QAction* m_file_menu_open;
                QAction* m_file_menu_save;
                QAction* m_file_menu_save_as;
                QAction* m_file_menu_quit;
                QAction* m_file_menu_print;
                QStatusBar* m_statusbar;
                QPushButton* m_add_lesson;
                QPushButton* m_delete_lesson;
                QPushButton* m_modify_lesson;
                QTabWidget* m_tab;
                QHBoxLayout* m_layout_1;
                QVBoxLayout* m_layout_1_2;
                QGraphicsView* m_widget_1_1;
                QHBoxLayout* m_layout_1_2_1;
                QBoxLayout* m_layout_2;
                QTabWidget* m_layout_2_1;
                QWidget* m_widget_2_1_1;
                QHBoxLayout* m_layout_2_1_1_1;
                QVBoxLayout* m_layout_2_1_1_1_1;
                QLabel* m_text_2_1_1_1_1_1;
                QHBoxLayout* m_layout_2_1_1_1_1_2;
                QPushButton* m_add_2_1_1_1_1_2_1;
                QPushButton* m_del_2_1_1_1_1_2_2;
                AsyncListView* m_level_2_1_1_1_1_3;
                QVBoxLayout* m_layout_2_1_1_1_2;
                QLabel* m_text_2_1_1_1_2_1;
                QHBoxLayout* m_layout_2_1_1_1_2_2;
                QPushButton* m_add_2_1_1_1_2_2_1;
                QPushButton* m_del_2_1_1_1_2_2_2;
                AsyncListView* m_subject_2_1_1_1_2_3;
                QListWidget* m_subjects;
                int m_subjects_id;
                QListWidget* m_timetable;
                int m_timetable_id;
                QTabWidget* m_layout_1_2_2;
                QVector<KeyValue> m_subject_items;
                QVector<KeyValue> m_timetable_items;
                QVector<AdvencedKeyValue> m_level;
                bool m_need_to_close;
                int m_edit_timetable_id;
                int m_generate_timetable_id;

        private slots:
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
                void draw_modify_pressed();
                ///
                /// \brief slot to emit the god signal when add button is pressed
                ///
                void draw_add_pressed();
                ///
                /// \brief slot to emit the god signa when dell button is pressed
                ///
                void draw_del_pressed();
                ///
                /// \brief slot to emit quit_needed and set the m_need_to_close
                ///
                void manage_quit_needed();
                ///
                /// \brief slot to emit the del_level signal and delet it in view
                ///
                void manage_del_level();

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
                /// \brief signel emit when timetable need to be delete
                /// \arg[in] data id and name of the id to dell
                ///
                void del_timetable(KeyValue data);
                ///
                /// \brief signal emit when subject need to be delete
                /// \arg[in] data id and name of the id to dell
                ///
                void del_subject(KeyValue data);
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
                void quit_needed();
                ///
                /// \brief signal emit when timetable need to be printed
                ///
                void print_needed();
                ///
                /// \brief signal emit when update level needed
                ///
                void update_level(AdvencedKeyValue item, unsigned int index);
                ///
                /// \brief signal emit when level need to be delete
                ///
                void del_level(AdvencedKeyValue item);
};
#endif
