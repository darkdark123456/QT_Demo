#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include    <QString>
#include    <QDir>
#include    <QFileDialog>
#include    <QColorDialog>
#include    <QFontDialog>
#include    <QLineEdit>
#include    <QInputDialog>
#include    <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnOpen_clicked();

    void on_btnOpenMulti_clicked();

    void on_btnSelectDir_clicked();

    void on_btnSave_clicked();

    void on_btnSelectColor_clicked();

    void on_btnSelectFont_clicked();

    void on_btnClear_clicked();

    void on_btnInputString_clicked();

    void on_btnInputInter_clicked();

    void on_btnInputFloat_clicked();

    void on_itemInput_clicked();

    void on_btnWarnning_clicked();

    void on_btnInfo_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
