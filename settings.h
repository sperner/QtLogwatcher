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

#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS_FILE "/etc/qtlogwatcher.conf"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QTableWidget>

#include "ui_settings.h"


namespace Ui {
    class settings;
}

class settings : public QDialog, public Ui::settings
{
    Q_OBJECT

public:
    settings();
    ~settings();


private:
    QSettings *configuration;

    void load();
    void insert(QString address, qint16 port, QString proto, qint16 status);


private slots:
    void save();
    void close();
    void addRow();
    void delRow();

};


#endif // SETTINGS_H
