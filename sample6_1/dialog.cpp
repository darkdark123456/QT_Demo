#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOpen_clicked()
{
    QString curPath=QDir::currentPath();
    QString title="选择一个文件";
    QString filter="*.png;;*.jpg;;*.txt;;所有文件*.*";
    QString aFileName=QFileDialog::getOpenFileName(this,title,curPath,filter);
    if(!aFileName.isEmpty()){
        ui->textEdit->append(aFileName);
    }
}


void Dialog::on_btnOpenMulti_clicked()
{    QString curPath=QDir::currentPath();
     QString title="选择多个文件";
     QString filter="*.png;;*.jpg;;*.txt;;所有文件*.*";
     QStringList fileNameList=QFileDialog::getOpenFileNames(this,title,curPath,filter);
     for(int i=0;i<fileNameList.count();++i){
         ui->textEdit->append(fileNameList[i]);
     }

}


void Dialog::on_btnSelectDir_clicked()
{    QString curPath=QDir::currentPath();
     QString title="选择一个目录";
     QString selectDir=QFileDialog::getExistingDirectory(this,title,curPath);
     if(!selectDir.isEmpty()){
         ui->textEdit->append(selectDir);
     }

}


void Dialog::on_btnSave_clicked()
{
    QString curPath=QDir::currentPath();
    QString title="保存文件";
    QString filter="*.cpp;;*.h;;*.txt;;所有文件*.*";
    QString aFileName=QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(!aFileName.isEmpty()){
        ui->textEdit->append(aFileName);
    }

}


void Dialog::on_btnSelectColor_clicked()
{
    QPalette palette=ui->textEdit->palette();
    QColor initcolor=palette.color(QPalette::Text);
    QColor color=QColorDialog::getColor(initcolor,this,"选择颜色");
    if(color.isValid()){
        palette.setColor(QPalette::Text,color);
        ui->textEdit->setPalette(palette);
    }
}


void Dialog::on_btnSelectFont_clicked()
{
    QFont currentFont=ui->textEdit->font();
    bool ok=true;
    QFont font=QFontDialog::getFont(&ok,currentFont);
    ui->textEdit->setFont(font);

}


void Dialog::on_btnClear_clicked()
{
    ui->textEdit->clear();
}


void Dialog::on_btnInputString_clicked()
{
    QString title="输入文字对话框";
    QString txtlabel="请输入文件名";
    QString defaultInput=".txt";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    bool ok=false;
    QString text=QInputDialog::getText(this,title,txtlabel,echoMode,defaultInput,&ok);
    if(ok && !text.isEmpty()){
        ui->textEdit->append(text);
    }
}


void Dialog::on_btnInputInter_clicked()
{   QString title="输入整数对话框";
    QString txtlabel="设置字体大小";
    int defaultValue=ui->textEdit->font().pointSize();
    int minValue=6;
    int maxValue=56;
    int stepValue=1;
    bool ok=true;
    int inputValue=QInputDialog::getInt(this,title,txtlabel,defaultValue,minValue,maxValue,stepValue,&ok);
    QFont font=ui->textEdit->font();
    font.setPointSize(inputValue);
    ui->textEdit->setFont(font);
}


void Dialog::on_btnInputFloat_clicked()
{
    QString title="输入浮点对话框";
    QString txtlabel="输入一个浮点数";
    float dafaultValue=3.13;
    float minValue=0;
    float maxValue=10000;
    int deciamals=2;
    bool ok=true;
    float inputValue=QInputDialog::getDouble(this,title,txtlabel,dafaultValue,minValue,maxValue,deciamals,&ok);
    QString str=QString("%1").arg(inputValue);
    ui->textEdit->append(str);
}


void Dialog::on_itemInput_clicked()
{
    QStringList items;
    items<<"优秀"<<"良好"<<"合格"<<"不合格";
    QString title="条目选择对话框";
    QString txtlabel="请选择级别";
    int curIndex=0;
    bool editable=true;
    bool ok;
    QString text=QInputDialog::getItem(this,title,txtlabel,items,curIndex,editable,&ok);
    ui->textEdit->append(text);
}


void Dialog::on_btnWarnning_clicked()
{
    QString title="warnning消息框";
    QString info="文件内容已经被修改";
    QMessageBox::warning(this,title,info);
}


void Dialog::on_btnInfo_clicked()
{
    QString title="infomation消息框";
    QString info="文件内容已经设置";
    QMessageBox::information(this,title,info);
}


void Dialog::on_pushButton_14_clicked()
{
    QString title="critical消息框";
    QString info="有不明程序访问网络";
    QMessageBox::critical(this,title,info);
}


void Dialog::on_pushButton_15_clicked()
{
    QString title="about消息框";
    QString info="我开发的数据查看软件";
    QMessageBox::about(this,title,info);
}


void Dialog::on_pushButton_11_clicked()
{
    QString title="question消息框";
    QString info="文件已被修改，是否保存？";
    QMessageBox::StandardButton result=QMessageBox::question(this,title,info,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if(result==QMessageBox::Yes){
        ui->textEdit->append("yes");
    }
    else if(result==QMessageBox::No){
        ui->textEdit->append("no");
    }
    else{
        ui->textEdit->append("cancel");
    }
}
