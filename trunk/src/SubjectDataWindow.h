/*
 * ./SubjectDataWindow.h
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
#ifndef SUBJECTDATAWINDOW_H
#define SUBJECTDATAWINDOW_H

///
/// \file SubjectDataWindow.h
/// \brief window to modify subject
/// \author Lameire Alexis
///

#include <QDialog>
#include "SubjectData.h"
#include "ui_SubjectDataWindow.h"
#include <QColorDialog>

///
/// \class SubjectDataWindow SubjectDataWindow.h
/// \brief window to modify subject
///

class SubjectDataWindow : public QDialog, private Ui::DataWindowModel
{
                Q_OBJECT
        public:
                ///
                /// \brief construct a new SubjectDataWindow with parent
                /// \arg parent parent windows of this window
                ///
                SubjectDataWindow(QWidget* parent = 0);
                ///
                /// \brief set contant of window
                /// \arg data data to set, if null an empty window is created
                ///
                void set_contant(SubjectData* data = 0);
                ///
                /// \brief get contant of window if case of modification
                ///
                SubjectData get_contant();

        private:
                unsigned int m_id;

        public slots:
                ///
                /// \brief slot to update the color of the text in the prevew box
                ///
                void update_text_prevew();
                ///
                /// \brief slot to update the background color of the text ine the prevew box
                ///
                void update_background_prevew();
                ///
                /// \brief slot called when color need to be choice for the forgournd of the text
                ///
                void select_text_color();
                ///
                /// \brief slot called when color need to be choice for the background of the text
                ///
                void select_background_color();
};

#endif // SUBJECTDATAWINDOW_H
