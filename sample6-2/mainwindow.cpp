#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QItemSelectionModel>
#include    <QAbstractItemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QStandardItemModel();
    ui->tableView->setModel(model);
    smodel=new QItemSelectionModel(model);
    ui->tableView->setSelectionModel(smodel);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actSetRowCol_triggered()
{
    dlgTableSize=new QWDialogSize();
    dlgTableSize->setRowColumn(1,2);
    dlgTableSize->setWindowFlags(dlgTableSize->windowFlags());
    int ret=dlgTableSize->exec();
    if(ret==QDialog::Accepted){
       model->setColumnCount(dlgTableSize->columnCount());
       model->setRowCount(dlgTableSize->rowCount());
    }
    delete dlgTableSize;
}


void MainWindow::on_actSetHeader_triggered()
{   QStringList strList;
    if(!dlgHeader){
        dlgHeader=new QWDialogHeader(this);
    }
    int ret=dlgHeader->exec();
    if(ret==QDialog::Accepted){
        model->setHorizontalHeaderLabels(dlgHeader->headersList());
    }

}



void MainWindow::setCellText(int row,int column,QString &text){
    QModelIndex index=model->index(row,column);
    smodel->clearSelection();
    smodel->setCurrentIndex(index,QItemSelectionModel::Select);
    model->setData(index,text,Qt::DisplayRole);
}


void MainWindow::setActLocateEnable(bool enable){
    ui->actLocate->setEnabled(enable);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChange(index.row(),index.column());
}




void MainWindow::on_actLocate_triggered()
{
    dlgLocate=new DialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    dlgLocate->setWindowFlags(dlgLocate->windowFlags() | Qt::WindowStaysOnTopHint);
    dlgLocate->setSpinValue(model->rowCount(),model->columnCount());
    QModelIndex currentIndex=smodel->currentIndex();
    if(currentIndex.isValid()){
        dlgLocate->setSpinValue(currentIndex.row(),currentIndex.column());
    }
    connect(this,SIGNAL(cellIndexChange(int,int)),dlgLocate,SLOT(setSpinValue(int,int)));
    connect(dlgLocate,SIGNAL(changeCellText(int,int,QString &)),this,SLOT(setCellText(int,int,QString &)));
    dlgLocate->show();

}

