#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    "qwdialogsize.h"
#include    <QStandardItemModel>
#include    <QItemSelectionModel>
#include    <qwdialogheader.h>
#include    <dialoglocate.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actSetRowCol_triggered();

    void on_actSetHeader_triggered();


    void on_tableView_clicked(const QModelIndex &index);

    void on_actLocate_triggered();

private:
    Ui::MainWindow *ui;
    QWDialogSize *dlgTableSize;
    QStandardItemModel *model;
    QItemSelectionModel*smodel;
    QWDialogHeader *dlgHeader;
    DialogLocate *dlgLocate;
public slots:
    void setCellText(int row,int column,QString &text);
    void setActLocateEnable(bool enable);
signals:
    void cellIndexChange(int row,int column);


};
#endif // MAINWINDOW_H
