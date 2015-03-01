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

#ifndef QTLOGWATCHER_H
#define QTLOGWATCHER_H

#define ICON_ACTIVE "/usr/share/pixmaps/qtlogwatcher_active.png"
#define ICON_INACTIVE "/usr/share/pixmaps/qtlogwatcher_inactive.png"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QHostAddress>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QSslSocket>

#include <settings.h>


namespace Ui {
    class qtlogwatcher;
}

class qtlogwatcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtlogwatcher( QWidget *parent = 0 );
    ~qtlogwatcher( );


private:
    Ui::qtlogwatcher *ui;
    QStatusBar *statusBar;
    QSystemTrayIcon *systrayIcon;
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
    QSslSocket *sslSocket;

    QMenuBar *menuBar;
    QMenu *mainMenu;
    QMenu *systrayMenu;

    QAction *clearAction;
    QAction *connectAction;
    QAction *disconnectAction;
    QAction *quitAction;

    QAction *removeAction;
    QAction *settingsAction;
    QAction *importAction;
    QAction *exportAction;

    settings *settingsDialog;

    void createActions();
    void createMenuBar();
    void createSocket();
    void createStatusBar();
    void createTrayIcon();
    void initTableWidget();


private slots:
    void toggleVisibility();
    void clear();
    void remove();

    void connectToServer();
    void disconnectFromServer();

    void isConnected();
    void isDisconnected();

    void doClientReceive();
    void doClientSend();

    void openSettings();

    void importTable();
    void exportTable();

    void quitProgram();
};


#endif // QTLOGWATCHER_H
