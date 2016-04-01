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

#ifndef UIMODLABEL_H
#define UIMODLABEL_H

#include <QWidget>
#include <QLabel>
#include <QString>

class UiModLabel : public QLabel
{
    Q_OBJECT
public:
    UiModLabel(const QString &text, QWidget *parent = 0);
    UiModLabel(QWidget *parent, const QString &text);
    UiModLabel(QWidget *parent = 0);
    ~UiModLabel();

protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);

signals:
    void mouseMoved();
    void mousePressed();
    void mouseReleased();
    void mouseDoubleClicked();
};

#endif // UIMODLABEL_H