#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatItemRow(int rowNo,QString name,QString sex,QDate birth,QString Nation,bool isPM,int score){
    QTableWidgetItem *item;
    QString str;
    item=new QTableWidgetItem(name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colName,item);

    item=new QTableWidgetItem(sex,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colSex,item);



    item=new QTableWidgetItem(birth.toString(),MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colBirth,item);

    item=new QTableWidgetItem(Nation,MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colNation,item);


    item=new QTableWidgetItem(QString("%1").arg(isPM),MainWindow::colPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colPartyM,item);

    item=new QTableWidgetItem(QString("%1").arg(score),MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo,MainWindow::colScore,item);

}


void MainWindow::on_pushButton_4_clicked()
{
    int curRow=ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(curRow+1);
    creatItemRow(curRow+1,"新学生","男",QDate::fromString("1996-12-06","yyyy-MM-dd"),"满族",false,100);
}


void MainWindow::on_pushButton_6_clicked()
{
    int curRow=ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(curRow);
}

