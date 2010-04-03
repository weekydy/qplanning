#ifndef DRAWTIMETABLE_H
#define DRAWTIMETABLE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLocale>
#include <QVector>
#include <QRect>
#include <QPainter>
#include "define.h"
#include "FullTimetable.h"
#include "QGraphicsItemBoundedText.h"
///
/// \struct RectData;
/// \brief store rect and his coordonies
struct RectData
{
        int x;
        int y;
        int h;
        int l;
        QGraphicsRectItem* item;
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
                void _clean_timetable_rect();
                ///
                /// \brief draw the text into text
                ///
                void _draw_text(QVector<FullTimetable> cases);

        private:
                QVector<RectData> m_timetable_rect;
};

#endif // DRAWTIMETABLE_H
