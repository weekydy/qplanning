/*
 * ./DrawTimetable.h
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
#ifndef DRAWTIMETABLE_H
#define DRAWTIMETABLE_H
///
/// \file DrawTimetable.h
/// \brief draw timetable with data of model
/// \author Lameire Alexis
///


#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QLocale>
#include <QVector>
#include <QRect>
#include <QPolygonF>
#include <QPainter>
#include "define.h"
#include "FullTimetable.h"
#include "QGraphicsItemBoundedText.h"
///
/// \struct RectData;
/// \brief store rect and his coordonies
///
struct RectData
{
        int x;
        int y;
        int w;
        int h;
        QGraphicsPolygonItem* item;
};


///
/// \class DrawTimetable DrawTimetable.h
/// \brief draw the timetable with data
///
class DrawTimetable : public QGraphicsScene
{
                Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
                DrawTimetable(QObject* parent = 0);

                ///
                /// \brief creates cases
                /// \arg cases cases to draw
                ///
                void create_cases(QVector<FullTimetable> cases);
        private:
                ///
                /// \brief create cases of the timetable
                ///
                void _create_cases();
                ///
                /// \brief place the title of collums and rows
                ///
                void _create_labels();
                ///
                /// \brief create all timetable rect
                ///
                void _create_timetable_rect(QVector<FullTimetable> cases);
                ///
                /// \brief clean previous rect
                ///
                void _clean_timetable_rect_and_text();
                ///
                /// \brief draw the text into rect
                /// \arg cases data to add in cases
                ///
                void _draw_text(QVector<FullTimetable> cases);

        private:
                QVector<RectData> m_timetable_rect;
                QVector<QGraphicsItemBoundedText *> m_all_lesson;
                QVector<QGraphicsItemBoundedText *> m_all_class;
                QVector<QGraphicsItemBoundedText *> m_all_teacher;
};

#endif // DRAWTIMETABLE_H
