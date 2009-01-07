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

#include "serverdialog.h"
#include "connectioninfowidget.h"

#include <QSystemTrayIcon>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

ServerDialog::ServerDialog(QWidget *parent) : QDialog(parent), m_tcpServer(0)
{
    server.setupUi(this);
    connect (server.okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect (server.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect (server.listenButton, SIGNAL(clicked()), this, SLOT(makeServer()));
}

ServerDialog::~ServerDialog()
{
    m_server->removeLockFile();
    delete m_server;
}

void ServerDialog::makeServer()
{
    m_tcpServer = new QTcpServer(this);
    bool status = m_tcpServer->listen(QHostAddress(server.comboBox->currentText()), server.spinBox->value());
    if (!status) {
        server.textBrowser->append(tr("Could not estabilish a server."), ConnectionInfoWidget::Bad);
        return;
    }
    server.textBrowser->append(tr("Server correctly set: ") + m_tcpServer->serverAddress().toString()
                                + tr(" listening on port ")+ QString::number(m_tcpServer->serverPort()) +".", ConnectionInfoWidget::Good);

    connect (m_tcpServer, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
}

void ServerDialog::setSuggestedAddress(const QString &address)
{
    server.comboBox->setEditText(address);
}

void ServerDialog::incomingConnection()
{
    server.textBrowser->append(tr("A new incoming connection estabilished with the server."), ConnectionInfoWidget::Normal);
    m_tcpServer->nextPendingConnection()->write("Welcome!");
}

void ServerDialog::setServer(NeptuneServer *server)
{
    m_server = server;

    QSystemTrayIcon trayIcon(m_server->serverIcon());
    trayIcon.show();
}

#include "serverdialog.moc"
