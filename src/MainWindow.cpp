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

MainWindow::MainWindow() : m_need_to_close(false)
{
        //initializing main windows
        m_main_edit_timetable = new QWidget;
        m_main_generate_timetable = new QWidget;
        m_tab = new QTabWidget;
        setCentralWidget(m_tab);

        //initializing menu bar
        m_file_menu = menuBar()->addMenu(tr("&File"));

        m_file_menu_new = m_file_menu->addAction(tr("&New"));
        m_file_menu_new->setShortcut(QKeySequence(tr("Ctrl+N", "new file")));
        m_file_menu_new->setIcon(QIcon::fromTheme("document-new"));

        m_file_menu_open = m_file_menu->addAction(tr("&Open"));
        m_file_menu_open->setShortcut(QKeySequence(tr("Ctrl+O", "open file")));
        m_file_menu_open->setIcon(QIcon::fromTheme("document-open"));

        m_file_menu_print = m_file_menu->addAction(tr("&Print"));
        m_file_menu_print->setShortcut(QKeySequence(tr("Ctrl+P", "print")));
        m_file_menu_print->setIcon(QIcon::fromTheme("document-print"));

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
        m_toolbar->addAction(m_file_menu_print);
        m_toolbar->addAction(m_file_menu_save);
        m_toolbar->addAction(m_file_menu_save_as);
        m_toolbar->addAction(m_file_menu_quit);

        //initializing statue bar
        m_statusbar = statusBar();

        /************************************************
         *              edit timetable tab              *
         ************************************************/
        //initializing layout
        m_layout_1 = new QHBoxLayout(m_main_edit_timetable);
        m_widget_1_1 = new QGraphicsView;
        m_layout_1_2 = new QVBoxLayout;
        m_layout_1_2_1 = new QHBoxLayout;
        m_layout_1_2_2 = new QTabWidget;
        m_timetable = new QListWidget;
        m_subjects = new QListWidget;

        m_widget_1_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_widget_1_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QSizePolicy policy;
        policy.setHorizontalPolicy(QSizePolicy::Minimum);
        policy.setVerticalPolicy(QSizePolicy::Minimum);
        policy.setHorizontalStretch(4);
        policy.setVerticalStretch(4);
        m_widget_1_1->setSizePolicy(policy);

        m_edit_timetable_id = m_tab->addTab(m_main_edit_timetable, tr("edit timetable"));
        m_layout_1->addWidget(m_widget_1_1);
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

        /*******************************************
         *        generate timetable tab           *
         *******************************************/
        //initializating layout
        m_layout_2 = new QBoxLayout(QBoxLayout::LeftToRight, m_main_generate_timetable);
        m_layout_2_1 = new QTabWidget;
        m_widget_2_1_1 = new QWidget;
        m_layout_2_1_1_1 = new QHBoxLayout(m_widget_2_1_1);
        m_layout_2_1_1_1_1 = new QVBoxLayout;
        m_layout_2_1_1_1_1_2 = new QHBoxLayout;
        m_layout_2_1_1_1_2 = new QVBoxLayout;
        m_layout_2_1_1_1_2_2 = new QHBoxLayout;

        //initializating labels
        m_text_2_1_1_1_1_1 = new QLabel(tr("edit level"));
        m_text_2_1_1_1_1_1->setAlignment(Qt::AlignCenter);
        m_text_2_1_1_1_2_1 = new QLabel(tr("edit subject"));
        m_text_2_1_1_1_2_1->setAlignment(Qt::AlignCenter);

        //create tab
        m_generate_timetable_id = m_tab->addTab(m_main_generate_timetable, tr("generate timetable"));
        m_layout_2_1->setTabPosition(QTabWidget::West);
        m_layout_2_1->addTab(m_widget_2_1_1, tr("define level and subject"));

        //empack layouts
        m_layout_2->addWidget(m_layout_2_1);
        m_widget_2_1_1->setLayout(m_layout_2_1_1_1);
        m_layout_2_1_1_1->addLayout(m_layout_2_1_1_1_1);
        m_layout_2_1_1_1_1->addWidget(m_text_2_1_1_1_1_1);
        m_layout_2_1_1_1_1->addLayout(m_layout_2_1_1_1_1_2);
        m_layout_2_1_1_1->addLayout(m_layout_2_1_1_1_2);
        m_layout_2_1_1_1_2->addWidget(m_text_2_1_1_1_2_1);
        m_layout_2_1_1_1_2->addLayout(m_layout_2_1_1_1_2_2);

        //initializating widgets
        m_add_2_1_1_1_1_2_1 = new QPushButton(tr("add"));
        m_del_2_1_1_1_1_2_2 = new QPushButton(tr("del"));
        m_add_2_1_1_1_2_2_1 = new QPushButton(tr("add"));
        m_del_2_1_1_1_2_2_2 = new QPushButton(tr("del"));
        m_level_2_1_1_1_1_3 = new AsyncListView;
        m_subject_2_1_1_1_2_3 = new AsyncListView;

        //configure widgets
        m_level_2_1_1_1_1_3->setEditTriggers(QAbstractItemView::DoubleClicked);
        m_subject_2_1_1_1_2_3->setEditTriggers(QAbstractItemView::DoubleClicked);

        //empack widget
        m_layout_2_1_1_1_1_2->addWidget(m_add_2_1_1_1_1_2_1);
        m_layout_2_1_1_1_1_2->addWidget(m_del_2_1_1_1_1_2_2);
        m_layout_2_1_1_1_2_2->addWidget(m_add_2_1_1_1_2_2_1);
        m_layout_2_1_1_1_2_2->addWidget(m_del_2_1_1_1_2_2_2);
        m_layout_2_1_1_1_1->addWidget(m_level_2_1_1_1_1_3);
        m_layout_2_1_1_1_2->addWidget(m_subject_2_1_1_1_2_3);
        m_level_2_1_1_1_1_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_subject_2_1_1_1_2_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        //connect signals
        QObject::connect(m_file_menu_open, SIGNAL(triggered()), this, SIGNAL(open_file()));
        QObject::connect(m_file_menu_new, SIGNAL(triggered()), this, SIGNAL(create_file()));
        QObject::connect(m_file_menu_save, SIGNAL(triggered()), this, SIGNAL(save_file()));
        QObject::connect(m_file_menu_save_as, SIGNAL(triggered()), this, SIGNAL(save_as_file()));
        QObject::connect(m_file_menu_print, SIGNAL(triggered()), this, SIGNAL(print_needed()));
        QObject::connect(m_file_menu_quit, SIGNAL(triggered()), this, SLOT(manage_quit_needed()));
        QObject::connect(m_modify_lesson, SIGNAL(clicked()), this, SLOT(draw_modify_pressed()));
        QObject::connect(m_add_lesson, SIGNAL(clicked()), this, SLOT(draw_add_pressed()));
        QObject::connect(m_delete_lesson, SIGNAL(clicked()), this, SLOT(draw_del_pressed()));
        QObject::connect(m_add_2_1_1_1_1_2_1, SIGNAL(clicked()), m_level_2_1_1_1_1_3, SLOT(addItem()));
        QObject::connect(m_level_2_1_1_1_1_3, SIGNAL(editing_finished(AdvencedKeyValue, unsigned int)),
                         this, SIGNAL(update_level(AdvencedKeyValue, unsigned int)));
}

