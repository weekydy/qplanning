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

///
/// \file XmlPlanning.h
/// \brief editing xml config file
/// \author Lameire Alexis
///

#include <QDomDocument>
#include <QObject>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QUrl>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QCoreApplication>
#include <QtDebug>
#include <QStringList>
#include <QVector>
#include <climits>
#include "SubjectData.h"
#include "TimeTable.h"
#include "KeyValue.h"


///
/// \enum xmlerror
/// \brief error list of all error returned
///
enum xmlerror
{
        BAD_XSD_PARSE, ///< the file don't match xsd shemas
        BAD_XSD_FILE, ///< can't use the specified xsd file
        UNASSOCIETED_ID, ///< one ore more ids are unassocieted
        NO_ERROR ///< no errors
};

///
/// \class XmlPlanning XmlPlanning.h
/// \brief editing xml config file
///

class XmlPlanning : public QObject
{
                Q_OBJECT
        public:
                ///
                /// \brief default constructor to create an empty file
                ///
                XmlPlanning();
                ///
                /// \brief constructor with filename
                /// \arg filename path of the file to open
                /// this method create an empty file and after call the open() method
                /// to open file with filename
                ///
                XmlPlanning(QString& filename);
                ///
                /// \brief search an half time that match the id.key
                /// \arg id id to search
                /// \return data collected on the found half time
                ///
                SubjectData search_id(KeyValue id);
                ///
                /// \brief search a subject that match the id.key
                /// \arg id id to search
                /// \return data collected on the found subject
                Timetable search_id_lesson(KeyValue id);

                ///
                /// \brief search the good id referenced and update his info with the content of struct
                /// \arg id struct that contain the id to edit and the data to update
                ///
                void update_id_lesson(SubjectData id);
                ///
                /// \brief search the good id referanced and update his info with the content of struct
                /// \arg id struct that content the id to edit and the data to update
                ///
                void update_timetable(Timetable id);
                ///
                /// \brief create an empty id and set is name to filneme
                /// \arg name name to tell to the new lesson
                /// \return return the ident atributed to the node
                ///
                unsigned int add_empty_id(QString name);
                ///
                /// \brief create an empty half time
                /// \return return the ident atributad to the node
                ///
                unsigned int add_empty_lesson();
                ///
                /// \brief get all lessons avalable
                /// \return return all lesson name and his associated id
                ///
                QVector<KeyValue> get_lessons();
                ///
                /// \brief accessor to get the m_filename private attribut
                /// \return m_filename
                ///
                QString get_filename();

        private:
                ///
                /// \brief verify if all id_lesso are renceced
                /// \return return the error occure durring verifing see xmlerror
                ///
                xmlerror verify_id();
                ///
                /// \brief verify if the file is valid with the xml shemas
                /// \return enumaration of the possible error
                /// this function try to verify if the xml file the xsd validation
                /// if not an error is printed on the console that explane that don't match in the file
                /// and error is returned
                ///
                xmlerror verify_xsd();
                ///
                /// \brief add empty id and set default value
                ///
                QDomElement _add_empty_id();
                ///
                /// \brief add empty half time and set default value
                ///
                QDomElement _add_empty_lesson();
                ///
                /// \brief get all lessons ids to found an empty ud
                /// \return ids founds
                ///
                QVector<unsigned int> _all_ident_lesson();
                ///
                /// \brief search an empty id in unsigned int value in excluding ids
                /// \arg id to exclude
                /// \return id found
                ///
                unsigned int _get_empty_id(QVector<unsigned int> ids);
                ///
                /// \brief separe rgb color formated string
                /// \arg src[int] formated string
                /// \arg red[out] red color ref
                /// \arg green[out] green color ref
                /// \arg blue[out] blue color ref
                ///
                void separe_color(QString& src, int& red, int& green, int& blue);
                ///
                /// \brief join rgb color to create a color formated string
                /// \arg red red color
                /// \arg green green color
                /// \arg blue blue color
                /// \return formated string
                ///
                QString join_color(int red, int green, int blue);

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
                ///
                /// \brief open file
                /// \arg filename filename to open
                ///
                void open(QString filename);
                ///
                /// \brief save file
                ///
                void save();
                ///
                /// \brief save file in a new location pointed by filename
                /// \arg filename path to save
                ///
                void save(QString filename);
                ///
                /// \brief enrase the current file and create a new empty file
                ///
                void new_file();
                ///
                /// \brief call to emit signals to refresh timetable and lessons list
                ///
                void refresh_all_view();

        signals:
                ///
                /// \brief signal to prevent that lessons avalables have changes
                /// \arg lessons new lessons
                ///
                void new_lessons_avalables(QVector<KeyValue> lessons);
                ///
                /// \brief signal to prevent that timetable avalable have changes
                /// \arg timetable new timetables
                ///
                void new_timetable_avalable(QVector<KeyValue> timetable);
};
#endif
