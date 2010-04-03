#include "QGraphicsItemBoundedText.h"

QGraphicsItemBoundedText::QGraphicsItemBoundedText() : color(255,255,255)
{
}

void QGraphicsItemBoundedText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        qDebug( Q_FUNC_INFO );
        int i;
        QFont font = painter->font();
        int font_size = bounding_rect.width();
        if ((font_size * m_text.size()) >= bounding_rect.height())
        {
                font_size = font_size / m_text.size();
        }
        font.setPixelSize(font_size);
        painter->setPen(color);
        painter->setFont(font);
        painter->drawText(bounding_rect, Qt::AlignCenter, m_text, &bounding_rect);
}

void QGraphicsItemBoundedText::setText(QString text)
{
        qDebug( Q_FUNC_INFO );
        m_text = text;
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

void QGraphicsItemBoundedText::setBoundingRect(int x, int y, int h, int l)
{
        bounding_rect.setRect(x, y, l, h);
}

QRectF QGraphicsItemBoundedText::boundingRect() const
{
        return bounding_rect;
}
