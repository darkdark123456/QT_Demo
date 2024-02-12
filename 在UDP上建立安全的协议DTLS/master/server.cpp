#include "server.h"


DtlsServer::DtlsServer(){
    initUdpSocket();
    initServerConfiguration();
   // connect(udpSocket,&QAbstractSocket::readyRead,this,&DtlsServer::readyRead);
    OneDtls=new QDtls(QSslSocket::SslServerMode);
    OneDtls->setPeer(QHostAddress("192.168.158.1"),55551);
    OneDtls->setDtlsConfiguration(serverConfiguration);
    connect(udpSocket,&QAbstractSocket::readyRead,this,&DtlsServer::TestFunction);
    connect(OneDtls,&QDtls::pskRequired,this,&DtlsServer::pskRequired);
    connect(OneDtls,&QDtls::handshakeTimeout,this,&DtlsServer::handshakeTimeout);
}


DtlsServer::~DtlsServer(){
    shudown();
    OneDtls->shutdown(udpSocket);
    udpSocket->close();
    delete  udpSocket;
    delete  OneDtls;
}


void DtlsServer::initUdpSocket(){
    udpSocket=new QUdpSocket();
    listening=udpSocket->bind(QHostAddress("192.168.158.1"),7755);
    if(listening){
         emit errorMessage("bind [192.158.168.1,7755] success");
    }
}


void DtlsServer::initServerConfiguration(){
    serverConfiguration=QSslConfiguration::defaultConfiguration();
    serverConfiguration.setDtlsCookieVerificationEnabled(false);
    serverConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    serverConfiguration.setProtocol(QSsl::DtlsV1_0);
}


void DtlsServer::pskRequired(QSslPreSharedKeyAuthenticator* auth){
    emit errorMessage(tr("received clients indetity  ")+auth->identity());
    QByteArray dataArray="meng";
    auth->setPreSharedKey(dataArray);
}


void DtlsServer::handshakeTimeout(){
    emit errorMessage(QString("hanshake time out "));
    if(!OneDtls->handleTimeout(udpSocket)){
        emit errorMessage(OneDtls->dtlsErrorString());
    }
}

void DtlsServer::handleNewConnection(const QHostAddress &peerAddress, unsigned int peerPort, const QByteArray &clientHello){
    if(!listening){
        emit errorMessage("服务端没有处于监听状态");
        return;
    }

    emit errorMessage(QString("现在我将建立一个新的连接"));
    if(cookieSender.verifyClient(udpSocket,clientHello,peerAddress,peerPort)){
        emit errorMessage("开始 握手");
        std::unique_ptr<QDtls> newconnection(new QDtls(QSslSocket::SslServerMode));
        newconnection->setDtlsConfiguration(serverConfiguration);
        newconnection->setPeer(peerAddress,peerPort);
        newconnection->connect(newconnection.get(),&QDtls::pskRequired,this,&DtlsServer::pskRequired);
        knownClients.push_back(std::move(newconnection));
        doHandshake(knownClients.back().get(),clientHello);
    }
    else if(cookieSender.dtlsError() != QDtlsError::NoError){
        emit errorMessage(cookieSender.dtlsErrorString());
    }
    else{
        emit errorMessage("verify failed");
    }
}


void DtlsServer::doHandshake(QDtls *newConnection, const QByteArray &clientHello){
    bool status=newConnection->doHandshake(udpSocket,clientHello);
    if(!status){
        emit errorMessage(newConnection->dtlsErrorString());
        return;
    }
    switch (newConnection->handshakeState()) {
        case QDtls::HandshakeInProgress:
             emit errorMessage("handshake is processing");
            break;
        case QDtls::HandshakeComplete:
            emit errorMessage("handshake completed");
            break;
        default:
            emit errorMessage("maybe something is wrong");
            break;
    }
}

