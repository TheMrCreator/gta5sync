/******************************************************************************
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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QList>
#include <QDialog>
#include <QSettings>
#include <QTreeWidgetItem>
#include "ProfileDatabase.h"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(ProfileDatabase *profileDB, QWidget *parent = 0);
    void commitProfiles(QStringList profiles);
    ~OptionsDialog();

private slots:
    void on_cmdOK_clicked();

signals:
    void settingsApplied(int contentMode, QString language);

private:
    ProfileDatabase *profileDB;
    Ui::OptionsDialog *ui;
    QList<QTreeWidgetItem*> playerItems;
    QString currentLanguage;
    QString defaultProfile;
    QSettings *settings;
    int contentMode;
    void setupTreeWidget();
    void setupLanguageBox();
    void setupRadioButtons();
    void setupDefaultProfile();
    void applySettings();
};

#endif // OPTIONSDIALOG_H
