/*
 * ./main.cpp
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
#include <QApplication>
#include <QObject>
#include <QTranslator>
#include "SubjectDataWindow.h"
#include "XmlPlanning.h"
#include "Control.h"
#include "define.h"
#include "debug_printf.h"

int main(int argc, char** argv)
{
        QApplication app(argc, argv);


        QString locale = QLocale::system().name().section('_', 0, 0);
        QTranslator translator;
        debug_printf("locale = %s", qPrintable(locale));
        QString path = QM_FILES + QString("/QPlanning_") + locale;
        debug_printf(qPrintable(path));
        bool result = translator.load("QPlanning_" + locale, QM_FILES);
        //Q_ASSERT(result);
        app.installTranslator(&translator);

        Control controler;
        return app.exec();
}
