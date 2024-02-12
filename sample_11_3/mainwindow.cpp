#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QFileDialog>
#include    <QMessageBox>
#include    <QSqlQuery>
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


void MainWindow::on_actOpen_triggered()
{
    QString aFile=QFileDialog::getOpenFileName(this,"选择数据库","","*.db3");
    if(aFile.isEmpty()){
        return ;
    }
    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open()){
        QMessageBox::warning(this,"error","打开数据库失败",QMessageBox::Ok);
        return ;
    }
    else{
        openTable();
    }
}


void MainWindow::openTable(){

    qryModel=new QSqlQueryModel(this);
    qryModel->setQuery("SELECT EmpNO ,Name,Gender,Height,Birthday,Mobile,Province,City,Department,Education,Salary FROM employee ORDER BY EmpNO");
    if(qryModel->lastError().isValid()){
        QMessageBox::critical(this,"error","数据表查询错误");
        return ;
    }

    qryModel->setHeaderData(0,Qt::Horizontal,"工号");
    qryModel->setHeaderData(1,Qt::Horizontal,"姓名");
    qryModel->setHeaderData(2,Qt::Horizontal,"性别");
    qryModel->setHeaderData(3,Qt::Horizontal,"身高");
    qryModel->setHeaderData(4,Qt::Horizontal,"出生日期");
    qryModel->setHeaderData(5,Qt::Horizontal,"手机");
    qryModel->setHeaderData(6,Qt::Horizontal,"省份");
    qryModel->setHeaderData(7,Qt::Horizontal,"城市");
    qryModel->setHeaderData(8,Qt::Horizontal,"部门");
    qryModel->setHeaderData(9,Qt::Horizontal,"学历");
    qryModel->setHeaderData(10,Qt::Horizontal,"工资");

    theSelectionModel=new QItemSelectionModel(qryModel);
    connect(theSelectionModel,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelectionModel);
    ui->actOpen->setEnabled(false);
}




void MainWindow::on_actDel_triggered()
{
    int curRecNo=theSelectionModel->currentIndex().row();
    QSqlRecord curRec=qryModel->record(curRecNo);
    if(curRec.isEmpty()){
        return;
    }
    int empNo=curRec.value("EmpNO").toInt();
    QSqlQuery query;
    query.prepare("delete from employee where EmpNO=:ID");
    query.bindValue(":ID",empNo);
    if(!query.exec()){
        QMessageBox::critical(this,"error","error");
    }
    else{
        query.exec();
    }

}


void MainWindow::on_actAddSalary_triggered()
{
    QSqlQuery queryList;
    queryList.exec("SELECT EmpNO,Salary FROM employee ORDER BY EmpNO");
    queryList.first();
    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE employee SET Salary=:salary WHERE EmpNO=:ID");
    while(queryList.isValid()){
        int empID=queryList.value("EmpNO").toInt();
        float salary=queryList.value("Salary").toFloat();
        salary+=1000;
        queryUpdate.bindValue(":ID",empID);
        queryUpdate.bindValue(":salary",salary);
        queryUpdate.exec();
        if(!queryList.next()){
            break;
        }
    }
    qryModel->query().exec();//update tableview
    QMessageBox::information(this,"提示","涨工资完毕");
}

