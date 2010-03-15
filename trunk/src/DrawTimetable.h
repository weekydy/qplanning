#ifndef DRAWTIMETABLE_H
#define DRAWTIMETABLE_H

#include <QGraphicsScene>
#include <QVector>
#include <QRect>
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
		DrawTimetable(QObject *parent = 0);

	private:
		void _create_cases();
};

#endif // DRAWTIMETABLE_H
