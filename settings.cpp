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

#include "settings.h"
#include "ui_settings.h"


settings::settings( )
{
    setupUi( this );

    connect( btnAdd, SIGNAL(clicked()), this, SLOT(addRow()) );
    connect( btnDel, SIGNAL(clicked()), this, SLOT(delRow()) );
    connect( buttonBox, SIGNAL(accepted()), this, SLOT(save()) );
    connect( buttonBox, SIGNAL(rejected()), this, SLOT(close()) );

    twHosts->setHorizontalHeaderItem( 0, new QTableWidgetItem("Host", QTableWidgetItem::Type) );
    twHosts->setHorizontalHeaderItem( 1, new QTableWidgetItem("Port", QTableWidgetItem::Type) );
    twHosts->setHorizontalHeaderItem( 2, new QTableWidgetItem("Proto", QTableWidgetItem::Type) );
    twHosts->setHorizontalHeaderItem( 3, new QTableWidgetItem("Active", QTableWidgetItem::Type) );
    twHosts->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    twHosts->setColumnCount( 4 );

    configuration = new QSettings( SETTINGS_FILE, QSettings::NativeFormat );
    load( );
}

settings::~settings( )
{
    delete this;
}


void settings::load( )
{
    QString key, hostport;
    QStringList keys, hplist;

    configuration->beginGroup( "QtLogwatcher" );
    cmbLogLevel->setCurrentIndex( cmbLogLevel->findText(configuration->value("Loglevel").toString(),Qt::MatchCaseSensitive) );
    cmbNotifier->setCurrentIndex( cmbNotifier->findText(configuration->value("Notifier").toString(),Qt::MatchCaseSensitive) );
    chkNotifier->setChecked( configuration->value("Enabled").toBool() );
    chkScroll->setChecked( configuration->value("AutoScroll").toBool() );
    chkHidden->setChecked( configuration->value("AutoHide").toBool() );
    chkConnect->setChecked( configuration->value("AutoConnect").toBool() );
    radTray->setChecked( configuration->value("Tray").toBool() );
    radSystem->setChecked( configuration->value("System").toBool() );
    spinTime->setValue( configuration->value("Time").toInt() );
    spinWait->setValue( configuration->value("Wait").toInt() );
    configuration->endGroup( );

    configuration->beginGroup( "Hosts" );
    keys = configuration->childKeys( );
    foreach( key, keys )
    {
        if( key.contains("Host") )
        {
            hostport = configuration->value( key ).toString();
            hplist = hostport.split(":");
            if( hplist.size() == 4 )
            {
                insert( hplist.at(0), hplist.at(1).toInt(), hplist.at(2), hplist.at(3).toInt() );
            }
            else
            {
                qDebug() << "Error in Hostlist" << endl;
            }
        }
    }
    configuration->endGroup( );
}


void settings::save( )
{
    int i;
    QString host, value;

    configuration->beginGroup( "QtLogwatcher" );
    configuration->setValue( "Loglevel", cmbLogLevel->currentText() );
    configuration->setValue( "Notifier", cmbNotifier->currentText() );
    configuration->setValue( "Enabled", chkNotifier->isChecked() );
    configuration->setValue( "AutoScroll", chkScroll->isChecked() );
    configuration->setValue( "AutoHide", chkHidden->isChecked() );
    configuration->setValue( "AutoConnect", chkConnect->isChecked() );
    configuration->setValue( "Tray", radTray->isChecked() );
    configuration->setValue( "System", radSystem->isChecked() );
    configuration->setValue( "Time", spinTime->value() );
    configuration->setValue( "Wait", spinWait->value() );
    configuration->endGroup( );

    configuration->beginGroup( "Hosts" );
    for( i = 0; i < twHosts->rowCount(); i++ )
    {
        host = "Host" + QString::number(i);
        value = twHosts->item( i, 0 )->text()
                + ":" + twHosts->item( i, 1 )->text()
                + ":" + twHosts->item( i, 2 )->text()
                + ":" + twHosts->item( i, 3 )->text();
        configuration->setValue( host, value );
    }
    configuration->endGroup( );

    configuration->sync( );
}

void settings::close( )
{
    qDebug() << "closed Settings" << endl;
}

void settings::addRow( )
{
    twHosts->setRowCount( twHosts->rowCount()+1 );
}

void settings::delRow( )
{
    twHosts->removeRow( twHosts->currentRow() );
}


void settings::insert( QString address, qint16 port, QString proto, qint16 status )
{
    QTableWidgetItem *item;
    twHosts->setRowCount( twHosts->rowCount()+1 );
    item = new QTableWidgetItem( address, 0 );
    twHosts->setItem( twHosts->rowCount()-1, 0, item );
    item = new QTableWidgetItem( QString::number(port), 0 );
    twHosts->setItem( twHosts->rowCount()-1, 1, item );
    item = new QTableWidgetItem( proto, 0 );
    twHosts->setItem( twHosts->rowCount()-1, 2, item );
    item = new QTableWidgetItem( QString::number(status), 0 );
    twHosts->setItem( twHosts->rowCount()-1, 3, item );
}


