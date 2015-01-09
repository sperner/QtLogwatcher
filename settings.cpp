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

    connect( buttonBox, SIGNAL(accepted()), this, SLOT(save()) );
    connect( buttonBox, SIGNAL(rejected()), this, SLOT(close()) );

    twHosts->setColumnCount( 2 );
    twHosts->setHorizontalHeaderItem( 0, new QTableWidgetItem("Host", QTableWidgetItem::Type) );
    twHosts->setHorizontalHeaderItem( 1, new QTableWidgetItem("Port", QTableWidgetItem::Type) );
    twHosts->horizontalHeader()->setSectionResizeMode( QHeaderView::Interactive );

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
    radioTray->setChecked( configuration->value("Tray").toBool() );
    radioSystem->setChecked( configuration->value("System").toBool() );
    configuration->endGroup( );

    configuration->beginGroup( "Hosts" );
    keys = configuration->childKeys( );
    foreach( key, keys )
    {
        if( key.contains("Host") )
        {
            hostport = configuration->value( key ).toString();
            hplist = hostport.split(":");
            insert( hplist[0], hplist[1].toInt() );
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
    configuration->setValue( "Tray", radioTray->isChecked() );
    configuration->setValue( "System", radioSystem->isChecked() );
    configuration->endGroup( );

    configuration->beginGroup( "Hosts" );
    for( i = 0; i < twHosts->rowCount(); i++ )
    {
        host = "Host" + QString::number(i);
        value = twHosts->item( i, 0 )->text() + ":" + twHosts->item( i, 1 )->text();
        configuration->setValue( host, value );
    }
    configuration->endGroup( );

    configuration->sync( );
}

void settings::close( )
{
    qDebug() << "closed Settings" << endl;
}

void settings::insert( QString address, qint16 port )
{
    QTableWidgetItem *item;
    twHosts->setRowCount( twHosts->rowCount()+1 );
    item = new QTableWidgetItem( address, 0 );
    twHosts->setItem( twHosts->rowCount()-1, 0, item );
    item = new QTableWidgetItem( QString::number(port), 0 );
    twHosts->setItem( twHosts->rowCount()-1, 1, item );
}

void settings::update( QString address, qint16 port )
{
    QTableWidgetItem *item;
    item = new QTableWidgetItem( address, 0 );
    twHosts->setItem( twHosts->currentRow(), 0, item );
    item = new QTableWidgetItem( QString::number(port), 0 );
    twHosts->setItem( twHosts->currentRow(), 1, item );
}


