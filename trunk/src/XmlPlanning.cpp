/*
 * ./XmlPlanning.cpp
 * Copyright (C) 2010 Lameire Alexi
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
#include "XmlPlanning.h"
#include "define.h"

XmlPlanning::XmlPlanning() : m_data_file(this)
{
	m_isopen = false;
	m_isparsed = false;
	qDebug("default constructor XmlPlaning");
}

XmlPlanning::XmlPlanning(QString &filename) : m_data_file(this)
{
	open(filename);
	qDebug("constructor with filename XmlPlanning");
}

void XmlPlanning::open(QString filename)
{
	qDebug("XmlPlanning : method open");
        m_data_file.setFileName(filename);
        if(!m_data_file.open(QIODevice::ReadOnly))
	{
		qDebug("can't open file");
		throw;	
	}
	
	QString error_msg;
	int line;
        if(!m_xml_document.setContent(&m_data_file, &error_msg, &line))
	{
		qDebug("bad contant");
		qDebug(qPrintable(error_msg));
		qDebug("line : %d", line);
                m_data_file.close();
		throw;
	}
	qDebug("good XML parsed");
	qDebug(qPrintable(error_msg));
	qDebug("line : %d", line);
	
	m_isparsed = true;
	qDebug("okey");

        //read done, verifying contraint
	xmlerror error = verify_xsd();
	if (error != NO_ERROR)
	{
		qDebug("bad xsd");
		throw;
	}

        m_root = m_xml_document.documentElement();
	m_lesson_list = m_root.firstChildElement("lesson-list"); 
	m_lesson_id_list = m_root.firstChildElement("lesson-id-list");
	error =	verify_id();
	if (error != NO_ERROR)
	{
		qDebug("bad id");
		throw;
	}
	m_data_file.close();
	qDebug() << Q_FUNC_INFO << " done";
}

xmlerror XmlPlanning::verify_xsd()
{
	qDebug("verify xsd error");
	QUrl xsd_file("file://" + QCoreApplication::applicationDirPath() + "/" + XSD_FILENAME);
	qDebug("file://%s/%s", qPrintable(QCoreApplication::applicationDirPath()), XSD_FILENAME);
	QXmlSchema schema;
	schema.load(xsd_file);

	if (!schema.isValid())
	{
		qDebug("BAD XSD FILE");
		return BAD_XSD_FILE;
	}
	else
	{
		QXmlSchemaValidator validator(schema);
                m_data_file.seek(0);
                if (!validator.validate(&m_data_file, QUrl::fromLocalFile(m_data_file.fileName())))
		{
			qDebug("BOD XSD PARSE");
			return BAD_XSD_PARSE;
		}
		else
		{
			qDebug("NO ERROR");
			return NO_ERROR;
		}
	}
}
xmlerror XmlPlanning::verify_id()
{
	QDomNodeList lesson_list = m_lesson_list.childNodes();
	QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();

	qDebug( Q_FUNC_INFO );
	qDebug() << lesson_list.size();

	for (int i = 0; i != lesson_list.size(); i++)
	{
		bool is_Existant = false;
		QDomElement current_lesson = lesson_list.item(i).toElement();
		unsigned int lesson_associated_id = current_lesson.firstChildElement("id-lesson").text().toUInt();

		for (int j = 0; j != lesson_id_list.size(); i++)
		{
			QDomElement current_id_lesson = lesson_id_list.item(j).toElement();
			unsigned int lesson_current_id = current_id_lesson.firstChildElement("ident").text().toUInt();
			
			if (lesson_current_id == lesson_associated_id)
			{
				is_Existant = true;
				break;
			}
		}
		if (!is_Existant)
		{
			return UNASSOCIETED_ID;
		}
	}
	return NO_ERROR;
}

void XmlPlanning::new_file()
{
	qDebug( Q_FUNC_INFO );

	m_isopen = false;
	m_isparsed = true;

	m_xml_document.clear();
	m_root = m_xml_document.createElement("xml");

	QDomElement version = m_xml_document.createElement("version");
	m_lesson_list = m_xml_document.createElement("lesson-list");
	m_lesson_id_list = m_xml_document.createElement("lesson-id-list");

	m_xml_document.appendChild(m_root);
	m_root.appendChild(version);
	version.appendChild(m_xml_document.createTextNode("1"));
	m_root.appendChild(m_lesson_list);
	m_root.appendChild(m_lesson_id_list);

	qDebug() << qPrintable(m_xml_document.toString(4));
}

void XmlPlanning::refresh_all_view()
{
	qDebug( Q_FUNC_INFO );

	QDomNodeList timetable_id_list = m_lesson_list.childNodes();
	QVector<KeyValue> timetable_list;

	for (int i = 0; i != timetable_id_list.count(); i++)
	{
		QString timetable = timetable_id_list.item(i)
				    .firstChildElement("hour")
				    .firstChild().toText().data();
		unsigned int id = timetable_id_list.item(i)
				  .firstChildElement("ident")
				  .firstChild().toText().data().toUInt();

		qDebug() << "begin 2";
		qDebug(qPrintable(timetable));
		qDebug("%d", id);
		qDebug() << "end 2";

		KeyValue current_item;
		current_item.key = id;
		current_item.value = timetable;
		timetable_list.push_back(current_item);
	}

        emit new_lessons_avalables(get_lessons());
	emit new_timetable_avalable(timetable_list);
}

SubjectData XmlPlanning::search_id(KeyValue id)
{
	qDebug( Q_FUNC_INFO );
	QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();
	SubjectData return_value;

	for (int i = 0; i != lesson_id_list.count(); i++)
	{
		unsigned int current_id = lesson_id_list.item(i)
					  .firstChildElement("ident")
					  .firstChild().toText().data().toUInt();
		if (current_id == id.key)
		{
			return_value.id = current_id;
			return_value.name = lesson_id_list.item(i)
					    .firstChildElement("name")
					    .firstChild().toText().data();
			return_value.teacher = lesson_id_list.item(i)
					       .firstChildElement("teacher")
					       .firstChild().toText().data();
			return_value.id = lesson_id_list.item(i)
					  .firstChildElement("ident")
					  .firstChild().toText().data().toUInt();
			QString color = lesson_id_list.item(i)
					.firstChildElement("color")
					.firstChild().toText().data();
			QString background = lesson_id_list.item(i)
					     .firstChildElement("background")
					     .firstChild().toText().data();
			separe_color(color, return_value.red_text,
				     return_value.green_text,
				     return_value.blue_text);
			separe_color(background, return_value.red_background,
				     return_value.green_background,
				     return_value.blue_background);

			qDebug("begin debug");
			qDebug() << qPrintable(color);
			qDebug() << qPrintable(background);
			qDebug() << return_value.id;
			qDebug("end debug");

			return_value.is_exist = true;
			return return_value;
		}
	}
	return_value.is_exist = false;
	return return_value;
}

Timetable XmlPlanning::search_id_lesson(KeyValue id)
{
	qDebug( Q_FUNC_INFO );
	QDomNodeList lesson_list = m_lesson_list.childNodes();
	Timetable return_value;
	int i;
	for (i = 0; i != lesson_list.size(); i++)
	{
		unsigned int id_tested = lesson_list.item(i).firstChildElement("ident").firstChild()
					.toText().data().toUInt();
		qDebug("id_tested = %d", id_tested);
		if (id_tested == id.key)
		{
			qDebug("id found");
			if (lesson_list.item(i).isNull())
			{
				qDebug("error");
			}

			return_value.ident = id.key;
			return_value.classroom = lesson_list.item(i).firstChildElement("class")
						 .firstChild().toText().data();
			return_value.unparsed_date = lesson_list.item(i)
						     .firstChildElement("hour").firstChild()
						     .toText().data();
			return_value.id_lesson = lesson_list.item(i).firstChildElement("id-lesson")
						 .firstChild().toText().data().toUInt();
			if (lesson_list.item(i).firstChildElement("group").isNull())
			{
				return_value.group = ALL_GROUP;
			}
			else
			{
				int group = lesson_list.item(i).firstChildElement("group")
					    .firstChild().toText().data().toInt();
				switch (group)
				{
					case ALL_GROUP:
						return_value.group = ALL_GROUP;
						break;
					case ONE:
						return_value.group = ONE;
						break;
					case TWO:
						return_value.group = TWO;
						break;
				}
			}

			if (lesson_list.item(i).firstChildElement("week").isNull())
			{
				return_value.week = ALL_WEEK;
			}
			else
			{
				int week = lesson_list.item(i).firstChildElement("week")
					   .firstChild().toText().data().toInt();
				switch (week)
				{
					case ALL_WEEK:
						return_value.week = ALL_WEEK;
						break;
					case PEER:
						return_value.week = PEER;
						break;
					case UNPEER:
						return_value.week = UNPEER;
						break;
				}
			}

                        char half_day;
                        QTextStream stream(return_value.unparsed_date.toAscii());
                        stream >> half_day >> return_value.begin_interval >> return_value.end_interval;
                        //bug here

			if (half_day == 'M')
			{
				return_value.half_day = MORNING;
			}
			else
			{
				return_value.half_day = AFTERNOON;
			}
			return return_value;
		}
	}
	Q_ASSERT(i != lesson_list.size());
	return return_value; //never used only to disable warning
}

void XmlPlanning::separe_color(QString &src, int &red, int &green, int &blue)
{
	red = src.section('.', 0, 0).toInt();
	green = src.section('.', 1, 1).toInt();
	blue = src.section('.', 2, 2).toInt();
}

QString XmlPlanning::join_color(int red, int green, int blue)
{
	return QString(QString::number(red) + "." +
		       QString::number(green) + "." +
		       QString::number(blue));
}

unsigned int XmlPlanning::_get_empty_id(QVector<unsigned int> ids)
{
	qDebug( Q_FUNC_INFO );
	unsigned int selected_id = UINT_MAX;
	unsigned int i;
	for (i = 0; i != (unsigned int) ids.size(); i++)
	{
		if (ids[i] != i)
		{
			selected_id = i;
			break;
		}
	}
	if (selected_id == UINT_MAX)
	{
		selected_id = i + 1;
	}
	qDebug("selected_id : %d", selected_id);

	return selected_id;
}

QVector<unsigned int> XmlPlanning::_all_ident_lesson()
{
	qDebug( Q_FUNC_INFO );
	QDomNodeList idents = m_lesson_list.childNodes();
	QVector<unsigned int> ident_list;

	for (unsigned int i = 0; i != idents.length(); i++)
	{
		unsigned int current_ident = idents.item(i).firstChildElement("ident")
				    .firstChild().toText().data().toUInt();
		ident_list.push_back(current_ident);
	}
	qSort(ident_list);

	return ident_list;
}

QDomElement XmlPlanning::_add_empty_id()
{
	qDebug( Q_FUNC_INFO );

	//creating tree
	QDomElement id = m_xml_document.createElement("id");
	id.appendChild(m_xml_document.createElement("ident"));
	id.appendChild(m_xml_document.createElement("name"));
	id.appendChild(m_xml_document.createElement("teacher"));
	id.appendChild(m_xml_document.createElement("color"));
	id.appendChild(m_xml_document.createElement("background"));

	//creating default node
	id.firstChildElement("name").appendChild(m_xml_document.createTextNode(""));
	id.firstChildElement("teacher").appendChild(m_xml_document.createTextNode(""));
	id.firstChildElement("color").appendChild(m_xml_document.createTextNode("0.0.0"));
	id.firstChildElement("background").appendChild(m_xml_document.createTextNode("0.0.0"));

	//search free id
	QDomNodeList ids = m_lesson_id_list.childNodes();
	QVector<unsigned int> used_id;

	//step one : collect all current id
	for (unsigned int i = 0; i != ids.length(); i++)
	{
		unsigned int current_id = ids.item(i).firstChildElement("ident")
				 .firstChild().toText().data().toUInt();
		used_id.push_back(current_id);
	}

	//step 2 : sorting list
	qSort(used_id);

	//step 3 : get the first id
	unsigned int selected_id = _get_empty_id(used_id);

	//append choice id and id tag
	id.firstChildElement("ident")
	  .appendChild(m_xml_document.createTextNode(QString::number(selected_id)));
	m_lesson_id_list.appendChild(id);
	return id;
}

QDomElement XmlPlanning::_add_empty_lesson()
{
	qDebug( Q_FUNC_INFO );

	//first create basic tree
	QDomElement id = m_xml_document.createElement("lesson");
	id.appendChild(m_xml_document.createElement("ident"));
	id.appendChild(m_xml_document.createElement("hour"));
	id.appendChild(m_xml_document.createElement("class"));
	id.appendChild(m_xml_document.createElement("id-lesson"));
	id.appendChild(m_xml_document.createElement("group"));
	id.appendChild(m_xml_document.createElement("week"));

	//creating default node
	id.firstChildElement("class").appendChild(m_xml_document.createTextNode(""));
	id.firstChildElement("id-lesson").appendChild(m_xml_document.createTextNode(QString::number( UINT_MAX )));
	id.firstChildElement("group").appendChild(m_xml_document.createTextNode("3"));
	id.firstChildElement("week").appendChild(m_xml_document.createTextNode("3"));
	id.firstChildElement("hour").appendChild(m_xml_document.createTextNode("undefined"));

	//get all nodes
	QVector<unsigned int> idents = _all_ident_lesson();

	//search an empty id
	unsigned int selected_id = _get_empty_id(idents);

	id.firstChildElement("ident").appendChild(m_xml_document.createTextNode(QString::number(selected_id)));

	//append new lesson
	m_lesson_list.appendChild(id);
	return id;
}

void XmlPlanning::update_id_lesson(SubjectData data)
{
	qDebug( Q_FUNC_INFO );
	qDebug("begin");

	QDomElement node_to_edit;
	//select node
	if (!data.is_exist)
	{
		node_to_edit = _add_empty_id();
	}
	else
	{
		QDomNodeList list = m_lesson_id_list.childNodes();
		bool is_found = false;
		for (int i = 0; i != list.count(); i++)
		{
			unsigned int current_id = list.item(i).firstChildElement("ident")
						 .firstChild().toText().data().toUInt();
			if (current_id == data.id)
			{
				node_to_edit = list.item(i).toElement();
				is_found = true;
				qDebug("node found");
				break;
			}
		}
		if (!is_found)
		{
			node_to_edit = _add_empty_id();
		}
	}

	QString color;
	node_to_edit.firstChildElement("name").firstChild().toText().setData(data.name);
	node_to_edit.firstChildElement("teacher").firstChild().toText().setData(data.teacher);
	color = join_color(data.red_text, data.green_text, data.blue_text);
	node_to_edit.firstChildElement("color").firstChild().toText().setData(color);
	color = join_color(data.red_background, data.green_background, data.blue_background);
	node_to_edit.firstChildElement("background").firstChild().toText().setData(color);
	qDebug("done");
}

unsigned int XmlPlanning::add_empty_id(QString name)
{
	qDebug( Q_FUNC_INFO );
	QDomElement element = _add_empty_id();
	element.firstChildElement("name").firstChild().toText().setData(name);
	return element.firstChildElement("ident").firstChild().toText().data().toUInt();
}

unsigned int XmlPlanning::add_empty_lesson()
{
	qDebug( Q_FUNC_INFO );
	QDomElement element = _add_empty_lesson();
	return element.firstChildElement("ident").firstChild().toText().data().toUInt();
}

void XmlPlanning::save(QString filename)
{
	m_data_file.setFileName(filename);
	save();
}

void XmlPlanning::save()
{
	qDebug( Q_FUNC_INFO );
	if (!m_data_file.open(QIODevice::WriteOnly))
	{
		qDebug("can't open file to sae");
		throw;
	}
	QByteArray xml = m_xml_document.toByteArray(8);
	qint64 error = m_data_file.write(xml);

	if (error == -1)
	{
		qDebug("an error occure when wrtie file");
		throw;
	}
	m_data_file.close();
}

QVector<KeyValue> XmlPlanning::get_lessons()
{
        QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();
        QVector<KeyValue> lesson_list;

        for (int i = 0; i != lesson_id_list.count(); i++)
        {
                QString lessen = lesson_id_list.item(i)
				 .firstChildElement("name")
				 .firstChild().toText().data();
		unsigned int id = lesson_id_list.item(i)
				  .firstChildElement("ident")
				  .firstChild().toText().data().toUInt();
                qDebug() << "begin";
                qDebug(qPrintable(lessen));
                qDebug("%d", id);
                qDebug() << "done";

                KeyValue current_item;
                current_item.key = id;
                current_item.value = lessen;
                lesson_list.push_back(current_item);
        }
        return lesson_list;
}
