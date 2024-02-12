#ifndef QDIALOGLOGIN_H
#define QDIALOGLOGIN_H

#include <QDialog>
#include    <QPoint>
namespace Ui {
class QDialogLogin;
}

class QDialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QDialogLogin(QWidget *parent = nullptr);
    ~QDialogLogin();
    void readSettings();
    void writeSetting();


private:
    Ui::QDialogLogin *ui;
private:
    bool m_moving=false;
    QPoint m_lastPos;
    QString m_user="user";
    QString m_pswd="12345";
    int m_tryCount=0;
    QString encrypt(char *str);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseRealaseEvent(QMouseEvent *event);





private slots:
    void on_btnOK_clicked();
};

#endif // QDIALOGLOGIN_H
