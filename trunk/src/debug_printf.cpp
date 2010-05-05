/*
 * ./debug_printf.cpp
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
#include "debug_printf.h"
///
/// \file debug_printf.cpp
/// \brief debuging fealure
/// \author Lameire Alexis
///


void debug_printf(const char* format, ...)
{
        void* functions[1000];
        int size = backtrace(functions, 1000);
        char** data = backtrace_symbols(functions, size);
        int correct_count = 0;

        for (int i = 0; i != size; i++)
        {
                QString current_data = data[i];
                if (current_data.contains(QCoreApplication::applicationFilePath()) && !current_data.contains("qt_metacall"))
                {
                        correct_count++;
                }
        }
        correct_count -= 2;
        QString string(correct_count, QChar('>'));
        string += " ";
        string += format;

        va_list ap;
        va_start(ap, format);
        string.vsprintf(qPrintable(string), ap);
        qDebug(qPrintable(string));
        va_end(ap);
}
