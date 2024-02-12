#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_count_clicked()
{
    QString str=ui->str1_editText->text();
    unsigned int num=str.count();
    ui->count_editText->setText(QString("%1").arg(num));
}


void Widget::on_size_clicked()
{
    QString str=ui->str1_editText->text();
    unsigned int num=str.count();
    ui->count_editText->setText(QString("%1").arg(num));
}


void Widget::on_upper_clicked()
{
    QString str=ui->str1_editText->text();
    str=str.toUpper();
    ui->result_editText->setText(str);
}


void Widget::on_lower_clicked()
{
    QString str=ui->str1_editText->text();
    str=str.toLower();
    ui->result_editText->setText(str);
}


void Widget::on_is_empty_clicked()
{
    QString str=ui->str1_editText->text();
    if(str.isEmpty()){
        ui->result_editText->setText("字符串为空");
    }
    else{
        ui->result_editText->setText("字符串非空");
    }
}


void Widget::on_is_null_clicked()
{
    QString str=ui->str1_editText->text();
    if(str.isEmpty()){
        ui->result_editText->setText("字符串为空");
    }
    else{
        ui->result_editText->setText("字符串非空");
    }
}


void Widget::on_append_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    str1=str1+str2;
    ui->result_editText->setText(str1);
    ui->str1_editText->setText(str1);
    ui->str2_editText->clear();
}


void Widget::on_prepend_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    str1=str2+str1;
    ui->result_editText->setText(str1);
    ui->str1_editText->setText(str1);
    ui->str2_editText->clear();
}


void Widget::on_indexof_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    int pos=str1.indexOf(str2);
    ui->result_editText->setText(QString("%1").arg(pos));
}


void Widget::on_lastindexof_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    int pos=str1.lastIndexOf(str2);
    ui->result_editText->setText(QString("%1").arg(pos));
}


void Widget::on_right_clicked()
{
    QString str1=ui->str1_editText->text();
    int num=ui->editText_count_right_or_left->text().toInt();
    QString str2=str1.right(num);
    ui->result_editText->setText(str2);
    ui->str2_editText->setText(str2);
}


void Widget::on_left_clicked()
{
    QString str1=ui->str1_editText->text();
    int num=ui->editText_count_right_or_left->text().toInt();
    QString str2=str1.left(num);
    ui->result_editText->setText(str2);
    ui->str2_editText->setText(str2);
}


void Widget::on_trimm_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=str1.trimmed();
    ui->result_editText->setText(str2);
}


void Widget::on_section_clicked()
{
     QString str1=ui->str1_editText->text();
     QString str2=str1.section(",",0,1);
     ui->result_editText->setText(str2);
}


void Widget::on_contains_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    bool n=str1.contains(str2);
    ui->result_editText->setText(QString("%1").arg(n));

}


void Widget::on_endwith_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    bool n=str1.endsWith(str2);
    ui->result_editText->setText(QString("%1").arg(n));
}


void Widget::on_stratswith_clicked()
{
    QString str1=ui->str1_editText->text();
    QString str2=ui->str2_editText->text();
    bool n=str1.startsWith(str2);
    ui->result_editText->setText(QString("%1").arg(n));
}

