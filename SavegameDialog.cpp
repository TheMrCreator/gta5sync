#include "SavegameDialog.h"
#include "ui_SavegameDialog.h"
#include "SavegameCopy.h"
#include <QMessageBox>

SavegameDialog::SavegameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SavegameDialog)
{
    ui->setupUi(this);
    savegameLabStr = ui->labSavegameText->text();

    if (QIcon::hasThemeIcon("dialog-close"))
    {
        ui->cmdClose->setIcon(QIcon::fromTheme("dialog-close"));
    }
}

SavegameDialog::~SavegameDialog()
{
    delete ui;
}

void SavegameDialog::setSavegameData(SavegameData *savegame, QString savegamePath, bool readOk)
{
    // Showing error if reading error
    if (!readOk)
    {
        QMessageBox::warning(this,tr("Savegame Viewer"),tr("Failed at %1").arg(savegame->getLastStep()));
        return;
    }
    sgdPath = savegamePath;
    ui->labSavegameText->setText(savegameLabStr.arg(savegame->getSavegameStr()));
}

void SavegameDialog::on_cmdClose_clicked()
{
    this->close();
}

void SavegameDialog::on_cmdCopy_clicked()
{
    SavegameCopy::copySavegame(this, sgdPath);
}
