#Just-In-Time Logwatcher with a joint venture to the desktopmanagementsystem
#Copyright (C) 2013 Sven Sperner - Bachelor Thesis, FH Frankfurt/Main
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T17:24:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-logwatcher
TEMPLATE = app


SOURCES += main.cpp\
        qtlogwatcher.cpp \
    settings.cpp \
    setserver.cpp

HEADERS  += qtlogwatcher.h \
    settings.h \
    setserver.h

FORMS    += qtlogwatcher.ui \
    settings.ui \
    setserver.ui
