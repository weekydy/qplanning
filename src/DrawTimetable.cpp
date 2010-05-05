/*
 * ./DrawTimetable.cpp
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
#include "DrawTimetable.h"
///
/// \file DrawTimetable.cpp
/// \brief draw timetable with data of model
/// \author Lameire Alexis
///

DrawTimetable::DrawTimetable(QObject* parent) : QGraphicsScene(parent)
{
        setSceneRect(0, 0, LENGTH, HEIGHT);

        _create_cases();
        _create_labels();
}

void DrawTimetable::_create_cases()
{
        debug_printf( Q_FUNC_INFO );
        setBackgroundBrush(Qt::white);
        QRect border(LEFT_PER_MIL,
                     TOP_PER_MIL,
                     LENGTH - (LEFT_PER_MIL + RIGHT_PER_MIL),
                     HEIGHT - (BOTTOM_PER_MIL + TOP_PER_MIL)
                     );
        QVector<QLine> lines;
        QVector<QLine> collums;

        for (int i = 1; i != 10; i++)
        {
                lines.push_back(QLine(LEFT_PER_MIL,
                                      TOP_PER_MIL + i * ROW_PREMITIVE_PER_MIL,
                                      LENGTH - RIGHT_PER_MIL,
                                      TOP_PER_MIL + i * ROW_PREMITIVE_PER_MIL));
                addLine(lines[i-1]);
        }
        collums.push_back(QLine(LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL,
                                TOP_PER_MIL,
                                LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL,
                                HEIGHT - BOTTOM_PER_MIL
                               ));
        addLine(collums[0]);
        for (int i = 1; i != 7; i++)
        {
                collums.push_back(QLine(LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL * (2*i + 1),
                                        TOP_PER_MIL,
                                        LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL * (2*i + 1),
                                        HEIGHT - BOTTOM_PER_MIL
                                       ));
                addLine(collums[i-1]);
        }
        addRect(border);
}

void DrawTimetable::_create_labels()
{
        QVector<QGraphicsTextItem *> day_label;
        QVector<QGraphicsTextItem *> hour_label;
        QLocale day;
        QFont font;

        font.setBold(true);
        font.setPointSize(16);

        for (int i = 1; i != 7; i++)
        {
                day_label.push_back(addText(
                                            day.dayName(i),
                                            font
                                   )
                                   );

                double x = day_label[i-1]->boundingRect().width();
                double y = day_label[i-1]->boundingRect().height();
                double center_x = ((double)COLLUM_PREMITIVE_PER_MIL * (double) 2 - x )/(double) 2;
                double center_y = ((double)ROW_PREMITIVE_PER_MIL - y)/(double) 2;

                day_label[i-1]->setX(LEFT_PER_MIL + (2*i-1) * COLLUM_PREMITIVE_PER_MIL + center_x);
                day_label[i-1]->setY(TOP_PER_MIL + center_y);

                day_label[i-1]->setDefaultTextColor(Qt::black);
        }

        for (int i = 1; i != 5; i++)
        {
                hour_label.push_back(addText(
                                                tr("M", "Morning") + QString::number(i),
                                                font
                                            )
                                     );

                double x = hour_label[i-1]->boundingRect().width();
                double y = hour_label[i-1]->boundingRect().height();
                double center_x = ((double)COLLUM_PREMITIVE_PER_MIL - x)/(double) 2;
                double center_y = ((double)ROW_PREMITIVE_PER_MIL - y)/(double) 2;

                hour_label[i-1]->setX(LEFT_PER_MIL + center_x);
                hour_label[i-1]->setY(TOP_PER_MIL + i*ROW_PREMITIVE_PER_MIL + center_y);
                hour_label[i-1]->setDefaultTextColor(Qt::black);
        }

        for (int i = 6; i != 10; i++)
        {
                hour_label.push_back(addText(
                                                tr("A", "Afternoon") + QString::number(i-5),
                                                font
                                            )
                                     );

                double x = hour_label[i-2]->boundingRect().width();
                double y = hour_label[i-2]->boundingRect().height();
                double center_x = ((double)COLLUM_PREMITIVE_PER_MIL - x)/(double) 2;
                double center_y = ((double)ROW_PREMITIVE_PER_MIL - y)/(double) 2;

                hour_label[i-2]->setX(LEFT_PER_MIL + center_x);
                hour_label[i-2]->setY(TOP_PER_MIL + i*ROW_PREMITIVE_PER_MIL + center_y);

                hour_label[i-2]->setDefaultTextColor(Qt::black);
        }
}

void DrawTimetable::create_cases(QVector<FullTimetable> cases)
{
        debug_printf( Q_FUNC_INFO );
        _clean_timetable_rect_and_text();
        _create_timetable_rect(cases);
        _draw_text(cases);
}

void DrawTimetable::_create_timetable_rect(QVector<FullTimetable> cases)
{
        debug_printf( Q_FUNC_INFO );
        for (int i = 0; i != cases.size(); i++)
        {
                debug_printf("ok");
                int x = LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL;
                x += (cases[i].timetable.day - 1) * 2 * COLLUM_PREMITIVE_PER_MIL;

                if (cases[i].timetable.week == UNPEER)
                {
                        x += COLLUM_PREMITIVE_PER_MIL;
                }

                int y = TOP_PER_MIL + ROW_PREMITIVE_PER_MIL;
                switch (cases[i].timetable.half_day)
                {
                        case MORNING:
                                y += ROW_PREMITIVE_PER_MIL * cases[i].timetable.begin_interval;
                                break;
                        case AFTERNOON:
                                y += 5 * ROW_PREMITIVE_PER_MIL;
                                y += ROW_PREMITIVE_PER_MIL * cases[i].timetable.begin_interval;
                                break;
                }

                int h = (cases[i].timetable.end_interval - cases[i].timetable.begin_interval) * ROW_PREMITIVE_PER_MIL;
                int w = 2*COLLUM_PREMITIVE_PER_MIL;

                if (cases[i].timetable.week != ALL_WEEK)
                {
                        w /= 2;
                }

                QPolygonF background_timetable;
                switch (cases[i].timetable.group)
                {
                        case ALL_GROUP:
                                background_timetable << QPointF(x, y)
                                                     << QPointF(x + w, y)
                                                     << QPointF(x + w, y + h)
                                                     << QPointF(x, y + h)
                                                     << QPointF(x, y);
                                break;
                        case ONE:
                                background_timetable << QPointF(x, y)
                                                     << QPointF(x + w, y)
                                                     << QPointF(x, y + h)
                                                     << QPointF(x, y);
                                h /= 2;
                                w /= 2;
                                break;
                        case TWO:
                                background_timetable << QPointF(x + w, y)
                                                     << QPointF(x + w, y + h)
                                                     << QPointF(x, y + h)
                                                     << QPointF(x + w, y);
                                h /= 2;
                                w /= 2;
                                x += w;
                                y += h;
                                break;
                }

                RectData current_rect;
                current_rect.item = addPolygon(background_timetable);
                current_rect.item->setBrush(
                                               QBrush(
                                               QColor(
                                               cases[i].subject_associated.red_background,
                                               cases[i].subject_associated.green_background,
                                               cases[i].subject_associated.blue_background
                                               )
                                               )
                                       );
                current_rect.x = x;
                current_rect.y = y;
                current_rect.h = h;
                current_rect.w = w;
                m_timetable_rect.push_back(current_rect);
        }
}

void DrawTimetable::_clean_timetable_rect_and_text()
{
        for (int i = 0; i != m_timetable_rect.size(); i++)
        {
                removeItem(m_timetable_rect[i].item);
                removeItem(m_all_lesson[i]);
                removeItem(m_all_class[i]);
                removeItem(m_all_teacher[i]);
                delete m_timetable_rect[i].item;
                delete m_all_lesson[i];
                delete m_all_class[i];
                delete m_all_teacher[i];
        }
        m_timetable_rect.clear();
        m_all_lesson.clear();
        m_all_class.clear();
        m_all_teacher.clear();
}

void DrawTimetable::_draw_text(QVector<FullTimetable> cases)
{
        debug_printf( Q_FUNC_INFO );

        for (int i = 0; i != m_timetable_rect.size(); i++)
        {
               m_all_lesson.push_back(new QGraphicsItemBoundedText);
               m_all_lesson[i]->setColor(cases[i].subject_associated.red_text,
                                    cases[i].subject_associated.green_text,
                                    cases[i].subject_associated.blue_text);
               m_all_lesson[i]->setText(cases[i].subject_associated.name);
               m_all_lesson[i]->setBoundingRect(m_timetable_rect[i].x,
                                           m_timetable_rect[i].y,
                                           m_timetable_rect[i].w,
                                           m_timetable_rect[i].h/3);
               debug_printf("first bounding rect");

               m_all_class.push_back(new QGraphicsItemBoundedText);
               m_all_class[i]->setColor(cases[i].subject_associated.red_text,
                                      cases[i].subject_associated.green_text,
                                      cases[i].subject_associated.blue_text);
               m_all_class[i]->setText(cases[i].timetable.classroom);
               m_all_class[i]->setBoundingRect(m_timetable_rect[i].x,
                                             m_timetable_rect[i].y + m_timetable_rect[i].h/3,
                                             m_timetable_rect[i].w,
                                             m_timetable_rect[i].h/3);
               debug_printf("second bounding rect");

               m_all_teacher.push_back(new QGraphicsItemBoundedText);
               m_all_teacher[i]->setColor(cases[i].subject_associated.red_text,
                                        cases[i].subject_associated.green_text,
                                        cases[i].subject_associated.blue_text);
               m_all_teacher[i]->setText(cases[i].subject_associated.teacher);
               m_all_teacher[i]->setBoundingRect(m_timetable_rect[i].x,
                                               m_timetable_rect[i].y + (m_timetable_rect[i].h * 2)/3,
                                               m_timetable_rect[i].w,
                                               m_timetable_rect[i].h/3);
               debug_printf("last bounding rect");

               addItem(m_all_lesson[i]);
               addItem(m_all_class[i]);
               addItem(m_all_teacher[i]);
               debug_printf("set items");
        }
}
