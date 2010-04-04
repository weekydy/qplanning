/*
 * ./QGraphicsItemBoundedText.cpp
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
#include "QGraphicsItemBoundedText.h"
///
/// \file QGraphicsItemBoundedText.cpp
/// \brief implementation of QGraphicsItemBoundedText class
/// \author Lameire Alexis
///

QGraphicsItemBoundedText::QGraphicsItemBoundedText() : color(255,255,255)
{
}

void QGraphicsItemBoundedText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        qDebug( Q_FUNC_INFO );
        if (!m_text.isNull())
        {
                int i;
                QFont font = painter->font();
                int font_size = bounding_rect.height();
                if ((font_size * m_text.size()) >= bounding_rect.width())
                {
                        qDebug("size of string ; %d", m_text.size());
                        qDebug("bounding_rect.width : %d", m_text.size());
                        font_size = bounding_rect.width() / m_text.size();
                        qDebug("font size : %d", font_size);
                }
                font.setPixelSize(font_size);
                painter->setPen(color);
                painter->setFont(font);
                painter->drawText(bounding_rect, Qt::AlignCenter, m_text, &bounding_rect);
        }
}

void QGraphicsItemBoundedText::setText(QString text)
{
        qDebug( Q_FUNC_INFO );
        if (text.isNull())
        {
                qDebug("free ok");
                m_text.clear();
        }
        else
        {
                qDebug("set ok");
                m_text = text;
        }
}

void QGraphicsItemBoundedText::setColor(int r, int g, int b)
{
        qDebug( Q_FUNC_INFO );
        if (r <= 255 && r >= 0)
        {
                if (g <= 255 && g >=0)
                {
                        if (b <= 255 && b >=0)
                        {
                                qDebug("ok");
                                color.setRgb(r, g, b);
                        }
                }
        }
}

void QGraphicsItemBoundedText::setBoundingRect(int x, int y, int w, int h)
{
        bounding_rect.setRect(x, y, w, h);
}

QRectF QGraphicsItemBoundedText::boundingRect() const
{
        return bounding_rect;
}
