#include "DrawTimetable.h"

DrawTimetable::DrawTimetable(QObject* parent) : QGraphicsScene(parent)
{
        setSceneRect(0, 0, 1000, 1000);

        _create_cases();
}

void DrawTimetable::_create_cases()
{
        qDebug( Q_FUNC_INFO );
        QRect border(45, 150, 910, 800);
        QVector<QLine> lines;
        QVector<QLine> collums;

        for (int i = 1; i != 10; i++)
        {
                lines.push_back(QLine(45,
                                      150 + i * 80,
                                      955,
                                      150 + i * 80));
                addLine(lines[i-1]);
        }
        collums.push_back(QLine(45 + 70,
                                150,
                                45 + 70,
                                950
                               ));
        addLine(collums[0]);
        for (int i = 1; i != 7; i++)
        {
                collums.push_back(QLine(45 + 70 + 2 * i * 70,
                                        150,
                                        45 + 70 + 2 * i * 70,
                                        950
                                       ));
                addLine(collums[i-1]);
        }
        addRect(border);
}
