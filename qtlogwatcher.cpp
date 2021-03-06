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

#include "qtlogwatcher.h"
#include "ui_qtlogwatcher.h"


qtlogwatcher::qtlogwatcher(QWidget *parent) : QMainWindow(parent), ui(new Ui::qtlogwatcher)
{
    ui->setupUi(this);

    connect( ui->btnClear, SIGNAL(clicked()), this, SLOT(clear()) );
    connect( ui->btnConnect, SIGNAL(clicked()), this, SLOT(connectToServer()) );
    connect( ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(disconnectFromServer()) );
    connect( ui->btnSend, SIGNAL(clicked()), this, SLOT(doClientSend()) );

    settingsDialog = new settings;

    createActions( );
    createMenuBar( );
    createStatusBar( );
    createTrayIcon( );
    initTableWidget( );

    if( settingsDialog->chkConnect->isChecked() )
    {
        connectToServer( );
    }
}

qtlogwatcher::~qtlogwatcher( )
{
    delete ui;
}


void qtlogwatcher::createActions( )
{
    clearAction = new QAction( "Clear", this );
    connectAction = new QAction( "Connect", this );
    disconnectAction = new QAction( "Diconnect", this );
    quitAction = new QAction( "Quit", this );

    removeAction = new QAction( "Delete", this );
    settingsAction = new QAction( "Settings", this );
    importAction = new QAction( "Import", this );
    exportAction = new QAction( "Export", this );

    connect( clearAction, SIGNAL(triggered()), this, SLOT(clear()) );
    connect( connectAction, SIGNAL(triggered()), this, SLOT(connectToServer()) );
    connect( disconnectAction, SIGNAL(triggered()), this, SLOT(disconnectFromServer()) );
    connect( quitAction, SIGNAL(triggered()), this, SLOT(quitProgram()) );

    connect( removeAction, SIGNAL(triggered()), this, SLOT(remove()) );
    connect( settingsAction, SIGNAL(triggered()), this, SLOT(openSettings()) );
    connect( importAction, SIGNAL(triggered()), this, SLOT(importTable()) );
    connect( exportAction, SIGNAL(triggered()), this, SLOT(exportTable()) );
}

void qtlogwatcher::createMenuBar( )
{
    menuBar = QMainWindow::menuBar( );

    mainMenu = new QMenu( menuBar );
    mainMenu->addAction( clearAction );
    mainMenu->addSeparator( );
    mainMenu->addAction( connectAction );
    mainMenu->addAction( disconnectAction );
    mainMenu->addSeparator( );
    mainMenu->addAction( quitAction );
    mainMenu->setTitle( "File" );
    menuBar->addMenu( mainMenu );

    mainMenu = new QMenu( menuBar );
    mainMenu->addAction( removeAction );
    mainMenu->addSeparator( );
    mainMenu->addAction( importAction );
    mainMenu->addAction( exportAction );
    mainMenu->addSeparator( );
    mainMenu->addAction( settingsAction );
    mainMenu->setTitle( "Edit" );
    menuBar->addMenu( mainMenu );
}

void qtlogwatcher::createStatusBar( )
{
    statusLabel = new QLabel;
    statusLabel->setText( "ready" );
    statusBar = QMainWindow::statusBar( );
    statusBar->addPermanentWidget( statusLabel );
}

void qtlogwatcher::createTrayIcon( )
{
    systrayMenu = new QMenu( this );
    systrayMenu->addAction( connectAction );
    systrayMenu->addAction( disconnectAction );
    systrayMenu->addAction( settingsAction );
    systrayMenu->addAction( quitAction );

    systrayIcon = new QSystemTrayIcon( this );
    systrayIcon->setContextMenu( systrayMenu );
    if( settingsDialog->chkHidden->isChecked() )
    {
        systrayIcon->setIcon( QIcon(ICON_INACTIVE) );
    }
    else
    {
        systrayIcon->setIcon( QIcon(ICON_ACTIVE) );
    }
    systrayIcon->show( );
    connect( systrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)) , this, SLOT(toggleVisibility()) );
}

void qtlogwatcher::initTableWidget( )
{
    ui->twMessages->setColumnCount( 4 );
    ui->twMessages->setHorizontalHeaderItem( 0, new QTableWidgetItem("Type", QTableWidgetItem::Type) );
    ui->twMessages->setHorizontalHeaderItem( 1, new QTableWidgetItem("Host", QTableWidgetItem::Type) );
    ui->twMessages->setHorizontalHeaderItem( 2, new QTableWidgetItem("File", QTableWidgetItem::Type) );
    ui->twMessages->setHorizontalHeaderItem( 3, new QTableWidgetItem("Message", QTableWidgetItem::Type) );
    ui->twMessages->horizontalHeader()->setStretchLastSection( true );
}


