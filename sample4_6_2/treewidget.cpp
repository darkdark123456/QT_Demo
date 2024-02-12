#include "treewidget.h"
#include "ui_treewidget.h"

treeWidget::treeWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::treeWidget)
{
    ui->setupUi(this);

}

treeWidget::~treeWidget()
{
    delete ui;
}


void treeWidget::on_actAddDirectory_triggered()
{
    QString dir=QFileDialog::getExistingDirectory(); //得到当前目录
    if(!dir.isEmpty()){
        QTreeWidgetItem *item=ui->treeWidget_2->currentItem();
        addDirectoryItem(item,dir);
    }
}


QString treeWidget::getFinalDirectoryName(const QString &fullPathName){
    int cnt=fullPathName.length();
    int i=fullPathName.lastIndexOf("/");
    QString str=fullPathName.right(cnt-i-1);
    return str;
}


void treeWidget::addDirectoryItem(QTreeWidgetItem *paritem,QString dir){
    QString NodeText=getFinalDirectoryName(dir);
    QIcon icon(":/image/file.ico");

    QTreeWidgetItem *item=new QTreeWidgetItem();//创建一个目录节点
    item->setIcon(0,icon);
    item->setText(0,NodeText);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsUserTristate);
    paritem->addChild(item);

}

void treeWidget::on_actAddFile_triggered() //添加图片
{
    QStringList files=QFileDialog::getOpenFileNames(this,"选择一个或多个文件","","Images(*.jpg)");
    qDebug()<<files;
    QTreeWidgetItem *item=ui->treeWidget_2->currentItem();
    //QTreeWidgetItem*parItem=item->parent();
    QString NodeText=getFinalDirectoryName(files[0]);
    QIcon icon(":/image/picture.ico");
    qDebug()<<NodeText;

    QTreeWidgetItem *tempItem=new QTreeWidgetItem();
    tempItem->setIcon(0,icon);
    tempItem->setText(0,NodeText);
    tempItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate | Qt::ItemIsEditable);
    tempItem->setData(0,Qt::UserRole,files[0]);
    item->addChild(tempItem);

    QString filename=tempItem->data(0,Qt::UserRole).toString();
    QPixmap curPixmap(filename);
    int H=ui->label->height();
    int realH=curPixmap.height();
    QPixmap pix=curPixmap.scaledToHeight(H-30);
    ui->label->setPixmap(pix);
    ui->label->show();
}


void treeWidget::on_actDeleteItem_triggered()
{
    QTreeWidgetItem *item=ui->treeWidget_2->currentItem();
    QTreeWidgetItem *parent=item->parent();
    parent->removeChild(item);
    delete item;
}


void treeWidget::on_actDisplay_triggered()
{
    QTreeWidgetItem *currentItem=ui->treeWidget_2->currentItem();
    QString filename=currentItem->data(0,Qt::UserRole).toString();
    QPixmap curPixmap(filename);
    int H=ui->label->height();
    QPixmap pix=curPixmap.scaledToHeight(H-30);
    ui->label->setPixmap(pix);
    ui->label->show();
}































