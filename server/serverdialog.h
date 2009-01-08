/***************************************************************************
 *   Copyright (C) 2009 by Alessandro Diaferia <alediaferia@gmail.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 **************************************************************************/

#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include "ui_server.h"
#include "neptuneserver.h"

class QTcpServer;

class ServerDialog : public QDialog
{
    Q_OBJECT
public:
    ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

    void setServer(NeptuneServer *);

private:
    Ui::Server server;
    QTcpServer *m_tcpServer;
    NeptuneServer *m_server;
    QSystemTrayIcon *m_trayIcon;

protected:
    void buildTray();

protected slots:
    void makeServer();
    void incomingConnection();
    void handleSystemTray(QSystemTrayIcon::ActivationReason);

public slots:
    void setSuggestedAddress(const QString &);
};

#endif
