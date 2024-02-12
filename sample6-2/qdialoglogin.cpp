#include "qdialoglogin.h"
#include "ui_qdialoglogin.h"
#include    <QPixmap>
#include    <QSettings>
#include    <QCryptographicHash>
#include    <QByteArray>
#include    <QMessageBox>
#include    <QMouseEvent>
QDialogLogin::QDialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDialogLogin)
{
    ui->setupUi(this);
    QPixmap pixmap;
    pixmap.load(":/image/login.jpg");
    QPixmap pix=pixmap.scaledToWidth(458);
    ui->labelPicture->setPixmap(pix);
    ui->textPaswd->setEchoMode(QLineEdit::Password);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    readSettings();


}

QDialogLogin::~QDialogLogin()
{
    delete ui;
}

void QDialogLogin::readSettings(){
    QString arganization="WWB-QT";
    QString appName="smaple6_2";
    QSettings setting(arganization,appName);
    bool saved=setting.value("saved",false).toBool();
    m_user=setting.value("username","mzc228699").toString();
    QString defaultPswd=encrypt("123456");
    m_pswd=setting.value("psed",defaultPswd).toString();
    ui->textUserName->setText(m_user);
    ui->boxSaveUsername->setChecked(saved);
    qDebug()<<defaultPswd;


}

void QDialogLogin::writeSetting(){
    QSettings settings("wwb-qt","sample6_2");
    settings.setValue("username",m_user);
    settings.setValue("PSWD",m_pswd);
    settings.setValue("saved",ui->boxSaveUsername->isChecked());
}


QString QDialogLogin:: encrypt(char *str){
    QByteArray btArray;
    btArray.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(btArray);
    QByteArray resArray=hash.result();
    QString md5 =resArray.toHex();
    return md5;
}




void QDialogLogin::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        m_moving=true;
        m_lastPos=event->globalPos()-pos();
    }
    return QDialog::mousePressEvent(event);

}

void QDialogLogin:: mouseMoveEvent(QMouseEvent *event){
    move(event->globalPos()-m_lastPos);
    return QDialog::mouseMoveEvent(event);

}

void QDialogLogin::mouseRealaseEvent(QMouseEvent *event){
    m_moving=false;
}

void QDialogLogin::on_btnOK_clicked()
{   QString user=ui->textUserName->text().trimmed();
    QString strpswd=ui->textPaswd->text().trimmed();
    char *pswd=strpswd.toLatin1().data();
    QString realPswd=encrypt(pswd);
    if((user==m_user)&&(realPswd==m_pswd)){
    this->accept();}
    else{
        QMessageBox::information(this,"error","密码错误");
        ++m_tryCount;
        if(m_tryCount>3){
            QMessageBox::critical(this,"error","输入密码错误次数过多");
            this->reject();
        }
    }
}



