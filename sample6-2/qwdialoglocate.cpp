#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include    <QMessageBox>
#include    "mainwindow.h"
QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{   QMessageBox::information(this,"提示","设定完毕");
    delete ui;
}


void QWDialogLocate::setSpinRange(int row,int column){
    ui->BoxRow->setRange(row,column);
    ui->BoxColumn->setRange(row,column);
}

void QWDialogLocate::setSpinValue(int row,int column){
    ui->BoxRow->setValue(row);
    ui->BoxColumn->setValue(column);
}


void QWDialogLocate::on_btnSet_clicked()
{
    int row=ui->BoxRow->value();
    int column=ui->BoxColumn->value();
    MainWindow*parWind=(MainWindow*)parent();
    parWind->setCellText(row,column,ui->lineEdit->text());

}

