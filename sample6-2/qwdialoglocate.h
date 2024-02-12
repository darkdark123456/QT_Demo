
#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>
#include    <QCloseEvent>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();
private:
    Ui::QWDialogLocate *ui;

public:
   // void closeEvent(QCloseEvent *event);
    void setSpinRange(int row,int column);
    void setSpinValue(int row,int column);
private slots:
    void on_btnSet_clicked();
};

#endif // QWDIALOGLOCATE_H
