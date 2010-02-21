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

#include <QDialog>
#include "SubjectData.h"
#include "ui_SubjectDataWindow.h"
#include <QColorDialog>

class SubjectDataWindow : public QDialog, private Ui::DataWindowModel
{
	Q_OBJECT
	public:
		SubjectDataWindow(QWidget *parent = 0);
		void set_contant(SubjectData *data = 0);
		SubjectData get_contant();

	private:
		QString create_text_label(int red, int green, int blue);
		int m_id;

	public slots:
		void update_text_prevew();
		void update_background_prevew();
		void select_text_color();
		void select_background_color();
};

#endif // SUBJECTDATAWINDOW_H
