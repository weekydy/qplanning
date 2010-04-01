#include "DrawTimetable.h"

DrawTimetable::DrawTimetable(QObject* parent) : QGraphicsScene(parent)
{
        setSceneRect(0, 0, LENGTH, HEIGHT);

        _create_cases();
        _create_labels();
}

void DrawTimetable::_create_cases()
{
        qDebug( Q_FUNC_INFO );
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
        qDebug( Q_FUNC_INFO );
        for (int i = 0; i != cases.size(); i++)
        {
                qDebug("ok");
                int x = LEFT_PER_MIL + COLLUM_PREMITIVE_PER_MIL;
                x += cases[i].timetable.day * 2 * COLLUM_PREMITIVE_PER_MIL;
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
                int l = 2*COLLUM_PREMITIVE_PER_MIL;

                QRect background_timetable(x, y, l, h);

                addRect(background_timetable)->setBrush(
                                               QBrush(
                                               QColor(
                                               cases[i].subject_associated.red_background,
                                               cases[i].subject_associated.green_background,
                                               cases[i].subject_associated.blue_background
                                               )
                                               )
                                               );
        }
}
