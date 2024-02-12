#include "qwdialogheader.h"
#include "ui_qwdialogheader.h"
#include    <QMessageBox>
QWDialogHeader::QWDialogHeader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeader)
{
    ui->setupUi(this);
    listModel=new QStringListModel();
    ui->listView->setModel(listModel);
    QStringList strList;
    strList<<"姓名"<<"性别"<<"年龄"<<"籍贯";
    listModel->setStringList(strList);
}

QWDialogHeader::~QWDialogHeader()
{   QMessageBox::information(this,"提示","设置标题对话框被删除");
    delete ui;
}

void QWDialogHeader::setHeaderList(QStringList&strList){
    listModel->setStringList(strList);
}


QStringList QWDialogHeader::headersList(){
    return listModel->stringList();
}

