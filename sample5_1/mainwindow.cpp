#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);

}
s
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->tableView->setRootIndex(index);
    ui->listView->setRootIndex(index);
    ui->labelFileName->setText(model->fileName(index));
    ui->labelPath->setText(model->filePath(index));
    ui->labelType->setText(model->type(index));
    ui->checkBoxIsDir->setChecked(model->isDir(index));

    int size=model->size(index) / 1024;
    if(size<1024){
        ui->labelFileSzie->setText(QString("%1KB").arg(size));
    }
    else{
        ui->labelFileSzie->setText(QString(".1f MB").arg(size/1024.0));
    }
}

