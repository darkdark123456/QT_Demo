#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    "server.h"

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
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void addErrorMessage(const QString& message);
    void on_TestHandBtn_clicked();

private:
    Ui::MainWindow *ui;
    DtlsServer* server;

};
#endif // MAINWINDOW_H