void qtlogwatcher::toggleVisibility( )
{
    if( this->isVisible() )
    {
        this->hide( );
        systrayIcon->setIcon( QIcon(ICON_INACTIVE) );
    }
    else
    {
        this->show( );
        systrayIcon->setIcon( QIcon(ICON_ACTIVE) );
    }
}

void qtlogwatcher::clear( )
{
    ui->txtInput->clear( );
    ui->twMessages->clear( );
    ui->twMessages->setRowCount( 0 );
    initTableWidget( );
}

void qtlogwatcher::remove( )
{
    ui->twMessages->removeRow( ui->twMessages->currentRow() );
}


void qtlogwatcher::connectToServer( )
{
    int i;
    for( i = 0; i < settingsDialog->twHosts->rowCount(); i++ )
    {
        if( settingsDialog->twHosts->item( i, 3 )->text().toInt() == 1 )
        {
            if( settingsDialog->twHosts->item( i, 2 )->text().compare( "tcp" ) == 0 )
            {
                QTcpSocket* tcpSocket = new QTcpSocket();
                socketList.append( tcpSocket );
                connect( tcpSocket, SIGNAL(connected()), this, SLOT(updateState()) );
                connect( tcpSocket, SIGNAL(disconnected()), this, SLOT(updateState()) );
                connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(doClientReceive()) );
                tcpSocket->connectToHost( settingsDialog->twHosts->item( i, 0 )->text(),
                                          settingsDialog->twHosts->item( i, 1 )->text().toInt() );
            }
            else if( settingsDialog->twHosts->item( i, 2 )->text().compare( "udp" ) == 0 )
            {
                QUdpSocket* udpSocket = new QUdpSocket();
                socketList.append( udpSocket );
                connect( udpSocket, SIGNAL(connected()), this, SLOT(updateState()) );
                connect( udpSocket, SIGNAL(disconnected()), this, SLOT(updateState()) );
                connect( udpSocket, SIGNAL(readyRead()), this, SLOT(doClientReceive()) );
                udpSocket->connectToHost( settingsDialog->twHosts->item( i, 0 )->text(),
                                          settingsDialog->twHosts->item( i, 1 )->text().toInt() );
            }
            else if( settingsDialog->twHosts->item( i, 2 )->text().compare( "ssl" ) == 0 )
            {
                QSslSocket* sslSocket = new QSslSocket();
                socketList.append( sslSocket );
                connect( sslSocket, SIGNAL(connected()), this, SLOT(updateState()) );
                connect( sslSocket, SIGNAL(disconnected()), this, SLOT(updateState()) );
                connect( sslSocket, SIGNAL(readyRead()), this, SLOT(doClientReceive()) );
                sslSocket->connectToHostEncrypted( settingsDialog->twHosts->item( i, 0 )->text(),
                                          settingsDialog->twHosts->item( i, 1 )->text().toInt() );
            }
        }
    }
}

void qtlogwatcher::disconnectFromServer( )
{
    for( int i = socketList.size()-1; i >= 0 ; i-- )
    {
        socketList.takeAt(i)->disconnectFromHost();
    }
}


void qtlogwatcher::updateState( )
{
    QString message = "";
    for( int i = 0; i < socketList.size(); i++ )
    {
        if( socketList.at(i)->state() == QAbstractSocket::ConnectedState )
        {
            message += socketList.at(i)->peerName() + ":up; ";
        }
        else
        {
            message += socketList.at(i)->peerName() + ":down; ";
        }
    }
    if( message == "" )
    {
        statusBar->setStyleSheet( "QLabel { color : red; }" );
        message = "Not connected";
    }
    else
    {
        statusBar->setStyleSheet( "QLabel { color : green; }" );
    }
    statusLabel->setText( message );
}


