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

#include "SnapmaticWidget.h"
#include "ui_SnapmaticWidget.h"
#include "SnapmaticPicture.h"
#include "DatabaseThread.h"
#include "PictureDialog.h"
#include "PictureExport.h"
#include "PictureCopy.h"
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QMenu>
#include <QFile>

SnapmaticWidget::SnapmaticWidget(ProfileDatabase *profileDB, DatabaseThread *threadDB, QWidget *parent) :
    ProfileWidget(parent), profileDB(profileDB), threadDB(threadDB),
    ui(new Ui::SnapmaticWidget)
{
    ui->setupUi(this);
    ui->cmdView->setVisible(false);
    ui->cmdCopy->setVisible(false);
    ui->cmdExport->setVisible(false);
    ui->cmdDelete->setVisible(false);
    ui->cbSelected->setVisible(false);

    QPalette palette;
    highlightBackColor = palette.highlight().color();
    highlightTextColor = palette.highlightedText().color();

    clkIssued = 0;
    picPath = "";
    picStr = "";
    smpic = 0;

    installEventFilter(this);
}

SnapmaticWidget::~SnapmaticWidget()
{
    delete ui;
}

bool SnapmaticWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == this)
    {
        if (ev->type() == QEvent::Enter)
        {
            setStyleSheet(QString("QFrame#SnapmaticFrame{background-color: rgb(%1, %2, %3)}QLabel#labPicStr{color: rgb(%4, %5, %6)}").arg(QString::number(highlightBackColor.red()), QString::number(highlightBackColor.green()), QString::number(highlightBackColor.blue()), QString::number(highlightTextColor.red()), QString::number(highlightTextColor.green()), QString::number(highlightTextColor.blue())));
            return true;
        }
        else if(ev->type() == QEvent::Leave)
        {
            setStyleSheet("");
            return true;
        }
    }
    return false;
}

void SnapmaticWidget::setSnapmaticPicture(SnapmaticPicture *picture, QString picturePath)
{
    smpic = picture;
    picPath = picturePath;
    picStr = picture->getPictureStr();
    picTitl = picture->getPictureTitl();

    QPixmap SnapmaticPixmap = QPixmap::fromImage(picture->getPicture(), Qt::AutoColor);
    SnapmaticPixmap.scaled(ui->labPicture->width(), ui->labPicture->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labPicStr->setText(picStr + "\n" + picTitl + "");
    ui->labPicture->setPixmap(SnapmaticPixmap);
}

void SnapmaticWidget::setSnapmaticPicture(SnapmaticPicture *picture)
{
    setSnapmaticPicture(picture, picture->getPictureFileName());
}

void SnapmaticWidget::on_cmdView_clicked()
{
    PictureDialog *picDialog = new PictureDialog(profileDB, this);
    picDialog->setWindowFlags(picDialog->windowFlags()^Qt::WindowContextHelpButtonHint);
    picDialog->setSnapmaticPicture(smpic, picPath, true);
    picDialog->setModal(true);

    // be ready for playerName updated
    QObject::connect(threadDB, SIGNAL(playerNameUpdated()), picDialog, SLOT(playerNameUpdated()));
    QObject::connect(picDialog, SIGNAL(nextPictureRequested()), this, SLOT(dialogNextPictureRequested()));
    QObject::connect(picDialog, SIGNAL(previousPictureRequested()), this, SLOT(dialogPreviousPictureRequested()));

    // show picture dialog
    picDialog->showNormal();
    picDialog->setMinimumSize(picDialog->size());
    picDialog->setMaximumSize(picDialog->size());
    picDialog->exec();
    delete picDialog;
}

void SnapmaticWidget::on_cmdCopy_clicked()
{
    PictureCopy::copyPicture(this, picPath);
}

void SnapmaticWidget::on_cmdExport_clicked()
{
    PictureExport::exportPicture(this, smpic);
}

void SnapmaticWidget::on_cmdDelete_clicked()
{
    int uchoice = QMessageBox::question(this, tr("Delete picture"), tr("Are you sure to delete %1 from your Snapmatic pictures?").arg("\""+picStr+"\""), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (uchoice == QMessageBox::Yes)
    {
        if (!QFile::exists(picPath))
        {
            emit pictureDeleted();
        }
        else if(QFile::remove(picPath))
        {
            emit pictureDeleted();
        }
        else
        {
            QMessageBox::warning(this, tr("Delete picture"), tr("Failed at deleting %1 from your Snapmatic pictures").arg("\""+picStr+"\""));
        }
    }
}

void SnapmaticWidget::mousePressEvent(QMouseEvent *ev)
{
    ProfileWidget::mousePressEvent(ev);
}

void SnapmaticWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    ProfileWidget::mouseReleaseEvent(ev);
    if (ui->cbSelected->isVisible())
    {
        if (rect().contains(ev->pos()) && ev->button() == Qt::LeftButton)
        {
            clkIssued = false;
            //QTimer::singleShot(QApplication::doubleClickInterval(), this, SLOT(changeCheckedState()));
            ui->cbSelected->setChecked(!ui->cbSelected->isChecked());
        }
    }
    else
    {
        if (rect().contains(ev->pos()) && ev->button() == Qt::LeftButton)
        {
            on_cmdView_clicked();
        }
    }
}

void SnapmaticWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    QWidget::mouseDoubleClickEvent(ev);

    //  if (ev->button() == Qt::LeftButton)
    //  {
    //      clkIssued = true;
    //      on_cmdView_clicked();
    //  }
}

