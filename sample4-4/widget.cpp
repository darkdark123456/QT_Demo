#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->greenSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
    connect(ui->blueSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
    connect(ui->alphaSlider,SIGNAL(valueChanged(int)),this,SLOT(on_redSlider_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_redSlider_valueChanged(int value)
{
    Q_UNUSED(value);
    QColor color;
    int r=ui->redSlider->value();
    int g=ui->greenSlider->value();
    int b=ui->blueSlider->value();
    int a=ui->alphaSlider->value();
    color.setRgb(r,g,b,a); /* get color object*/
    QPalette pal=ui->textEdit->palette();
    pal.setColor(QPalette::Base,color); /* get palette object*/

    ui->textEdit->setPalette(pal);

}


void Widget::on_dial_valueChanged(int value)
{

    ui->lcdDisplay->display(value);
}

