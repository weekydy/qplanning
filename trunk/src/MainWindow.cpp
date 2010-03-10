/*
 * ./MainWindow.cpp
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
/// \file MainWindow.cpp
/// \brief main window of qplanning
/// \author Lameire Alexis
///

#include "MainWindow.h"

MainWindow::MainWindow()
{
        //initializing main window
	m_main = new QWidget;
	setCentralWidget(m_main);
	
        //initializing menu bar
	m_file_menu = menuBar()->addMenu(tr("&Fichier"));

	m_file_menu_new = m_file_menu->addAction(tr("&New"));
	m_file_menu_new->setShortcut(QKeySequence(tr("Ctrl+N", "new file")));
	m_file_menu_new->setIcon(QIcon::fromTheme("document-new"));

	m_file_menu_open = m_file_menu->addAction(tr("&Open"));
	m_file_menu_open->setShortcut(QKeySequence(tr("Ctrl+O", "open file")));
	m_file_menu_open->setIcon(QIcon::fromTheme("document-open"));

	m_file_menu_save = m_file_menu->addAction(tr("&Save"));
	m_file_menu_save->setShortcut(QKeySequence(tr("Ctrl+S", "save fil")));
	m_file_menu_save->setIcon(QIcon::fromTheme("document-save"));

	m_file_menu_save_as = m_file_menu->addAction(tr("&Save as"));
	m_file_menu_save_as->setShortcut(QKeySequence(tr("Ctrl+Maj+S", "save as")));
	m_file_menu_save_as->setIcon(QIcon::fromTheme("document-save-as"));

	m_file_menu_quit = m_file_menu->addAction(tr("&Quit"));
	m_file_menu_quit->setShortcut(QKeySequence(tr("Ctrl+Q", "quit")));
	m_file_menu_quit->setIcon(QIcon::fromTheme("application-exit"));
	
        //initializing toolbar
	m_toolbar = addToolBar(tr("toolbar"));
	m_toolbar->addAction(m_file_menu_new);
	m_toolbar->addAction(m_file_menu_open);
	m_toolbar->addAction(m_file_menu_save);
	m_toolbar->addAction(m_file_menu_save_as);
	m_toolbar->addAction(m_file_menu_quit);

        //initializing statue bar
	m_statusbar = statusBar();

        //initializing layout
	m_layout_1 = new QHBoxLayout(m_main);
	m_layout_1_1 = new QTableView;
	m_layout_1_2 = new QVBoxLayout;
	m_layout_1_2_1 = new QHBoxLayout;
	m_layout_1_2_2 = new QTabWidget;
	m_timetable = new QListWidget;
	m_subjects = new QListWidget;

	m_layout_1->addWidget(m_layout_1_1);
	m_layout_1->addLayout(m_layout_1_2);
	m_layout_1_2->addLayout(m_layout_1_2_1);
	m_layout_1_2->addWidget(m_layout_1_2_2);

	m_timetable_id = m_layout_1_2_2->addTab(m_timetable, tr("timetable"));
	m_subjects_id = m_layout_1_2_2->addTab(m_subjects, tr("subjects"));

	//initialisation button
	m_add_lesson = new QPushButton(tr("add"));
	m_delete_lesson = new QPushButton(tr("del"));
	m_modify_lesson = new QPushButton(tr("edit"));
	m_layout_1_2_1->addWidget(m_add_lesson);
        m_layout_1_2_1->addWidget(m_delete_lesson);
	m_layout_1_2_1->addWidget(m_modify_lesson);

	//connect signals
	QObject::connect(m_file_menu_open, SIGNAL(triggered()), this, SIGNAL(open_file()));
	QObject::connect(m_file_menu_new, SIGNAL(triggered()), this, SIGNAL(create_file()));
	QObject::connect(m_file_menu_save, SIGNAL(triggered()), this, SIGNAL(save_file()));
	QObject::connect(m_file_menu_save_as, SIGNAL(triggered()), this, SIGNAL(save_as_file()));
	QObject::connect(m_modify_lesson, SIGNAL(clicked()), this, SLOT(modify_pressed()));
	QObject::connect(m_add_lesson, SIGNAL(clicked()), this, SLOT(add_pressed()));
}

void MainWindow::update_all_lessons(QVector<KeyValue> subjects)
{
	qDebug( Q_FUNC_INFO );
	m_subjects->clear();
	m_subject_items = subjects;
	for (int i = 0; i != subjects.size(); i++)
	{
		m_subjects->addItem(subjects[i].value);
	}
}

void MainWindow::update_all_timetable(QVector<KeyValue> timetable)
{
	qDebug( Q_FUNC_INFO );
	m_timetable->clear();
	m_timetable_items = timetable;
	for (int i = 0; i != timetable.size(); i++)
	{
		m_timetable->addItem(timetable[i].value);
	}
}

void MainWindow::modify_pressed()
{
	qDebug( Q_FUNC_INFO );
	KeyValue value_to_return;
	if (m_layout_1_2_2->currentIndex() == m_subjects_id)
	{
		if (m_subjects->currentItem() != NULL)
		{
			value_to_return.value = m_subjects->currentItem()->text();
			value_to_return.key =
					m_subject_items[m_subjects->currentRow()].key;
			emit modify_subject(value_to_return);
		}
	}
	else if (m_layout_1_2_2->currentIndex() == m_timetable_id)
	{
		if (m_timetable->currentItem() != NULL)
		{
			value_to_return.value = m_timetable->currentItem()->text();
			value_to_return.key =
					m_timetable_items[m_timetable->currentRow()].key;
			emit modify_timetable(value_to_return);
		}
	}
}

void MainWindow::add_pressed()
{
	if (m_layout_1_2_2->currentIndex() == m_subjects_id)
	{
		emit add_subject();
	}
	else
	{
		emit add_timetable();
	}
}
