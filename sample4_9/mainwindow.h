#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QDate>
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
    Ui::MainWindow *ui;
private:
    enum FieldColNum{colName=0,colSex,colBirth,colNation,colScore,colPartyM};// 列编号
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore}; // 某一列
public:
    void creatItemRow(int rowNo,QString name,QString sex,QDate birth,QString Nation,bool isPM,int score);
private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
};
#endif // MAINWINDOW_H
