#ifndef SERVER_H
#define SERVER_H

#include    <QtCore>
#include    <QUdpSocket>
#include    <QSslConfiguration>
#include    <QDtlsClientVerifier>
#include    <QVector>
#include    <memory>
#include    <QDtls>
#include    <vector>
#include    <QSslPreSharedKeyAuthenticator>
#include    <QMessageBox>
#include    <QNetworkDatagram>

using std::vector;
using std::unique_ptr;

class DtlsServer  : public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(DtlsServer);
private:
    QUdpSocket* udpSocket;
    QSslConfiguration serverConfiguration;
    QDtlsClientVerifier cookieSender;
    std::vector<std::unique_ptr<QDtls>> knownClients;
    QDtls* OneDtls;
    bool listening=false;
    unsigned long long messageCount=0;
public:
    DtlsServer();
    ~DtlsServer();
public:
    unsigned int  function();
private:
    void handleNewConnection(const QHostAddress& peerAddress,unsigned int peerPort,const QByteArray& clientHello);
    void doHandshake(QDtls* newConnection,const QByteArray& clientHello);
    void decryptDatagram(QDtls* connection,const QByteArray& clientMessage);
    void initUdpSocket();
    void initServerConfiguration();
    void FunctionTest();
    void handshakeTest();
    void shudown();
signals:
    void datagramReceived(const QString& peerInfo,const QByteArray& cipherText,const QByteArray& plainText);
    void errorMessage(const QString &message);
private  slots:
    void readyRead();
    void TestFunction();
    void pskRequired(QSslPreSharedKeyAuthenticator* auth);
    void handshakeTimeout();
};

#endif // SERVER_H
