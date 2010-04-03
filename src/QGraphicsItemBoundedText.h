#ifndef QGRAPHICSITEMBOUNDEDTEXT_H
#define QGRAPHICSITEMBOUNDEDTEXT_H
#include <QGraphicsItem>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QRect>

class QGraphicsItemBoundedText : public QGraphicsItem
{
        public:
                QGraphicsItemBoundedText();
                void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
                void setText(QString text);
                void setColor(int r, int g, int b);
                void setBoundingRect(int x, int y, int h, int l);
                QRectF boundingRect() const;

        private:
                QString m_text;
                QColor color;
                QRectF bounding_rect;
};

#endif // QGRAPHICSITEMBOUNDEDTEXT_H
