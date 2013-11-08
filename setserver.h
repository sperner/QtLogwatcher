/*
Just-In-Time Logwatcher with a joint venture to the desktopmanagementsystem
Copyright (C) 2013 Sven Sperner - Bachelor Thesis, FH Frankfurt/Main

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SETSERVER_H
#define SETSERVER_H

#include <QDialog>

#include "settings.h"
#include "ui_setserver.h"


namespace Ui {
    class setserver;
}

class setserver : public QDialog
{
    Q_OBJECT
    
public:
    explicit setserver(QWidget *parent = 0, QString address = "", qint16 port = 0);
    ~setserver();

    QString getAddress();
    qint16 getPort();

    
private:
    Ui::setserver *ui;


private slots:
    void save();
    void close();

};


#endif // SETSERVER_H
