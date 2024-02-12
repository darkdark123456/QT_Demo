#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenu>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void creatSelectPopMenu();
    void creatActSelectMenu();
private:
    Ui::MainWindow *ui;
private slots:
    void on_actListInit_triggered();
    void on_actListInsert_triggered();
    void on_actClearCurrent_triggered();
    void on_btnSelectAll_1_clicked();
    void on_btnSelectNotAtALL_1_clicked();
    void on_btnPartialSelect_clicked();
    void on_actAdd_triggered();
    void on_actSelect_triggered();
    void on_actSelectAll_triggered();
    void on_actSelectNAll_triggered();
    void on_actSelectInvs_triggered();
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
};
#endif // MAINWINDOW_H
