#ifndef DRAWTIMETABLE_H
#define DRAWTIMETABLE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLocale>
#include <QVector>
#include <QRect>
#include "define.h"
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

        private:
                ///
                /// \brief create cases of the timetable
                ///
                void _create_cases();
                ///
                /// \brief place the title of collums and rows
                ///
                void _create_labels();
};

#endif // DRAWTIMETABLE_H
