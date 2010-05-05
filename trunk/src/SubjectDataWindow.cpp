/*
 * ./SubjetDataWindow.cpp
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
/// \file SubjectDataWindow.cpp
/// \brief window to edit subject
/// \author Lameire Alexis
///

#include "SubjectDataWindow.h"
#include "ui_SubjectDataWindow.h"

SubjectDataWindow::SubjectDataWindow(QWidget* parent) : QDialog(parent)
{
        setupUi(this);
        QObject::connect(red_text_color, SIGNAL(valueChanged(int)), this, SLOT(update_text_prevew()));
        QObject::connect(green_text_color, SIGNAL(valueChanged(int)), this, SLOT(update_text_prevew()));
        QObject::connect(blue_text_color, SIGNAL(valueChanged(int)), this, SLOT(update_text_prevew()));
        QObject::connect(red_background_color, SIGNAL(valueChanged(int)), this, SLOT(update_background_prevew()));
        QObject::connect(green_background_color, SIGNAL(valueChanged(int)), this, SLOT(update_background_prevew()));
        QObject::connect(blue_background_color, SIGNAL(valueChanged(int)), this, SLOT(update_background_prevew()));
        QObject::connect(text_color_edit, SIGNAL(pressed()), this, SLOT(select_text_color()));
        QObject::connect(background_color_edit, SIGNAL(pressed()), this, SLOT(select_background_color()));
}

SubjectData SubjectDataWindow::get_contant()
{
        SubjectData content;
        content.name = name_edit->text();
        content.teacher = teacher_edit->text();

        content.red_text = red_text_color->value();
        content.green_text = green_text_color->value();
        content.blue_text = blue_text_color->value();


        content.red_background = red_background_color->value();
        content.green_background = green_background_color->value();
        content.blue_background = blue_background_color->value();

        content.id = m_id;
        if (m_id != UINT_MAX)
        {
                content.is_exist = true;
        }
        else
        {
                content.is_exist = false;
        }
        return content;
}

void SubjectDataWindow::set_contant(SubjectData* data)
{
        if (data == 0)
        {
                name_edit->clear();
                teacher_edit->clear();

                red_text_color->clear();
                green_text_color->clear();
                blue_text_color->clear();

                red_background_color->clear();
                green_background_color->clear();
                blue_background_color->clear();
                m_id = UINT_MAX;
        }
        else
        {
                name_edit->setText(data->name);
                teacher_edit->setText(data->teacher);

                red_text_color->setValue(data->red_text);
                green_text_color->setValue(data->green_text);
                blue_text_color->setValue(data->blue_text);

                red_background_color->setValue(data->red_background);
                green_background_color->setValue(data->green_background);
                blue_background_color->setValue(data->blue_background);
                m_id = data->id;
        }
        update_text_prevew();
        update_background_prevew();
}

void SubjectDataWindow::update_text_prevew()
{
        debug_printf( Q_FUNC_INFO );
        QString color("background-color: rgb(");
        color += QString::number(red_text_color->value());
        color += ", ";
        color += QString::number(green_text_color->value());
        color += ", ";
        color += QString::number(blue_text_color->value());
        color += ");";
        debug_printf(qPrintable(color));
        text_color_prevew->setStyleSheet(color);
}

void SubjectDataWindow::update_background_prevew()
{
        debug_printf( Q_FUNC_INFO );
        QString color ("background-color: rgb(");
        color += QString::number(red_background_color->value());
        color += ", ";
        color += QString::number(green_background_color->value());
        color += ", ";
        color += QString::number(blue_background_color->value());
        color += ");";
        debug_printf(qPrintable(color));
        background_color_prevew->setStyleSheet(color);
}

void SubjectDataWindow::select_text_color()
{
        QColor color(red_text_color->value(),
                     green_text_color->value(),
                     blue_text_color->value());
        QColor new_color = QColorDialog::getColor(color, this);
        int r, g, b;
        new_color.getRgb(&r, &g, &b);

        red_text_color->setValue(r);
        green_text_color->setValue(g);
        blue_text_color->setValue(b);
}

void SubjectDataWindow::select_background_color()
{
        QColor color(red_background_color->value(),
                     green_background_color->value(),
                     blue_background_color->value());
        QColor new_color = QColorDialog::getColor(color, this);
        int r, g, b;
        new_color.getRgb(&r, &g, &b);

        red_background_color->setValue(r);
        green_background_color->setValue(g);
        blue_background_color->setValue(b);

}

void SubjectDataWindow::closeEvent(QCloseEvent* event)
{
        if (isVisible())
        {
                event->ignore();
        }
        else
        {
                event->accept();
        }
}
