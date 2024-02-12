#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_toolButton_clicked()
{   float price=ui->priceEdit->text().toFloat();
    int number=ui->numEdit->text().toInt();
    float total=number*price;
    ui->allPriceEdit->setText(QString("%1").arg(total));

}


void Widget::on_toolButton_2_clicked()
{
    QString str=ui->editDec->text();
    int val=str.toInt();

    str=str.setNum(val,16);
    str=str.toUpper();
    ui->editHex->setText(str);

    str=QString::number(val,2);
    ui->editBinary->setText(str);

}

