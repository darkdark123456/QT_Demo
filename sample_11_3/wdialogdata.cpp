#include "wdialogdata.h"
#include "ui_wdialogdata.h"

WDialogData::WDialogData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WDialogData)
{
    ui->setupUi(this);
    this->setWindowTitle("更新记录");
}

WDialogData::~WDialogData()
{
    delete ui;
}
