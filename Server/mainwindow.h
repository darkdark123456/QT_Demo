#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QtNetwork>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getLocalIP();
private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
private slots:
    void onNewConnection(); // 建立一个新连接时，server发送newconnection信号，被此响应函数接收，作用于this当前窗口
    void onSocketStateChange(QAbstractSocket::SocketState socketState); // socket的状态字改变
    void onClientConnected(); // 客户端已连接
    void onClientDisConnected(); // 客户端断开连接
    void onSocketReadyRead(); // 读取socket的数据
    void on_actStart_triggered();
    void on_actFinish_triggered();
    void on_actClear_triggered();
    void on_actExit_triggered();
    void on_btnSend_clicked();
};
#endif // MAINWINDOW_H
