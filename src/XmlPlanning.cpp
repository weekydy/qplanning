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

///
/// \file XmlPlanning.cpp
/// \brief editing xml config file
/// \author Lameire Alexis
///

#include "XmlPlanning.h"
#include "define.h"

XmlPlanning::XmlPlanning() : m_data_file(this)
{
        m_isopen = false;
        m_isparsed = false;
        debug_printf("default constructor XmlPlaning");
}

XmlPlanning::XmlPlanning(QString& filename) : m_data_file(this)
{
        open(filename);
        debug_printf("constructor with filename XmlPlanning");
}

void XmlPlanning::open(QString filename)
{
        debug_printf("XmlPlanning : method open");
        m_data_file.setFileName(filename);
        if (!m_data_file.open(QIODevice::ReadOnly))
        {
                debug_printf("can't open file");
                throw;
        }

        QString error_msg;
        int line;
        if (!m_xml_document.setContent(&m_data_file, &error_msg, &line))
        {
                debug_printf("bad contant");
                debug_printf(qPrintable(error_msg));
                debug_printf("line : %d", line);
                m_data_file.close();
                throw;
        }
        debug_printf("good XML parsed");
        debug_printf(qPrintable(error_msg));
        debug_printf("line : %d", line);

        m_isparsed = true;
        debug_printf("okey");

        //read done, verifying contraint
        xmlerror error = verify_xsd();
        if (error != NO_ERROR)
        {
                debug_printf("bad xsd");
                throw;
        }

        m_root = m_xml_document.documentElement();
        m_lesson_list = m_root.firstChildElement("lesson-list");
        m_lesson_id_list = m_root.firstChildElement("lesson-id-list");
        error = verify_id();
        if (error != NO_ERROR)
        {
                debug_printf("bad id");
                throw;
        }
        m_data_file.close();
}

xmlerror XmlPlanning::verify_xsd()
{
        /*
         * disabling fealure : because sheama.load wount stop
         * http://bugreports.qt.nokia.com/browse/QTBUG-6485
         *

        debug_printf(Q_FUNC_INFO);
        QUrl xsd_file("file://" + XSD_FILENAME);
        QXmlSchema schema;
        schema.load(xsd_file);

        if (!schema.isValid())
        {
                debug_printf("BAD XSD FILE");
                return BAD_XSD_FILE;
        }
        else
        {
                QXmlSchemaValidator validator(schema);
                m_data_file.seek(0);
                if (!validator.validate(&m_data_file, QUrl::fromLocalFile(m_data_file.fileName())))
                {
                        debug_printf("BOD XSD PARSE");
                        return BAD_XSD_PARSE;
                }
                else
                {
                        debug_printf("NO ERROR");
                        return NO_ERROR;
                }
        }
        */
        return NO_ERROR;
}
xmlerror XmlPlanning::verify_id()
{
        QDomNodeList lesson_list = m_lesson_list.childNodes();
        QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();

        debug_printf( Q_FUNC_INFO );
        debug_printf("lesson_list.size() = %d", lesson_list.size());

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
        debug_printf( Q_FUNC_INFO );

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

        debug_printf(qPrintable(m_xml_document.toString(4)));
}

void XmlPlanning::refresh_all_view()
{
        debug_printf( Q_FUNC_INFO );

        emit new_lessons_avalables(get_lessons());
        emit new_timetable_avalable(get_timetables());
}

SubjectData XmlPlanning::search_subject(KeyValue id)
{
        debug_printf( Q_FUNC_INFO );
        SubjectData return_value;
        QDomElement element = _search_subject(id.key);

        return_value.id = id.key;
        return_value.name = element.firstChildElement("name")
                            .firstChild().toText().data();
        return_value.teacher = element.firstChildElement("teacher")
                               .firstChild().toText().data();
        return_value.id = element.firstChildElement("ident")
                          .firstChild().toText().data().toUInt();
        QString color = element.firstChildElement("color")
                        .firstChild().toText().data();
        QString background = element.firstChildElement("background")
                             .firstChild().toText().data();
        separe_color(color, return_value.red_text,
                     return_value.green_text,
                     return_value.blue_text);
        separe_color(background, return_value.red_background,
                     return_value.green_background,
                     return_value.blue_background);

        debug_printf("begin debug");
        debug_printf(qPrintable(color));
        debug_printf(qPrintable(background));
        debug_printf("return_value.id %d", return_value.id);
        debug_printf("end debug");

        return return_value;
}

