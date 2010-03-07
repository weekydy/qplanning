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
#include "Control.h"

Control::Control() : m_windows(), m_config_subject(&m_windows), m_config_timetable(&m_windows)
{
	qDebug( Q_FUNC_INFO );
	m_is_modified = false;
	
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
	QObject::connect(&m_config_subject, SIGNAL(accepted()), this, SLOT(update_xml()));
	QObject::connect(&m_windows, SIGNAL(add_subject()), this, SLOT(add_subject()));
	QObject::connect(&m_windows, SIGNAL(add_timetable()), this, SLOT(add_timetable()));

	m_windows.show();
}

void Control::save_before_changing()
{
	qDebug( Q_FUNC_INFO );
	int reponse = QMessageBox::question(NULL,
		"would you like save",
		"the file have been modified, would you like save it before",
		QMessageBox::Yes,
		QMessageBox::No);
	if (reponse == QMessageBox::Yes)
	{
		//save
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
							"open file",
							"/home",
							"XML files (*.xml)");
	if (!filename.isNull())
	{
		m_config.open(filename);
		m_config.refresh_all_view();
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
}

void Control::show_subject(KeyValue subject)
{
	qDebug( Q_FUNC_INFO );
	SubjectData info = m_config.search_id(subject);
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

	Timetable info = m_config.search_id_lesson(timetable);
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

void Control::update_xml()
{
	SubjectData subject = m_config_subject.get_contant();
	m_config.update_id_lesson(subject);
	m_config.refresh_all_view();
	m_is_modified = true;
}

void Control::add_subject()
{
	unsigned int id = m_config.add_empty_id( DEFAULT_ID_NAME );
	KeyValue id_to_store;
	id_to_store.key = id;
	id_to_store.value = DEFAULT_ID_NAME;
	SubjectData data = m_config.search_id(id_to_store);
	m_config_subject.set_contant(&data);
	m_config_subject.show();
}

void Control::add_timetable()
{
	qDebug( Q_FUNC_INFO );

	unsigned int id = m_config.add_empty_lesson();
	QVector<KeyValue> lesson_list = m_config.get_lessons();

	KeyValue id_to_edit;
	id_to_edit.key = id;
	Timetable data = m_config.search_id_lesson(id_to_edit);

	qDebug("begin info");
	qDebug() << id;
	qDebug() << data.unparsed_date;
	qDebug() << data.group;
	qDebug() << data.week;
	qDebug() << data.id_lesson;
	qDebug("end info");

	m_config_timetable.set_content(data, lesson_list);
	m_config_timetable.show();
}

void Control::manage_save_file()
{
	m_config.save();
	m_is_modified = false;
}

void Control::manage_save_as_file()
{
	QString filename = QFileDialog::getSaveFileName(&m_windows,
							"save file",
							"/home",
							"XML files (*.xml)");
	if (!filename.isNull())
	{
		m_config.save(filename);
		m_is_modified = false;
	}
}
