#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QtSql>
#include    <QDataWidgetMapper>
#include    "wdialogdata.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    WDialogData *dlgdata;

private slots:
    void on_actOpen_triggered();

    void on_actDel_triggered();

    void on_actAddSalary_triggered();

private:
    Ui::MainWindow *ui;
private:
    QSqlDatabase DB;
    QSqlQueryModel *qryModel;
    QItemSelectionModel *theSelectionModel;
    void updateRecord(int recNo);
    void openTable();

};
#endif // MAINWINDOW_H
