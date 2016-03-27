/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2016 Syping
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef SNAPMATICWIDGET_H
#define SNAPMATICWIDGET_H

#include "SnapmaticPicture.h"
#include "ProfileDatabase.h"
#include "DatabaseThread.h"
#include <QWidget>

namespace Ui {
class SnapmaticWidget;
}

class SnapmaticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SnapmaticWidget(ProfileDatabase *profileDB, DatabaseThread *threadDB, QWidget *parent = 0);
    void setSnapmaticPicture(SnapmaticPicture *picture, QString picturePath);
    ~SnapmaticWidget();

private slots:
    void on_cmdView_clicked();

private:
    ProfileDatabase *profileDB;
    DatabaseThread *threadDB;
    Ui::SnapmaticWidget *ui;
    SnapmaticPicture *smpic;
    QString picPath;
};

#endif // SNAPMATICWIDGET_H