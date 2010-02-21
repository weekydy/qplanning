/*
 * ./XmlPlanning.h
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
#ifndef XMLPLANNING_H
#define XMLPLANNING_H
#include <QDomDocument>
#include <QObject>
#include <QFile>
#include <QString>
#include <QUrl>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QCoreApplication>
#include <QtDebug>
#include <QStringList>
#include "SubjectData.h"

enum xmlerror
{
	BAD_XSD_PARSE,
	BAD_XSD_FILE,
	UNASSOCIETED_ID,
	NO_ERROR
};
class XmlPlanning : public QObject
{
	Q_OBJECT
	public:
		XmlPlanning();
		XmlPlanning(QString &filename);
		SubjectData search_id(QString name);

	private:
		xmlerror verify_id();
		xmlerror verify_xsd();
		void separe_color(QString &src, int &red, int &green, int &blue);

	private:
                QFile m_data_file;
                QDomDocument m_xml_document;
		QDomElement m_root;
		QDomElement m_lesson_list;
		QDomElement m_lesson_id_list;
		QString m_filename;
		bool m_isparsed;
		bool m_isopen;

	public slots:
		void open(QString filename);
		void new_file();
		void refresh_all_view();

	signals:
		void new_lessons_avalables(QStringList lessons);
};
#endif
