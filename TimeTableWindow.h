#ifndef TIMETABLEWINDOW_H
#define TIMETABLEWINDOW_H

#include <QDialog>
#include "ui_TimeTableWindow.h"


class TimeTableWindow : public QDialog, private Ui::TimeTableWindow
{
	Q_OBJECT
	public:
		TimeTableWindow(QWidget *parent = 0);
};

#endif // TIMETABLEWINDOW_H