Timetable XmlPlanning::search_timetable(KeyValue id)
{
        debug_printf( Q_FUNC_INFO );
        QDomElement element_found = _search_timetable(id.key);
        Timetable return_value;
        if (element_found.isNull())
        {
                debug_printf("error");
        }

        return_value.ident = id.key;
        return_value.classroom = element_found.firstChildElement("class")
                                              .firstChild().toText().data();
        return_value.unparsed_date = element_found.firstChildElement("hour")
                                                   .firstChild().toText().data();
        return_value.id_lesson = element_found.firstChildElement("id-lesson")
                                              .firstChild().toText().data().toUInt();
        return_value.day = (Day) element_found.firstChildElement("day")
                                        .firstChild().toText().data().toUInt();
        if (element_found.firstChildElement("group").isNull())
        {
                return_value.group = ALL_GROUP;
        }
        else
        {
                int group = element_found.firstChildElement("group")
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

        if (element_found.firstChildElement("week").isNull())
        {
                return_value.week = ALL_WEEK;
        }
        else
        {
                int week = element_found.firstChildElement("week")
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
        stream >> half_day >> return_value.begin_interval;
        stream.seek(stream.pos() + 2);
        stream >> return_value.end_interval;

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

QDomElement XmlPlanning::_search_timetable(unsigned int id)
{
        QDomNodeList lesson_list = m_lesson_list.childNodes();
        Timetable return_value;
        int i;
        for (i = 0; i != lesson_list.size(); i++)
        {
                unsigned int id_tested = lesson_list.item(i).firstChildElement("ident").firstChild()
                                         .toText().data().toUInt();
                debug_printf("id_tested = %d", id_tested);
                debug_printf("id = %d", id);
                if (id_tested == id)
                {
                        Q_ASSERT(!lesson_list.item(i).isNull());
                        return lesson_list.item(i).toElement();
                }
        }
        throw;
}

QDomElement XmlPlanning::_search_subject(unsigned int id)
{
        QDomNodeList lesson_id_list = m_lesson_id_list.childNodes();

        for (int i = 0; i != lesson_id_list.count(); i++)
        {
                unsigned int current_id = lesson_id_list.item(i)
                                          .firstChildElement("ident")
                                          .firstChild().toText().data().toUInt();
                if (current_id == id)
                {
                        return lesson_id_list.item(i).toElement();
                }
        }
}

void XmlPlanning::separe_color(QString& src, int& red, int& green, int& blue)
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
        debug_printf( Q_FUNC_INFO );
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
        debug_printf("selected_id : %d", selected_id);

        return selected_id;
}

QVector<unsigned int> XmlPlanning::_all_ident_lesson()
{
        debug_printf( Q_FUNC_INFO );
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
        debug_printf( Q_FUNC_INFO );

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
        debug_printf( Q_FUNC_INFO );

        //first create basic tree
        QDomElement id = m_xml_document.createElement("lesson");
        id.appendChild(m_xml_document.createElement("ident"));
        id.appendChild(m_xml_document.createElement("hour"));
        id.appendChild(m_xml_document.createElement("class"));
        id.appendChild(m_xml_document.createElement("id-lesson"));
        id.appendChild(m_xml_document.createElement("group"));
        id.appendChild(m_xml_document.createElement("week"));
        id.appendChild(m_xml_document.createElement("day"));

        //creating default node
        id.firstChildElement("class").appendChild(m_xml_document.createTextNode(""));
        id.firstChildElement("id-lesson").appendChild(m_xml_document.createTextNode(QString::number( UINT_MAX )));
        id.firstChildElement("group").appendChild(m_xml_document.createTextNode("3"));
        id.firstChildElement("week").appendChild(m_xml_document.createTextNode("3"));
        id.firstChildElement("hour").appendChild(m_xml_document.createTextNode("undefined"));
        id.firstChildElement("day").appendChild(m_xml_document.createTextNode("1"));

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
        debug_printf( Q_FUNC_INFO );
        debug_printf("begin");

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
                                debug_printf("node found");
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
        debug_printf("done");
}

void XmlPlanning::update_timetable(Timetable id)
{
        debug_printf( Q_FUNC_INFO );
        QDomElement node_to_edit;
        QDomNodeList list = m_lesson_list.childNodes();
        bool is_found = false;

        for (int i = 0; i != list.count(); i++)
        {
                unsigned int current_id = list.item(i).toElement().firstChildElement("ident")
                                          .firstChild().toText().data().toInt();
                if (current_id == id.ident)
                {
                        node_to_edit = list.item(i).toElement();
                        is_found = true;
                        debug_printf("node found");
                        break;
                }
        }
        if (!is_found)
        {
                _add_empty_lesson();
        }

        node_to_edit.firstChildElement("day").firstChild().toText().setData(QString::number(id.day));
        node_to_edit.firstChildElement("hour").firstChild().toText().setData(id.unparsed_date);
        node_to_edit.firstChildElement("id-lesson").firstChild().toText().setData(QString::number(id.id_lesson));
        node_to_edit.firstChildElement("class").firstChild().toText().setData(id.classroom);
        switch (id.week)
        {
                case ALL_WEEK:
                        node_to_edit.removeChild(node_to_edit.firstChildElement("week"));
                        break;
                default:
                        if (node_to_edit.firstChildElement("week").isNull())
                        {
                                node_to_edit.appendChild(m_xml_document.createElement("week"));
                        }
                        switch (id.week)
                        {
                                case PEER:
                                        node_to_edit.firstChildElement("week").firstChild()
                                        .toText().setData("1");
                                        break;
                                case UNPEER:
                                        node_to_edit.firstChildElement("week").firstChild()
                                        .toText().setData("2");
                                        break;
                        }
                        break;
        }

        switch (id.group)
        {
                case ALL_GROUP:
                        node_to_edit.removeChild(node_to_edit.firstChildElement("group"));
                        break;
                default:
                        if (node_to_edit.firstChildElement("group").isNull())
                        {
                                node_to_edit.appendChild(m_xml_document.createElement("group"));
                        }
                        switch (id.group)
                        {
                                case ONE:
                                        node_to_edit.firstChildElement("group").firstChild()
                                        .toText().setData("1");
                                        break;
                                case TWO:
                                        node_to_edit.firstChildElement("group").firstChild()
                                        .toText().setData("2");
                                        break;
                        }
                        break;
        }
}

void XmlPlanning::del_timetable(KeyValue timetable)
{
        QDomElement element_to_delete = _search_timetable(timetable.key);
        Q_ASSERT(!element_to_delete.isNull());

        element_to_delete.parentNode().removeChild(element_to_delete);
}

void XmlPlanning::del_subject(KeyValue subject)
{
        QDomElement element_to_delete = _search_subject(subject.key);
        Q_ASSERT(!element_to_delete.isNull());

        element_to_delete.parentNode().removeChild(element_to_delete);
}

unsigned int XmlPlanning::add_empty_id(QString name)
{
        debug_printf( Q_FUNC_INFO );
        QDomElement element = _add_empty_id();
        element.firstChildElement("name").firstChild().toText().setData(name);
        return element.firstChildElement("ident").firstChild().toText().data().toUInt();
}

unsigned int XmlPlanning::add_empty_lesson()
{
        debug_printf( Q_FUNC_INFO );
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
        debug_printf( Q_FUNC_INFO );
        if (!m_data_file.open(QIODevice::WriteOnly))
        {
                debug_printf("can't open file to sae");
                throw;
        }
        QByteArray xml = m_xml_document.toByteArray(8);
        qint64 error = m_data_file.write(xml);

        if (error == -1)
        {
                debug_printf("an error occure when wrtie file");
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
                debug_printf("begin");
                debug_printf(qPrintable(lessen));
                debug_printf("%d", id);
                debug_printf("done");

                KeyValue current_item;
                current_item.key = id;
                current_item.value = lessen;
                lesson_list.push_back(current_item);
        }
        return lesson_list;
}

QVector<KeyValue> XmlPlanning::get_timetables()
{
        QDomNodeList timetable_id_list = m_lesson_list.childNodes();
        QVector<KeyValue> timetable_list;
        QLocale locale;

        for (int i = 0; i != timetable_id_list.count(); i++)
        {
                QString timetable = locale.dayName(timetable_id_list.item(i)
                                    .firstChildElement("day")
                                    .firstChild().toText().data().toInt());
                timetable += " ";
                timetable += timetable_id_list.item(i).firstChildElement("hour")
                                              .firstChild().toText().data();
                unsigned int id = timetable_id_list.item(i)
                                  .firstChildElement("ident")
                                  .firstChild().toText().data().toUInt();

                debug_printf("begin 2");
                debug_printf(qPrintable(timetable));
                debug_printf("%d", id);
                debug_printf("end 2");

                KeyValue current_item;
                current_item.key = id;
                current_item.value = timetable;
                timetable_list.push_back(current_item);
        }
        return timetable_list;
}

QVector<Timetable> XmlPlanning::get_full_timetables()
{
        QVector<KeyValue> timetable_list = get_timetables();
        QVector<Timetable> full_timetable_list;
        for (int i = 0; i != timetable_list.size(); i++)
        {
                Timetable timetable_to_add = search_timetable(timetable_list[i]);
                full_timetable_list.push_back(timetable_to_add);
        }
        return full_timetable_list;
}

QVector<SubjectData> XmlPlanning::get_full_subjects()
{
        QVector<KeyValue> lessons_list = get_lessons();
        QVector<SubjectData> full_lessons_list;
        for (int i = 0; i != lessons_list.size(); i++)
        {
                SubjectData subject_to_add = search_subject(lessons_list[i]);
                full_lessons_list.push_back(subject_to_add);
        }
        return full_lessons_list;
}

QString XmlPlanning::get_filename()
{
        return m_filename;
}
