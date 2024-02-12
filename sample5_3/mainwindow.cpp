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


void MainWindow::on_actOpenFile_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath(); // 目前debug的目录
    QString fileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,"*.txt");
    if(fileName.isEmpty()){
        return;
    }
    QStringList stringList;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream textStream(&file);
        ui->plainTextEdit->clear();
        while(!textStream.atEnd()){
            QString str=textStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            stringList.append(str);
        }
        file.close();
        ui->labCurrentFile->setText(fileName);
        QString header=stringList.at(1);
        initModel(stringList);
    }
}



void MainWindow::initModel(QStringList stringlist){
    int rowCount=stringlist.count();
    qDebug()<<stringlist[1][1];
    qDebug()<<stringlist[1][2];

    //standModel->setRowCount(rowCount-1);

}
