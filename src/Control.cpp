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
        debug_printf( Q_FUNC_INFO );
        m_is_modified = false;
        m_windows.set_scean(&m_timetable_veuw);


        QObject::connect(&m_windows, SIGNAL(open_file()), this, SLOT(manage_open_file()));
        QObject::connect(&m_windows, SIGNAL(create_file()), this, SLOT(manage_create_file()));
        QObject::connect(&m_windows, SIGNAL(save_file()), this, SLOT(manage_save_file()));
        QObject::connect(&m_windows, SIGNAL(save_as_file()), this, SLOT(manage_save_as_file()));
        QObject::connect(&m_xml_config, SIGNAL(new_lessons_avalables(QVector<KeyValue>)),
                         &m_windows, SLOT(update_all_lessons(QVector<KeyValue>)));
        QObject::connect(&m_xml_config, SIGNAL(new_timetable_avalable(QVector<KeyValue>)),
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
        QObject::connect(&m_windows, SIGNAL(print_needed()), this, SLOT(print_timetable()));
        QObject::connect(&m_windows, SIGNAL(update_level(AdvencedKeyValue, unsigned int)),
                         this, SLOT(update_level(AdvencedKeyValue, unsigned int)));
        QObject::connect(&m_windows, SIGNAL(del_level(AdvencedKeyValue)), this, SLOT(del_level(AdvencedKeyValue)));

        manage_create_file();
        m_windows.show();
}

void Control::save_before_changing()
{
        debug_printf( Q_FUNC_INFO );
        int reponse = QMessageBox::question(NULL,
                                            tr("would you like save"),
                                            tr("the file have been modified, would you like save it before"),
                                            QMessageBox::Yes,
                                            QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
                m_xml_config.save();
        }
}

void Control::manage_open_file()
{
        debug_printf( Q_FUNC_INFO );
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
                m_xml_config.open(filename);
                _update_all_view();
        }
}

void Control::manage_create_file()
{
        debug_printf( Q_FUNC_INFO );
        if (m_is_modified)
        {
                save_before_changing();
        }
        m_xml_config.new_file();
        m_is_modified = false;
}

void Control::show_subject(KeyValue subject)
{
        debug_printf( Q_FUNC_INFO );
        SubjectData info = m_xml_config.search_subject(subject);
        debug_printf("begin info list");
        debug_printf(qPrintable(info.name));
        debug_printf(qPrintable(info.teacher));
        debug_printf("%d.%d.%d", info.red_text, info.green_text, info.blue_text);
        debug_printf("%d.%d.%d", info.red_background, info.green_background, info.blue_background);
        debug_printf("end info list");
        m_config_subject.set_contant(&info);
        m_config_subject.show();
}

void Control::show_timetable(KeyValue timetable)
{
        debug_printf( Q_FUNC_INFO );
        debug_printf("timetable info list");
        debug_printf("timetable.key = %d", timetable.key);
        debug_printf("timetable.value = %s", qPrintable(timetable.value));
        debug_printf("end timetable info list");

        Timetable info = m_xml_config.search_timetable(timetable);
        QVector<KeyValue> lesson_list = m_xml_config.get_lessons();

        debug_printf("begin info list");
        debug_printf("info.unparsed_data = %s", qPrintable(info.unparsed_date));
        debug_printf("info.classroom = %s", qPrintable(info.classroom));
        debug_printf("info.indent = %d", info.ident);
        debug_printf("info.id_lesson = %d", info.id_lesson);
        debug_printf("info.begin_interval = %f", info.begin_interval);
        debug_printf("info.end_interval = %f", info.end_interval);
        debug_printf("end info list");

        m_config_timetable.set_content(info, lesson_list);
        m_config_timetable.show();
}

void Control::update_subject()
{
        SubjectData subject = m_config_subject.get_contant();
        m_xml_config.update_id_lesson(subject);
        _update_all_view();
        m_is_modified = true;
}

void Control::update_timetable()
{
        debug_printf( Q_FUNC_INFO );
        Timetable timetable = m_config_timetable.get_content();
        m_xml_config.update_timetable(timetable);
        _update_all_view();
        m_is_modified = true;
}

