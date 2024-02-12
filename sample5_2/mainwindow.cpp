#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList stringList;
    stringList<<"蒙阴县"<<"沂水县"<<"费县"<<"平邑县"<<"莒南县";
    model=new QStringListModel(this);
    model->setStringList(stringList);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    model->insertRow(model->rowCount());
    QModelIndex index=model->index(model->rowCount()-1,0);
    model->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);

}


void MainWindow::on_pushButton_4_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    model->removeRow(index.row());
}


void MainWindow::on_pushButton_5_clicked()
{
    model->removeRows(0,model->rowCount());
}


void MainWindow::on_pushButton_3_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    model->insertRow(index.row());
    model->setData(index,"insert item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_pushButton_7_clicked()
{
    QStringList stringList=model->stringList();
    ui->plainTextEdit->clear();
    for(int i=0;i<stringList.count();i++){
        ui->plainTextEdit->appendPlainText(stringList.at(i));
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_pushButton_clicked()
{

}

