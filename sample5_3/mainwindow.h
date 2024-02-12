#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    <QStandardItemModel>
#include    <QItemSelectionModel>
#include    <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initModel(QStringList stringList);

private slots:
    void on_actOpenFile_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *standModel;
    QItemSelectionModel *selectModel;


};
#endif // MAINWINDOW_H
