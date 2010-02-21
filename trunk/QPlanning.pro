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
HEADERS += Control.h \
    define.h \
    MainWindow.h \
    XmlPlanning.h \
    SubjectDataWindow.h \
    SubjectData.h
SOURCES += main.cpp \
    Control.cpp \
    MainWindow.cpp \
    XmlPlanning.cpp \
    SubjectDataWindow.cpp
FORMS += SubjectDataWindow.ui
OTHER_FILES += XmlSpec.xsd \
    COPYING.txt
