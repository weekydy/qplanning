/*
 * ./Control.cpp
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
/// \file Control.cpp
/// \brief manage communication bitwin veuws and models
/// \author Lameire Alexis
///

#include "Control.h"

Control::Control() : m_windows(), m_config_subject(&m_windows), m_config_timetable(&m_windows), m_timetable_veuw(&m_windows)
{
        qDebug( Q_FUNC_INFO );
        m_is_modified = false;
        m_windows.set_scean(&m_timetable_veuw);


        QObject::connect(&m_windows, SIGNAL(open_file()), this, SLOT(manage_open_file()));
        QObject::connect(&m_windows, SIGNAL(create_file()), this, SLOT(manage_create_file()));
        QObject::connect(&m_windows, SIGNAL(save_file()), this, SLOT(manage_save_file()));
        QObject::connect(&m_windows, SIGNAL(save_as_file()), this, SLOT(manage_save_as_file()));
        QObject::connect(&m_config, SIGNAL(new_lessons_avalables(QVector<KeyValue>)),
                         &m_windows, SLOT(update_all_lessons(QVector<KeyValue>)));
        QObject::connect(&m_config, SIGNAL(new_timetable_avalable(QVector<KeyValue>)),
                         &m_windows, SLOT(update_all_timetable(QVector<KeyValue>)));
        QObject::connect(&m_windows, SIGNAL(modify_subject(KeyValue)),
                         this, SLOT(show_subject(KeyValue)));
        QObject::connect(&m_windows, SIGNAL(modify_timetable(KeyValue)),
                         this, SLOT(show_timetable(KeyValue)));
        QObject::connect(&m_config_subject, SIGNAL(accepted()), this, SLOT(update_subject()));
        QObject::connect(&m_config_timetable, SIGNAL(accepted()), this, SLOT(update_timetable()));
        QObject::connect(&m_windows, SIGNAL(add_subject()), this, SLOT(add_subject()));
        QObject::connect(&m_windows, SIGNAL(add_timetable()), this, SLOT(add_timetable()));
        QObject::connect(&m_windows, SIGNAL(del_timetable(KeyValue)), this, SLOT(del_timetable(KeyValue)));
        QObject::connect(&m_windows, SIGNAL(del_subject(KeyValue)), this, SLOT(del_subject(KeyValue)));
        QObject::connect(&m_windows, SIGNAL(quit_needed()), this, SLOT(manage_quit()));

        manage_create_file();
        m_windows.show();
}

void Control::save_before_changing()
{
        qDebug( Q_FUNC_INFO );
        int reponse = QMessageBox::question(NULL,
                                            tr("would you like save"),
                                            tr("the file have been modified, would you like save it before"),
                                            QMessageBox::Yes,
                                            QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
                m_config.save();
        }
}

void Control::manage_open_file()
{
        qDebug( Q_FUNC_INFO );
        if (m_is_modified)
        {
                save_before_changing();
        }
        QString filename = QFileDialog::getOpenFileName(&m_windows,
                           tr("open file"),
                           "/home",
                           "XML files (*.xml)");
        if (!filename.isNull())
        {
                m_config.open(filename);
                _update_all_veuw();
        }
}

void Control::manage_create_file()
{
        qDebug( Q_FUNC_INFO );
        if (m_is_modified)
        {
                save_before_changing();
        }
        m_config.new_file();
        m_is_modified = false;
}

void Control::show_subject(KeyValue subject)
{
        qDebug( Q_FUNC_INFO );
        SubjectData info = m_config.search_subject(subject);
        qDebug() << "begin info list";
        qDebug() << qPrintable(info.name);
        qDebug() << qPrintable(info.teacher);
        qDebug("%d.%d.%d", info.red_text, info.green_text, info.blue_text);
        qDebug("%d.%d.%d", info.red_background, info.green_background, info.blue_background);
        qDebug() << "end info list";
        m_config_subject.set_contant(&info);
        m_config_subject.show();
}

void Control::show_timetable(KeyValue timetable)
{
        qDebug( Q_FUNC_INFO );
        qDebug() << "timetable info list";
        qDebug() << timetable.key;
        qDebug() << qPrintable(timetable.value);
        qDebug() << "end timetable info list";

        Timetable info = m_config.search_timetable(timetable);
        QVector<KeyValue> lesson_list = m_config.get_lessons();

        qDebug() << "begin info list";
        qDebug() << qPrintable(info.unparsed_date);
        qDebug() << qPrintable(info.classroom);
        qDebug() << info.ident;
        qDebug() << info.id_lesson; //
        qDebug("%f", info.begin_interval);
        qDebug("%f", info.end_interval);
        qDebug() << "end info list";

        m_config_timetable.set_content(info, lesson_list);
        m_config_timetable.show();
}

void Control::update_subject()
{
        SubjectData subject = m_config_subject.get_contant();
        m_config.update_id_lesson(subject);
        _update_all_veuw();
        m_is_modified = true;
}

void Control::update_timetable()
{
        qDebug( Q_FUNC_INFO );
        Timetable timetable = m_config_timetable.get_content();
        m_config.update_timetable(timetable);
        _update_all_veuw();
        m_is_modified = true;
}

void Control::add_subject()
{
        unsigned int id = m_config.add_empty_id( DEFAULT_ID_NAME );
        KeyValue id_to_store;
        id_to_store.key = id;
        id_to_store.value = DEFAULT_ID_NAME;
        SubjectData data = m_config.search_subject(id_to_store);
        m_config_subject.set_contant(&data);
        m_config_subject.show();
        m_is_modified = true;
}

void Control::add_timetable()
{
        qDebug( Q_FUNC_INFO );
        QVector<KeyValue> lesson_list = m_config.get_lessons();

        if (lesson_list.isEmpty())
        {
                QMessageBox::warning(&m_windows,
                                     tr("warning"),
                                     tr("you cant add a timetable if you don't have lessons"));
        }
        else
        {
                unsigned int id = m_config.add_empty_lesson();
                KeyValue id_to_edit;
                id_to_edit.key = id;
                Timetable data = m_config.search_timetable(id_to_edit);

                qDebug("begin info");
                qDebug() << id;
                qDebug() << data.unparsed_date;
                qDebug() << data.group;
                qDebug() << data.week;
                qDebug() << data.id_lesson;
                qDebug("end info");

                m_config_timetable.set_content(data, lesson_list);
                m_config_timetable.show();
                m_is_modified = true;
        }
}

void Control::del_subject(KeyValue subject)
{
        bool delete_file = false;
        bool operate_cancel = false;
        QVector<Timetable> all_lesson = m_config.get_full_timetables();

        for (int i = 0;i != all_lesson.size(); i++)
        {
                if (all_lesson[i].id_lesson == subject.key)
                {
                        int result;
                        if (!delete_file)
                        {
                                QLocale locale;
                                QString sentence = tr("this subject is referenced on ");
                                sentence += locale.dayName(all_lesson[i].day);
                                sentence += " ";
                                sentence += all_lesson[i].unparsed_date;
                                sentence += tr(" would you like to delete it ?");
                                result = QMessageBox::question(&m_windows,
                                                               tr("conflict detected"),
                                                               sentence,
                                                               QMessageBox::Yes
                                                               | QMessageBox::YesAll
                                                               | QMessageBox::No
                                                               );
                        }
                        if (result == QMessageBox::No)
                        {
                                operate_cancel = true;
                                break;
                        }
                        else
                        {
                                KeyValue element_to_del;
                                element_to_del.key = all_lesson[i].ident;
                                m_config.del_timetable(element_to_del);
                                if (result == QMessageBox::YesAll)
                                {
                                        delete_file = true;
                                }
                        }
                }
        }
        if (!operate_cancel)
        {
                m_config.del_subject(subject);
        }
        _update_all_veuw();
}

void Control::del_timetable(KeyValue timetable)
{
        qDebug( Q_FUNC_INFO );
        int confirm = QMessageBox::question(&m_windows,
                                            tr("confirm deleting"),
                                            tr("would you like delete this timetable"),
                                            QMessageBox::Yes,
                                            QMessageBox::No);
        if (confirm == QMessageBox::Yes)
        {
                qDebug( "okey : save" ),
                m_config.del_timetable(timetable);
                _update_all_veuw();
        }
}

void Control::manage_save_file()
{
        qDebug( Q_FUNC_INFO );
        if (m_config.get_filename().isNull())
        {
                manage_save_as_file();
        }
        else
        {
                m_config.save();
        }
        m_is_modified = false;
}

void Control::manage_save_as_file()
{
        QString filename = QFileDialog::getSaveFileName(&m_windows,
                           tr("save file"),
                           "/home",
                           "XML files (*.xml)");
        if (!filename.isNull())
        {
                m_config.save(filename);
                m_is_modified = false;
        }
}

void Control::manage_quit()
{
        qDebug( Q_FUNC_INFO );
        if (m_is_modified)
        {
                save_before_changing();
        }
        m_windows.close();
        m_config_timetable.close();
        m_config_subject.close();
        qApp->quit();
}

QVector<FullTimetable> Control::create_full_timetable()
{
        qDebug( Q_FUNC_INFO );
        QVector<Timetable> all_timetable = m_config.get_full_timetables();
        QVector<SubjectData> all_subject = m_config.get_full_subjects();
        QVector<FullTimetable> full_timetable;
        bool id_found = false;

        for (int i = 0; i != all_timetable.size(); i++)
        {
                FullTimetable current_full_timetable;
                current_full_timetable.timetable = all_timetable[i];
                for (int j = 0; j != all_subject.size(); j++)
                {
                        qDebug("current_full_timetable.timetable.id_lesson = %d",
                               current_full_timetable.timetable.id_lesson);
                        qDebug("all_subject[j].id = %d",
                               all_subject[j].id);
                        if (current_full_timetable.timetable.id_lesson == all_subject[j].id)
                        {
                                current_full_timetable.subject_associated = all_subject[j];
                                full_timetable.push_back(current_full_timetable);
                                id_found = true;
                                qDebug("ok");
                                break;
                        }
                }
                Q_ASSERT(id_found);
        }
        return full_timetable;
}

void Control::_update_all_veuw()
{
        m_config.refresh_all_view();
        m_timetable_veuw.create_cases(create_full_timetable());
}