void Control::add_subject()
{
        unsigned int id = m_xml_config.add_empty_id( DEFAULT_ID_NAME );
        KeyValue id_to_store;
        id_to_store.key = id;
        id_to_store.value = DEFAULT_ID_NAME;
        SubjectData data = m_xml_config.search_subject(id_to_store);
        m_config_subject.set_contant(&data);
        m_config_subject.show();
        m_is_modified = true;
}

void Control::add_timetable()
{
        debug_printf( Q_FUNC_INFO );
        QVector<KeyValue> lesson_list = m_xml_config.get_lessons();

        if (lesson_list.isEmpty())
        {
                QMessageBox::warning(&m_windows,
                                     tr("warning"),
                                     tr("you cant add a timetable if you don't have lessons"));
        }
        else
        {
                unsigned int id = m_xml_config.add_empty_lesson();
                KeyValue id_to_edit;
                id_to_edit.key = id;
                Timetable data = m_xml_config.search_timetable(id_to_edit);

                debug_printf("begin info");
                debug_printf("id = %d", id);
                debug_printf("data.unparsed_data = %s", qPrintable(data.unparsed_date));
                debug_printf("data.group = %d", data.group);
                debug_printf("data.week = %d", data.week);
                debug_printf("data.id_lesson = %d", data.id_lesson);
                debug_printf("end info");

                m_config_timetable.set_content(data, lesson_list);
                m_config_timetable.show();
                m_is_modified = true;
        }
}

void Control::del_subject(KeyValue subject)
{
        bool delete_file = false;
        bool operate_cancel = false;
        QVector<Timetable> all_lesson = m_xml_config.get_full_timetables();

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
                                m_xml_config.del_timetable(element_to_del);
                                if (result == QMessageBox::YesAll)
                                {
                                        delete_file = true;
                                }
                        }
                }
        }
        if (!operate_cancel)
        {
                m_xml_config.del_subject(subject);
        }
        _update_all_view();
}

void Control::del_timetable(KeyValue timetable)
{
        debug_printf( Q_FUNC_INFO );
        int confirm = QMessageBox::question(&m_windows,
                                            tr("confirm deleting"),
                                            tr("would you like delete this timetable"),
                                            QMessageBox::Yes,
                                            QMessageBox::No);
        if (confirm == QMessageBox::Yes)
        {
                debug_printf( "okey : save" ),
                m_xml_config.del_timetable(timetable);
                _update_all_view();
        }
}

void Control::manage_save_file()
{
        debug_printf( Q_FUNC_INFO );
        if (m_xml_config.get_filename().isNull())
        {
                manage_save_as_file();
        }
        else
        {
                m_xml_config.save();
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
                m_xml_config.save(filename);
                m_is_modified = false;
        }
}

void Control::manage_quit()
{
        debug_printf( Q_FUNC_INFO );
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
        debug_printf( Q_FUNC_INFO );
        QVector<Timetable> all_timetable = m_xml_config.get_full_timetables();
        QVector<SubjectData> all_subject = m_xml_config.get_full_subjects();
        QVector<FullTimetable> full_timetable;
        bool id_found = false;

        for (int i = 0; i != all_timetable.size(); i++)
        {
                FullTimetable current_full_timetable;
                current_full_timetable.timetable = all_timetable[i];
                for (int j = 0; j != all_subject.size(); j++)
                {
                        debug_printf("current_full_timetable.timetable.id_lesson = %d",
                               current_full_timetable.timetable.id_lesson);
                        debug_printf("all_subject[j].id = %d",
                               all_subject[j].id);
                        if (current_full_timetable.timetable.id_lesson == all_subject[j].id)
                        {
                                current_full_timetable.subject_associated = all_subject[j];
                                full_timetable.push_back(current_full_timetable);
                                id_found = true;
                                debug_printf("ok");
                                break;
                        }
                }
                Q_ASSERT(id_found);
        }
        return full_timetable;
}

void Control::_update_all_view()
{
        m_xml_config.refresh_all_view();
        m_timetable_veuw.create_cases(create_full_timetable());
}

void Control::print_timetable()
{
        debug_printf( Q_FUNC_INFO );

        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Landscape);
        printer.setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);

        QPrintDialog *dialog = new QPrintDialog(&printer, &m_windows);
        dialog->setWindowTitle(tr("Print Document"));
        if (dialog->exec() == QDialog::Accepted)
        {
                QPainter page(&printer);
                page.setTransform(QTransform::fromScale(1.41421356, 1)); //sqrt(2);
                m_timetable_veuw.render(&page);
        }
}
