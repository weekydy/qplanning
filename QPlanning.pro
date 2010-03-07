# #####################################################################
# ./QPlanning.pro
# Copyright (C) 2010 Lameire Alexis
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QT += xml
QT += xmlpatterns

# Input
HEADERS += src/ontrol.h \
    src/define.h \
    src/MainWindow.h \
    src/XmlPlanning.h \
    src/SubjectDataWindow.h \
    src/SubjectData.h \
    src/TimeTableWindow.h \
    src/KeyValue.h \
    src/TimeTable.h
SOURCES += src/main.cpp \
    src/Control.cpp \
    src/MainWindow.cpp \
    src/XmlPlanning.cpp \
    src/SubjectDataWindow.cpp \
    src/TimeTableWindow.cpp
FORMS += src/SubjectDataWindow.ui \
    src/TimeTableWindow.ui
OTHER_FILES += XmlSpec.xsd \
    COPYING.txt \
    test.xml \
    CMakeList.txt