void MainWindow::set_scean(QGraphicsScene* scene)
{
        m_widget_1_1->setScene(scene);
        calcule_scale_factor();
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

void MainWindow::draw_modify_pressed()
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

void MainWindow::draw_add_pressed()
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

void MainWindow::draw_del_pressed()
{
        qDebug( Q_FUNC_INFO );
        KeyValue value_to_return;
        if (m_layout_1_2_2->currentIndex() == m_subjects_id)
        {
               if (m_subjects->currentItem() != NULL)
               {
                      value_to_return.value = m_subjects->currentItem()->text();
                      value_to_return.key = m_subject_items[m_subjects->currentRow()].key;
                      emit del_subject(value_to_return);
               }
        }
        else
        {
                if (m_timetable->currentItem() != NULL)
                {
                        value_to_return.value = m_timetable->currentItem()->text();
                        value_to_return.key = m_timetable_items[m_timetable->currentRow()].key;
                        emit del_timetable(value_to_return);
                }
        }
}

void MainWindow::calcule_scale_factor()
{
        m_widget_1_1->resetTransform();

        int x = m_widget_1_1->size().width();
        int y = m_widget_1_1->size().height();

        qreal x_scale = (qreal) x / (qreal) LENGTH;
        qreal y_scale = (qreal) y / (qreal) HEIGHT;
        m_widget_1_1->scale(x_scale, y_scale);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
        event->accept();
        calcule_scale_factor();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
        if (m_need_to_close)
        {
                event->accept();
        }
        else
        {
                event->ignore();
                manage_quit_needed();
        }
}

void MainWindow::showEvent(QShowEvent* event)
{
        event->accept();
        calcule_scale_factor();
}

void MainWindow::manage_quit_needed()
{
        m_need_to_close = true;
        emit quit_needed();
}

void MainWindow::update_index_level(AdvencedKeyValue item, unsigned int index)
{
        m_level_2_1_1_1_1_3->update_index(item, index);
}
