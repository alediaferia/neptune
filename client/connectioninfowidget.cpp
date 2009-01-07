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
#include "connectioninfowidget.h"

#include <QTime>

ConnectionInfoWidget::ConnectionInfoWidget(QWidget *parent) : QTextBrowser(parent)
{
}

ConnectionInfoWidget::~ConnectionInfoWidget()
{}

void ConnectionInfoWidget::append(const QString &string, NotificationState state)
{
    QString time = QTime::currentTime().toString("[hh:mm:ss]") + ' ';
    QString line;
    switch (state) {
        case Good :
            line.append(time + "<b><font color=\"green\">"+ string +"</font></b>");
            break;
        case Normal :
            line.append(time + "<b>"+ string +"</b>");
            break;
        case Bad :
            line.append(time +"<b><font color=\"red\">"+ string +"</font></b>");
            break;
        default : ;
    }
    insertHtml("<br>" + line + "</br>");
}

#include "connectioninfowidget.moc"
