/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2016-2017 Syping
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

#include "ProfileDatabase.h"
#include "StandardPaths.h"
#include "config.h"
#include <QFile>
#include <QDir>

ProfileDatabase::ProfileDatabase(QObject *parent) : QObject(parent)
{
    QDir dir;
    dir.mkpath(StandardPaths::dataLocation());
    dir.setPath(StandardPaths::dataLocation());
    QString dirPath = dir.absolutePath();
    QString defaultConfPath = dirPath + QDir::separator() + "players.ini";

    QSettings confPathSettings(GTA5SYNC_APPVENDOR, GTA5SYNC_APPSTR);
    confPathSettings.beginGroup("Database");
    QString confPathFile = confPathSettings.value("Players", defaultConfPath).toString();
    confPathSettings.endGroup();

    profileDB = new QSettings(confPathFile, QSettings::IniFormat);
    profileDB->beginGroup("Players");
}

ProfileDatabase::~ProfileDatabase()
{
    profileDB->endGroup();
    delete profileDB;
}

QStringList ProfileDatabase::getPlayers()
{
    return profileDB->childKeys();
}

QString ProfileDatabase::getPlayerName(int playerID)
{
    return profileDB->value(QString::number(playerID), playerID).toString();
}

void ProfileDatabase::setPlayerName(int playerID, QString playerName)
{
    profileDB->setValue(QString::number(playerID), playerName);
}
