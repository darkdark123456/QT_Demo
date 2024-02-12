#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(600,700);
    tcpClient=new QTcpSocket(this);
    QString IP=getLocalIP();
    this->setWindowTitle("本机ip "+IP);
    ui->boxSAddress->addItem(IP);
    connect(tcpClient,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(tcpClient,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;

}

QString MainWindow::getLocalIP(){
    QString hostName=QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    QString localIP;
    QList<QHostAddress>  addList=hostInfo.addresses();
    if(!addList.isEmpty()){
        for(int i=0;i<addList.count();i++){
            QHostAddress aHost=addList.at(i);
            if(aHost.protocol()==QAbstractSocket::IPv4Protocol){
                localIP=aHost.toString();
            }
        }
    }
    return localIP;
}



void MainWindow::onConnected(){
    ui->plainTextEdit->appendPlainText("**服务器已连接");
}


void MainWindow::onDisconnected(){
    if(tcpClient->state()==QAbstractSocket::ConnectedState){
        tcpClient->close();
    }
}


void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState){

}


void MainWindow::onSocketReadyRead(){

    while(tcpClient->canReadLine()){
        ui->plainTextEdit->appendPlainText("[client]"+tcpClient->readLine());
    }
}
void MainWindow::on_btnSend_clicked()
{
    QString text=ui->textInfo->text();
    ui->textInfo->clear();
    ui->textInfo->setFocus();
    QByteArray str=text.toUtf8();
    str.append('\n');
    tcpClient->write(str);
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_actConnectServer_triggered()
{
    QString ip=ui->boxSAddress->currentText();
    quint16 port=ui->boxPort->value();
    tcpClient->connectToHost(ip,port);
    ui->actConnectServer->setEnabled(false);
    ui->actCloseConnect->setEnabled(true);
}

