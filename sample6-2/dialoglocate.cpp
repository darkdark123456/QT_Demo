#include "dialoglocate.h"
#include "ui_dialoglocate.h"

DialogLocate::DialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocate)
{
    ui->setupUi(this);


}

DialogLocate::~DialogLocate()
{
    delete ui;
}

void DialogLocate::setSpinValue(int row,int column){
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}

void DialogLocate::setSpinRange(int row,int column){
    ui->spinBoxRow->setRange(0,row);
    ui->spinBoxColumn->setRange(0,column);
}

void DialogLocate::on_btnSetText_clicked()
{
    int row=ui->spinBoxRow->value();
    int col=ui->spinBoxColumn->value();
    QString text=ui->lineEditText->text();
    emit changeCellText(row,col,text);
}

