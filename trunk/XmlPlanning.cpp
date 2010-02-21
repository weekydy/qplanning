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
		int lesson_associated_id = current_lesson.firstChildElement("id-lesson").text().toInt();

		for (int j = 0; j != lesson_id_list.size(); i++)
		{
			QDomElement current_id_lesson = lesson_id_list.item(j).toElement();
			int lesson_current_id = current_id_lesson.firstChildElement("ident").text().toInt();
			
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

	QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();
	QStringList list;

	for (int i = 0; i != lesson_id_list.count(); i++)
	{
		QString element = lesson_id_list.item(i)
				  .firstChildElement("name")
				  .firstChild().toText().data();
		qDebug() << "begin";
		qDebug(qPrintable(element));
		qDebug() << "done";
		list << element;
	}
	emit new_lessons_avalables(list);
}

SubjectData XmlPlanning::search_id(QString name)
{
	qDebug( Q_FUNC_INFO );
	QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();
	SubjectData return_value;

	for (int i = 0; i != lesson_id_list.count(); i++)
	{
		QString current_name = lesson_id_list.item(i)
			       .firstChildElement("name")
			       .firstChild().toText().data();
		if (current_name == name)
		{
			return_value.name = current_name;
			return_value.teacher = lesson_id_list.item(i)
					       .firstChildElement("teacher")
					       .firstChild().toText().data();
			return_value.id = lesson_id_list.item(i)
					  .firstChildElement("ident")
					  .firstChild().toText().data().toInt();
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

void XmlPlanning::separe_color(QString &src, int &red, int &green, int &blue)
{
	red = src.section('.', 0, 0).toInt();
	green = src.section('.', 1, 1).toInt();
	blue = src.section('.', 2, 2).toInt();
}
