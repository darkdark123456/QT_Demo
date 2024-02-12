#ifndef ASSOCIATION_H
#define ASSOCIATION_H
#include    <QtCore>
#include    <QUdpSocket>
#include    <QDtls>
#include    <QSsl>
#include    <QTimer>
#include    <QHostAddress>
#include    <QSslPreSharedKeyAuthenticator>
#include    <QSslSocket>
#include    <QHostAddress>
#include    <QAbstractSocket>
#include    <QMessageBox>
#include    <QSslConfiguration>
#include    <QNetworkInterface>



class Association: public QObject{
    Q_OBJECT
public:
    Association();
    Association(const QHostAddress& address,quint16 port,const QString& connectionName);
    ~Association();
public:
    void startHandshake();
    bool initUdpSocket();
    QString udpSocketBindStatus();
    QString udpSocketConnectStatus(const QHostAddress& address,quint16 port);
    QSslConfiguration initSslConfiguration();
    void FunctionTest();
    void TestHandshakeToServer();
    QList<QHostAddress> getAllIPV4Address();

signals:
    void errorMessage(const QString& message);
    void serverResponse(const QString& client,const QByteArray& plainText);
private slots:
    void udpSocketConnected();
    void readyRead();
    void handshakeTimeout();
    void pskRequired(QSslPreSharedKeyAuthenticator* auth);
    void pingTimeOut();
private:
    QString name;
    QUdpSocket* udpSocket;
    QDtls crypto;
    QTimer* PingTimer;
    unsigned int ping=0;
    bool status=false;
    unsigned long long messageReceivedTime=0;
};

#endif // ASSOCIATION_H