void SnapmaticWidget::changeCheckedState()
{
    if (!clkIssued)
    {
        ui->cbSelected->setChecked(!ui->cbSelected->isChecked());
    }
}

void SnapmaticWidget::setSelected(bool isSelected)
{
    ui->cbSelected->setChecked(isSelected);
}

void SnapmaticWidget::pictureSelected()
{
    setSelected(!ui->cbSelected->isChecked());
}

void SnapmaticWidget::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu contextMenu(this);
    QMenu exportMenu(tr("&Export"), this);
    exportMenu.addAction(tr("Export as &JPG picture..."), this, SLOT(on_cmdExport_clicked()));
    exportMenu.addAction(tr("Export as &GTA Snapmatic..."), this, SLOT(on_cmdCopy_clicked()));
    contextMenu.addAction(tr("&View"), this, SLOT(on_cmdView_clicked()));
    contextMenu.addMenu(&exportMenu);
    contextMenu.addAction(tr("&Remove"), this, SLOT(on_cmdDelete_clicked()));
    if (ui->cbSelected->isVisible())
    {
        contextMenu.addSeparator();
        if (!ui->cbSelected->isChecked()) { contextMenu.addAction(tr("&Select"), this, SLOT(pictureSelected())); }
        if (ui->cbSelected->isChecked()) { contextMenu.addAction(tr("&Deselect"), this, SLOT(pictureSelected())); }
        contextMenu.addAction(tr("Select &All"), this, SLOT(selectAllWidgets()), QKeySequence::fromString("Ctrl+S"));
        contextMenu.addAction(tr("&Deselect All"), this, SLOT(deselectAllWidgets()), QKeySequence::fromString("Ctrl+D"));
    }
    else
    {
        contextMenu.addSeparator();
        contextMenu.addAction(tr("&Select"), this, SLOT(pictureSelected()));
        contextMenu.addAction(tr("Select &All"), this, SLOT(selectAllWidgets()), QKeySequence::fromString("Ctrl+S"));
    }
    //ui->SnapmaticFrame->setStyleSheet(QString("QFrame#SnapmaticFrame{background-color: rgb(%1, %2, %3)}QLabel#labPicStr{color: rgb(%4, %5, %6)}").arg(QString::number(highlightBackColor.red()), QString::number(highlightBackColor.green()), QString::number(highlightBackColor.blue()), QString::number(highlightTextColor.red()), QString::number(highlightTextColor.green()), QString::number(highlightTextColor.blue())));
    contextMenu.exec(ev->globalPos());
    //ui->SnapmaticFrame->setStyleSheet("");
}

void SnapmaticWidget::dialogNextPictureRequested()
{
    emit nextPictureRequested((QWidget*)sender());
}

void SnapmaticWidget::dialogPreviousPictureRequested()
{
    emit previousPictureRequested((QWidget*)sender());
}

void SnapmaticWidget::on_cbSelected_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        emit widgetSelected();
    }
    else if (arg1 == Qt::Unchecked)
    {
        emit widgetDeselected();
    }
}

bool SnapmaticWidget::isSelected()
{
    return ui->cbSelected->isChecked();
}

void SnapmaticWidget::setSelectionMode(bool selectionMode)
{
    ui->cbSelected->setVisible(selectionMode);
}

void SnapmaticWidget::selectAllWidgets()
{
    emit allWidgetsSelected();
}

void SnapmaticWidget::deselectAllWidgets()
{
    emit allWidgetsDeselected();
}

SnapmaticPicture* SnapmaticWidget::getPicture()
{
    return smpic;
}

QString SnapmaticWidget::getWidgetType()
{
    return "SnapmaticWidget";
}
