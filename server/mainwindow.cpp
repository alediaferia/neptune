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

#include "mainwindow.h"
#include "serverdialog.h"
#include "connectioninfowidget.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTime>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect (ui.scanButton, SIGNAL(clicked()), this, SLOT(slotTryConnection()));
    connect (ui.comboBox->lineEdit(), SIGNAL(returnPressed()), this, SLOT(slotTryConnection()));

    ServerDialog *dialog = new ServerDialog(this);
    connect (ui.actionConfigure_Server, SIGNAL(triggered()), dialog, SLOT(exec()));
}

MainWindow::~MainWindow()
{}

void MainWindow::slotTryConnection()
{
//     ui.textBrowser->append(tr("Connecting..."));
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(ui.comboBox->currentText(), ui.spinBox->value());
//     m_socket->waitForReadyRead();
    connect (m_socket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect (m_socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect (m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect (m_socket, SIGNAL(hostFound()), this, SLOT(slotHostFound()));
    connect (m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotStateChanged(QAbstractSocket::SocketState)));
    connect (m_socket, SIGNAL(readyRead()), this, SLOT(slotRead()));
}

void MainWindow::slotConnected()
{
    ui.textBrowser->append(tr("Connection estabilished."), ConnectionInfoWidget::Good);
}

void MainWindow::slotRead()
{
    ui.textBrowser->append(tr("Available data:"), ConnectionInfoWidget::Normal);
    ui.textBrowser->append(m_socket->readAll(), ConnectionInfoWidget::Normal);
}

void MainWindow::slotDisconnected()
{
    ui.textBrowser->append(tr("Disconnected."), ConnectionInfoWidget::Bad);
}

void MainWindow::slotError(QAbstractSocket::SocketError)
{
    ui.textBrowser->append(tr("An error occurred."), ConnectionInfoWidget::Bad);
}

void MainWindow::slotHostFound()
{
    ui.textBrowser->append(tr("Host found."), ConnectionInfoWidget::Good);
}

void MainWindow::slotStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
        case QAbstractSocket::UnconnectedState :
            ui.textBrowser->append(tr("Not connected."), ConnectionInfoWidget::Normal);
            break;
        case QAbstractSocket::HostLookupState :
            ui.textBrowser->append(tr("Performing hostname lookup..."), ConnectionInfoWidget::Normal);
            break;
        case QAbstractSocket::ConnectingState :
            ui.textBrowser->append(tr("Connecting..."), ConnectionInfoWidget::Normal );
            break;
        case QAbstractSocket::ConnectedState :
            ui.textBrowser->append(tr("Connected to: ") + m_socket->peerAddress().toString() + " [ " + m_socket->peerName() + " ]", ConnectionInfoWidget::Good);
            break;
         default : ;
    }
}
#include "mainwindow.moc" 
