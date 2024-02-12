#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    "association.h"
#include    <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initCombox();

private slots:
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
    void on_testToolButton_clicked();

private:
    Ui::MainWindow *ui;
    Association *association;

};
#endif // MAINWINDOW_H
