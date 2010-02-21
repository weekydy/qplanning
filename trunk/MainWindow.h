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

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QTableView>
#include <QListWidget>
#include <QString>
#include <QStringList>

class MainWindow : public QMainWindow
{
	Q_OBJECT;
	public:
        MainWindow();

	private:
	QWidget* m_main;
        QMenu* m_file_menu;
	QToolBar* m_toolbar;
	QAction* m_file_menu_new;
        QAction* m_file_menu_open;
        QAction* m_file_menu_save;
        QAction* m_file_menu_save_us;
        QAction* m_file_menu_quit;
	QStatusBar* m_statusbar;
        QPushButton* m_add_lesson;
        QPushButton* m_delete_lesson;
        QPushButton* m_modify_lesson;
	QHBoxLayout* m_layout_1;
	QVBoxLayout* m_layout_1_2;
	QTableView* m_layout_1_1;
	QHBoxLayout* m_layout_1_2_1;
	QListWidget* m_widget_1_2_2;

	public slots:
	void update_all_lessons(QStringList subjects);
	void modify_subject_pressed();

	signals:
	void modify_subject(QString subject);
	void add_subject();
	void open_file();
        void create_file();
};
#endif
