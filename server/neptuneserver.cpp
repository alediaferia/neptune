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
#include "neptuneserver.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIcon>

NeptuneServer::NeptuneServer(QApplication *application) : QObject(application),
                                                          app(application)
{
}

NeptuneServer::~NeptuneServer()
{
}

NeptuneServer* NeptuneServer::instance(QApplication *application)
{
    QString path = QDir::tempPath();
    if (!path.endsWith(QDir::separator())) {
        path.append(QDir::separator());
    }

    QFile locker(path + "neptune_server");
    if (locker.exists()) {
        qDebug() << "cannot run another instance";
        return 0;
    }

    NeptuneServer *server = new NeptuneServer(application);
    server->setLockerPath(path + "neptune_server");
    locker.open(QIODevice::WriteOnly);
    locker.write("Neptune Server");

    return server;
}

void NeptuneServer::killServer()
{
    qDebug() << "test";
//     qDebug() << "an error occurred.. shutting server down..";
//     app->quit();
}

void NeptuneServer::removeLockFile()
{
    QFile locker(m_lockerPath);
    locker.remove();
    qDebug() << "removed " << m_lockerPath;
}

void NeptuneServer::setLockerPath(const QString &path)
{
    m_lockerPath = path;
}

QIcon NeptuneServer::serverIcon()
{
    QIcon sIcon;
    sIcon.addFile(":/icons/server-16x16.png", QSize(16, 16));
    sIcon.addFile(":/icons/server-24x24.png", QSize(24, 24));
    sIcon.addFile(":/icons/server-32x32.png", QSize(32, 32));
    sIcon.addFile(":/icons/server-48x48.png", QSize(48, 48));
    sIcon.addFile(":/icons/server-64x64.png", QSize(64, 64));

    return sIcon;
}

#include "neptuneserver.moc"
