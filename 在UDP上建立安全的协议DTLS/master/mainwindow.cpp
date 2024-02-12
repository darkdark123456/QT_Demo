#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(QSize(746,725));
    server=new DtlsServer();
    //QMessageBox::information(this,"size",QString::number(server->function()));
    connect(server,&DtlsServer::errorMessage,this,&MainWindow::addErrorMessage);
}


MainWindow::~MainWindow()
{
    delete  server;
    delete ui;

}


void MainWindow::on_toolButton_clicked(){
    QApplication::exit(0);
}


void MainWindow::on_toolButton_2_clicked(){
    return;
}


void MainWindow::addErrorMessage(const QString& message){
    ui->plainTextEdit->appendPlainText(message);
}

void MainWindow::on_TestHandBtn_clicked(){

}

