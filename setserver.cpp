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

#include "setserver.h"
#include "ui_setserver.h"


setserver::setserver(QWidget *parent, QString address, qint16 port) : QDialog(parent), ui(new Ui::setserver)
{
    ui->setupUi( this );

    connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()) );
    connect( ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()) );

    if( address != "" )
    {
        ui->linAddress->setText( address );
    }
    if( port != 0 )
    {
        ui->linPort->setText( QString::number(port) );
    }

}

setserver::~setserver( )
{
    delete ui;
}


void setserver::save( )
{
//    this->hide();
}

void setserver::close( )
{
//    this->hide();
}


QString setserver::getAddress( )
{
    return ui->linAddress->text( );
}

qint16 setserver::getPort( )
{
    return ui->linPort->text().toInt( );
}
