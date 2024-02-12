#include "widget.h"
#include "ui_widget.h"
#include    <time.h>



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
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->dateEdit->setDate(curDateTime.date());
    ui->dateTimeEdit->setDateTime(curDateTime);

    ui->timeStrEdit->setText(curDateTime.toString("hh:mm:ss"));
    ui->dateStrEdit->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateAndtimeStrEdit->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}


void Widget::on_calendarWidget_selectionChanged()
{
    QDate dt=ui->calendarWidget->selectedDate();
    QString str=dt.toString("yyyy年M月d日");
    ui->editCalender->setText(str);
}


void Widget::on_toolButton_7_clicked()
{
    this->close();
}


static clock_t start;
static clock_t finish;
void Widget::on_toolButton_5_clicked()
{
    ui->lcdMin->setDigitCount(2);
    ui->lcdMin->display("00");
    ui->lcdSec->setDigitCount(2);
    ui->lcdSec->display("00");
    ui->lcdMm->setDigitCount(4);
    ui->lcdMm->display("0000");
    start=clock();


}


void Widget::on_toolButton_9_clicked()
{
    long mvalue=0;
    long svalue=0;
    long msvalue=0;

    finish=clock();
    msvalue=finish-start;

    if(msvalue<1000){
        ui->lcdMm->display((int)msvalue);
    }
    else{
        ui->lcdMm->display(int(msvalue%1000));
        for(int i=0;i<(msvalue/1000);++i){
            ++svalue;

        }
        if(svalue<60){
        ui->lcdSec->display((int)svalue);}
        else{
            ui->lcdSec->display((int)(svalue%6));
            for(int i=0;i<(svalue/60);i++){
                ++mvalue;
            }
            ui->lcdMin->display((int)mvalue);

        }

    }

}