/*当客户端使用DTLS协议进行建立安全连接时，应该先用自己的udp socket给服务端发送一个 信息*/
void DtlsServer::readyRead(){
    qint16 size=udpSocket->pendingDatagramSize(); /*返回2^32-1*/
    if(size<=0) { /*没有足够的缓存读数据了*/
        emit errorMessage("Not have enough mem");
        return;
    }

    QByteArray datagram(size,Qt::Uninitialized);
    QHostAddress peerAddress;
    quint16 peerPort=0;

    const unsigned int bytesRead=udpSocket->readDatagram(datagram.data(),datagram.size(),&peerAddress,&peerPort); /*没有连接0*/
    emit errorMessage("peerInfo : "+peerAddress.toString()+QString::number(peerPort));

    if(bytesRead <= 0 ){
        emit errorMessage("fail to read datagram");
        return;
    }

    datagram.resize(bytesRead);

    if(peerAddress.isNull() || peerPort==0){
        emit errorMessage(tr("failed to extract peer info from %1,%d").arg(peerAddress.toString()).arg(peerPort));
        return;
    }

    const auto client=std::find_if(knownClients.begin(),knownClients.end(),[&](const std::unique_ptr<QDtls>& connection){
        return connection->peerAddress()==peerAddress && connection->peerPort()==peerPort;
    });

    /*此时连接池里没有一个客户端*/
    if(client ==knownClients.end()){
        return handleNewConnection(peerAddress,peerPort,datagram);
    }

    if((*client)->isConnectionEncrypted()){
        decryptDatagram(client->get(),datagram);
        if((*client)->dtlsError()==QDtlsError::RemoteClosedConnectionError){
            knownClients.erase(client);
        }
        return;
    }
    doHandshake(client->get(),datagram);
}


/*如果客户端进行doHandshake 或 writeEntryDatagram操作，会触发次函数*/
void DtlsServer::TestFunction(){
    emit errorMessage(tr("客户端发来了握手请求信息,请处理................. "));
    qint16 size=udpSocket->pendingDatagramSize(); /*返回2^32-1*/
    if(size<=0) { /*没有足够的缓存读数据了*/
        emit errorMessage("Not have enough mem");
        return;
    }

    /*如果以下的代码执行，说明接收到的数据的size>0*/
    QByteArray datagram(size,Qt::Uninitialized);
    QHostAddress peerAddress;
    quint16 peerPort=0;
    const unsigned int bytesRead=udpSocket->readDatagram(datagram.data(),datagram.size(),&peerAddress,&peerPort); /*没有连接0*/

    if(bytesRead <= 0 ){
        emit errorMessage("fail to read datagram");
        return;
    }


    datagram.resize(bytesRead);

    if(!OneDtls->isConnectionEncrypted()){ /*如果接收到了客户端的数据，但不是进行加密连接的，说明服务端没有进行握手，此时应该先进行握手操作*/
        OneDtls->doHandshake(udpSocket,datagram);
    }
    else{
        switch (OneDtls->handshakeState()) {/*如果已经进行了加密连接，那么直接接收数据回复就可以了*/
            case QDtls::HandshakeComplete:
                ++messageCount;
                emit errorMessage("received data "+OneDtls->decryptDatagram(udpSocket,datagram));
                emit errorMessage("来自 [ "+OneDtls->peerAddress().toString()+","+QString::number(OneDtls->peerPort())+"]"+"time : "+QString::number(messageCount));
                OneDtls->writeDatagramEncrypted(udpSocket,"******这是我写回的数据******");
                break;
            case QDtls::HandshakeInProgress:
                emit errorMessage("handshake is processing ,wait.......");
                break;
            case QDtls::HandshakeNotStarted:
                emit errorMessage("handshake has not been start");
                break;
            case QDtls::PeerVerificationFailed:
                emit errorMessage("peer verify wrong.............");
                break;
            default:
                 break;
        }
    }

}


void DtlsServer::decryptDatagram(QDtls *connection, const QByteArray &clientMessage){
    const QString peer_info=connection->peerAddress().toString()+QString::number(connection->peerPort());
    const QByteArray datagram=connection->decryptDatagram(udpSocket,clientMessage);
    if(datagram.size()){
        emit datagramReceived(peer_info,clientMessage,datagram);
        connection->writeDatagramEncrypted(udpSocket,peer_info.toUtf8());
    }
    else if(connection->dtlsError() == QDtlsError::NoError){
        emit errorMessage(peer_info+": "+"0 byte datagram, could be re-connect attempt?");
    }
    else {
        emit errorMessage(peer_info+": "+connection->dtlsErrorString());
    }
    return;
}


void DtlsServer::shudown(){
    for (const auto& connection : knownClients){
        if(connection){
            connection->shutdown(udpSocket);
        }
    }
    udpSocket->close();
}


unsigned int DtlsServer::function(){
    qint16 size=udpSocket->pendingDatagramSize(); /*返回2^32-1*/
    if(size<=0) {   return 0;}
    QByteArray datagram(size,Qt::Uninitialized);
    QHostAddress peerAddress;
    quint16 peerPort=0;
    unsigned int bytesRead=udpSocket->readDatagram(datagram.data(),datagram.size(),&peerAddress,&peerPort);
    return  bytesRead;;
}


void DtlsServer::handshakeTest(){
    return;
}