void qtlogwatcher::doClientReceive( )
{
    QString type, host, file, message;
    QTableWidgetItem *item;

    for( int x = 0; x < socketList.size(); x++ )
    {
        QString stream( socketList.at(x)->readAll( ) );
        QStringList msgList = stream.split("|!|");

        for( int y = 0; y < msgList.size(); y++ )
        {
            QStringList wordList = msgList[y].split("|:|");

            for( int z = 0; z < wordList.size()-2; z = z + 3 )
            {
                type = wordList.at( z );
                host = socketList.at(x)->peerAddress().toString() + ":"
                     + QString::number( socketList.at(x)->peerPort() );
                file = wordList.at( z+1 );
                message = wordList.at( z+2 );

                if( settingsDialog->cmbLogLevel->currentIndex() >= type.toInt() )
                {
                    ui->twMessages->setRowCount( ui->twMessages->rowCount() + 1 );
                    item = new QTableWidgetItem( type, 0 );
                    ui->twMessages->setItem( ui->twMessages->rowCount()-1, 0, item );
                    item = new QTableWidgetItem( host, 0 );
                    ui->twMessages->setItem( ui->twMessages->rowCount()-1, 1, item );
                    item = new QTableWidgetItem( file, 0 );
                    ui->twMessages->setItem( ui->twMessages->rowCount()-1, 2, item );
                    item = new QTableWidgetItem( message, 0 );
                    ui->twMessages->setItem( ui->twMessages->rowCount()-1, 3, item );

                    if( settingsDialog->chkScroll->isChecked() )
                    {
                        ui->twMessages->scrollToBottom( );
                    }
                }

                if( settingsDialog->chkNotifier->isChecked() && settingsDialog->cmbNotifier->currentIndex() >= type.toInt() )
                {
                    if( z > 0 )
                    {
                        QThread::sleep( settingsDialog->spinWait->value() );
                    }
                    if( type.toInt() < 4 )
                    {
                        systrayIcon->showMessage( host + " - " + file, message, QSystemTrayIcon::Critical , settingsDialog->spinTime->value() * 1000 );
                    }
                    else if( type.toInt() == 4 )
                    {
                        systrayIcon->showMessage( host + " - " + file, message, QSystemTrayIcon::Warning , settingsDialog->spinTime->value() * 1000 );
                    }
                    else if( type.toInt() > 4 )
                    {
                        systrayIcon->showMessage( host + " - " + file, message, QSystemTrayIcon::Information , settingsDialog->spinTime->value() * 1000 );
                    }
                }
                /*
                 TODO: System-Notifier (KNotify) or Tray-Icon-Notification (systrayIcon)
                */
            }
        }

        ui->txtInput->appendPlainText( stream );
    }
}

void qtlogwatcher::doClientSend( )
{
    /*
        TODO: Multiple Hosts
    */
//    if( tcpSocket->isWritable() )
//    {
//        tcpSocket->write( ui->txtOutput->toPlainText().toUtf8().constData(), ui->txtOutput->toPlainText().toUtf8().length() );
//    }
}


void qtlogwatcher::openSettings( )
{
    settingsDialog->show();
}

void qtlogwatcher::importTable( )
{
    QString filename = QFileDialog::getOpenFileName( );
    QFile importFile( filename );

    if( importFile.open(QFile::ReadOnly) )
    {
        QString data = importFile.readAll( );
        QStringList rowList = data.split( "\n" );
        QStringList singleRow;
        QTableWidgetItem *item;

        for( int row = 0; row < rowList.size(); row++ )
        {
            singleRow = rowList.at(row).split( ";" );
            if( singleRow.size() == 4 )
            {
                ui->twMessages->setRowCount( ui->twMessages->rowCount() + 1 );
                for( int column = 0; column < singleRow.size(); column++ )
                {
                    item = new QTableWidgetItem( singleRow[column], 0 );
                    ui->twMessages->setItem( ui->twMessages->rowCount()-1, column, item );
                }
            }
        }
        importFile.close( );
    }
}

void qtlogwatcher::exportTable( )
{
    QString filename = QFileDialog::getSaveFileName( );
    QFile exportFile( filename );

    if( exportFile.open(QFile::WriteOnly) )
    {
        QTextStream data( &exportFile );
        QStringList rowList;

        for( int row = 0; row < ui->twMessages->rowCount(); row++ )
        {
            rowList.clear();
            for( int column = 0; column < ui->twMessages->columnCount(); column++ )
            {
                rowList << ui->twMessages->item(row, column)->text( );
            }
            data << rowList.join( ";" );
        }
        exportFile.close( );
    }
}


bool qtlogwatcher::getStartHidden( )
{
    return settingsDialog->chkHidden->isChecked();
}


void qtlogwatcher::quitProgram( )
{
    QApplication::quit( );
}
