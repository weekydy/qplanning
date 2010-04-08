/*
 * ./QGraphicsItemBoundedText.h
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
#ifndef QGRAPHICSITEMBOUNDEDTEXT_H
#define QGRAPHICSITEMBOUNDEDTEXT_H
///
/// \file QGraphicsItemBoundedText.h
/// \brief declaration of QGraphicsItemBoundedText class
/// \author Lameire Alexis
///

#include <QGraphicsItem>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QRect>

///
/// \class QGraphicsItemBoundedText QGraphicsItemBoundedText.h
/// \brief draw the timetable with data
///
class QGraphicsItemBoundedText : public QGraphicsItem
{
        public:
                ///
                /// \brief default constructor
                ///
                QGraphicsItemBoundedText();
                ///
                /// \brief  surcharged paint method of QGraphicsItem, see Qt docs for more info
                ///
                void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
                ///
                /// \brief set text to paint
                /// \arg text text to draw
                ///
                void setText(QString text);
                ///
                /// \brief set the color to draw
                /// \arg r red composent
                /// \arg g green composent
                /// \arg b blue composent
                ///
                void setColor(int r, int g, int b);
                ///
                /// \brief set the bonding rect
                /// \arg x x left
                /// \arg y y top
                /// \arg w width
                /// \arg h height
                ///
                void setBoundingRect(int x, int y, int w, int h);
                ///
                /// \brief surcharged boundingRect Qt method
                ///
                QRectF boundingRect() const;

        private:
                QString m_text;
                QColor color;
                QRectF bounding_rect;
};

#endif // QGRAPHICSITEMBOUNDEDTEXT_H
