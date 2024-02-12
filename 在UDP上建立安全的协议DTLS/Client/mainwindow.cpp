#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(QSize(800,1200)); // 电脑端的逻辑
  //  setFixedSize(QSize(1080,1920)) ; // 手机端的逻辑
    initCombox();
    ui->plainTextEdit->appendPlainText("*******程序初始化");
    association=new Association(QHostAddress("192.168.158.1"),7755,"judy");
    ui->plainTextEdit->setFont(QFont("Courier New",13,2));
    ui->plainTextEdit->appendPlainText(association->udpSocketBindStatus());
    ui->plainTextEdit->appendPlainText(association->udpSocketConnectStatus(QHostAddress("192.168.137.1"),7755));
    ui->plainTextEdit->appendPlainText("*******程序初始化完毕！");
    ui->plainTextEdit->appendPlainText("*******start handshake*****************");
    connect(association,&Association::errorMessage,this,[=](const QString message){
        ui->plainTextEdit->appendPlainText("#########"+message);
    });
    connect(association,&Association::serverResponse,this,[=](const QString client,const QByteArray plainText){
        ui->plainTextEdit->appendPlainText("######### client  "+client);
        ui->plainTextEdit->appendPlainText("######### plainText  "+plainText);
    });
}

MainWindow::~MainWindow(){
    delete  association;
    delete ui;
}


void MainWindow::initCombox(){
    QList<QHostAddress> ipv4List=association->getAllIPV4Address();
    if(ipv4List.size()>0){
        for (QHostAddress & address : ipv4List ) {
            if(address.protocol()==QUdpSocket::IPv4Protocol){
                ui->comboBox->addItem(address.toString());
            }

        }
    }

}



void MainWindow::on_toolButton_2_clicked(){
    QApplication::exit(0);
}

void MainWindow::on_toolButton_clicked(){
    association->FunctionTest();
    ui->plainTextEdit->appendPlainText("#####正在写clienthello");
}


void MainWindow::on_testToolButton_clicked(){
    association->TestHandshakeToServer();
}

