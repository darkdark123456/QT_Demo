#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btnClearList_1->setDefaultAction(ui->actClearList);
    connect(ui->actInitList,SIGNAL(triggered()),this,SLOT(on_actListInit_triggered()));
    ui->btnInitList_1->setDefaultAction(ui->actInitList);
    connect(ui->actInsErt,SIGNAL(triggered()),this,SLOT(on_actListInsert_triggered()));
    ui->btnInsertPage_1->setDefaultAction(ui->actInsErt);
    ui->btnDeleteCurrentPage_1->setDefaultAction(ui->actClearCurrent);
    ui->btnAdd_1->setDefaultAction(ui->actAdd);
    creatSelectPopMenu();
    creatActSelectMenu();
   // ui->varEditText->setText(ui->listWidget->currentItem()->text());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actListInit_triggered(){
    QListWidgetItem *aitem;
    QIcon icon;
    icon.addFile(":/image/button.ico");
    ui->listWidget->clear();
    for(int i=0;i<5;++i){
        aitem=new QListWidgetItem;
        aitem->setIcon(icon);
        aitem->setText(QString("item%1").arg(i));
        aitem->setCheckState(Qt::Checked);
        aitem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled |Qt::ItemIsUserCheckable);
        ui->listWidget->addItem(aitem);
    }
}


void MainWindow::on_actListInsert_triggered(){
    QIcon icon;
    icon.addFile(":/image/button.ico");
    QListWidgetItem *item=new QListWidgetItem("New Insert Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled |Qt::ItemIsUserCheckable);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),item);
}


void MainWindow::on_actClearCurrent_triggered(){ // on_actname_triggered 严格命名时，会自动设置connect函数；
    int row=ui->listWidget->currentRow();
    QListWidgetItem *currentItem=ui->listWidget->currentItem();
    ui->listWidget->takeItem(row);//在ui上移除这一行
    delete currentItem;// 真正析构掉new出的内存
}



void MainWindow::on_btnSelectAll_1_clicked()
{
    int cnt=ui->listWidget->count();
    for(int row=0;row<cnt;row++){
        QListWidgetItem *item=ui->listWidget->item(row);
        item->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_btnSelectNotAtALL_1_clicked()
{
    int cnt=ui->listWidget->count();
    for(int row=0;row<cnt;row++){
        QListWidgetItem *item=ui->listWidget->item(row);
        item->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_btnPartialSelect_clicked()
{
    int cnt=ui->listWidget->count();
    for(int row=0;row<cnt;row++){
        QListWidgetItem *item=ui->listWidget->item(row);
        item->setCheckState(Qt::PartiallyChecked);
    }
}


void MainWindow::on_actAdd_triggered()
{
    QIcon icon;
    icon.addFile(":/image/button.ico");
    QListWidgetItem *item=new QListWidgetItem("New Insert Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled |Qt::ItemIsUserCheckable);
    ui->listWidget->insertItem(ui->listWidget->count()+1,item);

}


void MainWindow::on_actSelect_triggered()
{

}


void MainWindow::creatSelectPopMenu(){
    QMenu*  menuSelect=new QMenu(this);
    menuSelect->addAction(ui->actSelectAll);
    menuSelect->addAction(ui->actSelectNAll);
    menuSelect->addAction(ui->actSelectInvs);
    ui->btnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->btnSelectItem->setMenu(menuSelect);
}



void MainWindow::creatActSelectMenu(){

}


void MainWindow::on_actSelectAll_triggered()
{    int cnt=ui->listWidget->count();
     for(int row=0;row<cnt;row++){
         QListWidgetItem *item=ui->listWidget->item(row);
         item->setCheckState(Qt::Checked);
     }
}


void MainWindow::on_actSelectNAll_triggered()
{
    int cnt=ui->listWidget->count();
    for(int row=0;row<cnt;row++){
        QListWidgetItem *item=ui->listWidget->item(row);
        item->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_actSelectInvs_triggered()
{
    int cnt=ui->listWidget->count();
    for(int row=0;row<cnt;row++){
        QListWidgetItem *item=ui->listWidget->item(row);
        item->setCheckState(Qt::PartiallyChecked);
    }
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menuList=new QMenu(this);
    menuList->addAction(ui->actInitList);
    menuList->addAction(ui->actClearList);
    menuList->addAction(ui->actClearCurrent);
    menuList->addAction(ui->actAdd);
    menuList->addAction(ui->actInsErt);
    menuList->addAction(ui->actExit);
    menuList->addSeparator();
    menuList->addAction(ui->actSelectAll);
    menuList->addAction(ui->actSelectNAll);
    menuList->addAction(ui->actSelectInvs);
    menuList->exec(QCursor::pos());
}

