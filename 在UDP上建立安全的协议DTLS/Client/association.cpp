#include    "association.h"

/**
* @brief    初始化udp socket 初始化 dtls configuration,和一些相关功能的槽函数的设置
*
* @return None
*/
Association::Association(const QHostAddress& address,quint16 port,const QString& connectionName):
                                          name(connectionName),crypto(QSslSocket::SslClientMode){
    initUdpSocket();/*初始化套接字*/
    QSslConfiguration configuration=initSslConfiguration();/*初始化dtls配置 ，需要的密钥 和证书都应在这里配置*/
    crypto.setPeer(address,port);/*设置建立安全连接的对方的ip和端口*/
    crypto.setDtlsConfiguration(configuration);/*设置配置*/
    udpSocket->connectToHost(address,port);/*使用udp socket 连接到服务端 用来 doHandshake */
    connect(&crypto,&QDtls::handshakeTimeout,this,&Association::handshakeTimeout); /*触发握手超时的信号*/
    connect(&crypto,&QDtls::pskRequired,this,&Association::pskRequired);/*触发psk密码套件*/
    connect(udpSocket,&QUdpSocket::readyRead,this,&Association::readyRead);/*触发 服务端发来的doHandshake 和 writeDatagramEncrypted*/
    PingTimer=new QTimer();/*设置一个定时器*/
    PingTimer->setInterval(3000); /*设置定时区间长度*/
    connect(PingTimer,&QTimer::timeout,this,&Association::pingTimeOut);/*当超时事件发生时触发定时器*/
}


Association::~Association(){
    delete  udpSocket;
}


/**
* @brief  获得所有的IP4地址
*
* @return List 包含所有的ip4  在手机上第一个是运营商的ip4 第二个是环回地址
* win10却不是这么返回的
*/
QList<QHostAddress> Association::getAllIPV4Address(){
    QList<QHostAddress> ipv4List=QNetworkInterface::allAddresses();
    return ipv4List;
}


/**
* @brief  初始化udp 套接字
*
* @return 绑定状态
*/
bool Association::initUdpSocket(){
    udpSocket=new QUdpSocket();
   status=udpSocket->bind(QHostAddress("192.168.158.1"),55551);/*udp socket 绑定 并返回绑定成功否？*/
   // status=udpSocket->bind(getAllIPV4Address().at(0),55551);
    return status;
}


/**
* @brief  初始化Dtls配置
*
* @return 设置好的配置
*/
QSslConfiguration Association::initSslConfiguration(){
    QSslConfiguration configuration=QSslConfiguration::defaultConfiguration(); /*设置默认的dtls配置*/
    configuration.setPeerVerifyMode(QSslSocket::VerifyNone);/*点对点之间不需要验证*/
    configuration.setProtocol(QSsl::DtlsV1_0); /*设置配置的协议*/
    configuration.setDtlsCookieVerificationEnabled(false);/*不需要验证对等方的cook*/
    return configuration;/*返回这个配置*/
}


void Association::udpSocketConnected(){
    startHandshake();
}


/**
* @brief 向主函数返回绑定的状态
*
* @return  string
*/
QString Association::udpSocketBindStatus(){
    if(status){
        return  QString("成功绑定到 ["+udpSocket->localAddress().toString()+","+QString::number(udpSocket->localPort())+"]");
    }
    return QString("绑定失败55551");
}


/**
* @brief  向主函数返回udp socket连接服务器的状态
*
* @return string
*/
QString Association::udpSocketConnectStatus(const QHostAddress& address,quint16 port){
        if(udpSocket->state() == QAbstractSocket::ConnectedState){
            return  QString("*******connect server succ,server is ["+address.toString()+","+QString::number(port)+"]");
        }
        return QString("*******connect server is processing, server is ["+address.toString()+","+QString::number(port)+"]");
}


/**
* @brief 处理没有成功握手 再次握手
*
* @return void
*/
void Association::startHandshake(){
    if(udpSocket->state() == QAbstractSocket::ConnectedState){
        emit errorMessage("success connected ");
    }
    else {
        emit errorMessage("fail connected");
        return;
    }
    crypto.doHandshake(udpSocket,name.toUtf8());
}


/**
* @brief 握手超时的处理
*
* @return    None
*/
void Association::handshakeTimeout(){
    emit errorMessage("handshake time out !!!");
    if(!crypto.handleTimeout(udpSocket)){
        emit errorMessage(crypto.dtlsErrorString());
    }
}


/**
* @brief  当需要密码套件时这里提供
*
* @return None
*/
void Association::pskRequired(QSslPreSharedKeyAuthenticator* auth){
    emit errorMessage(tr("providing a pre_shared key ").arg(name));
    auth->setIdentity(name.toLatin1()); /*设置客户端的认证名*/
    QByteArray arr="meng";
    auth->setPreSharedKey(arr);/*设置一个共享密钥 ，服务端也应该有这个密钥用来解密客户端发送的消息*/
}


/**
* @brief 当服务器进行doHandshake和writeDatagramEncrypted操作，会触发此函数* 即使看明白了逻辑也要写注释啊！！！！！不然以后真看不懂了！！！
*
* @return void
*/
void Association::readyRead(){
    /*如果套接字没有足够的缓存空间了直接返回 无法读取数据，更连服务端回复的doHandshake发来的clientHello信息都无法接收*/
    if(udpSocket->pendingDatagramSize()<=0){
        emit  errorMessage("Not have enough mem");
        return;
    }
    QByteArray datagram(udpSocket->pendingDatagramSize(),Qt::Uninitialized);/*/*如果套接字有足够的字节缓存空间，分配一块未初始化的datagram*/
    const qint64 bytesRead=udpSocket->readDatagram(datagram.data(),datagram.size());/*读取它的字节和大小*/
    if(bytesRead<=0){/*如果该数据的字节大小为0直接返回*/
        emit errorMessage("not have  data to read ");
        return;
    }
    datagram.resize(bytesRead);/*否则将未初始化的datagram的尺寸大小resize为你读到的字节的大小，datagram用来存放解密的数据 也就是说你读到的加密数据和解密数据的size是一样的*/
    /*如果你已经和服务端建立了加密连接，直接用dtls 向服务端写加密后的数据就可以了或解密服务端发来的数据*/
    if(crypto.isConnectionEncrypted()){
            ++messageReceivedTime;
            crypto.writeDatagramEncrypted(udpSocket,"******我收到了你的加密信息***********"); /*用共享密钥解密服务端发来的消息*/
            const QByteArray plainText=crypto.decryptDatagram(udpSocket,datagram);/*加密消息 发送给服务端*/
            /*如果你读到的text的size>0，直接递交到服务端的窗口显示这个消息*/
            if(plainText.size()){
                emit serverResponse(name,plainText);
                emit errorMessage("[peer address,peer port]  : ["+crypto.peerAddress().toString()+","+QString::number(crypto.peerPort())+"]"+" time : "
                                                    +QString::number(messageReceivedTime));
            }
            /*如果你在安全连接中出现了错误，关闭所使用的udp socket ，所建立的安全连接全部失效*/
            if(crypto.dtlsError()==QDtlsError::RemoteClosedConnectionError){
                emit errorMessage(QString("%1shut dowm alert receivedf").arg(name));
                udpSocket->close();
                return;
            }
        }
        /*如果你没有建立安全连接，说明你前面没有握手成功*/
        else{
            /*再次进行握手 并检查握手状态，我用switch 语句替代,好像没有必要，因为我知道他一定是握手没有成功，只需要再次握手就可以了*/
            if(!crypto.doHandshake(udpSocket,datagram)){
                emit errorMessage("hand shake error");
            }
            /*如果上面的握手成功了 仅仅发送一个提示*/
            if(crypto.handshakeState()==QDtls::HandshakeComplete){
                emit errorMessage("hanshake complate , will entry data transport !");
            }
            /*如果已经建立起了加密连接 那么就等着触发定时器 发送pingTimeOut slot 所发送的信息 用来测试*/
            if(crypto.isConnectionEncrypted()){
                emit errorMessage("encrypted connect is  constructed  successly");
                PingTimer->start();
                pingTimeOut(); /*感觉它可有可无*/
            }
            else {
                emit errorMessage("handshake is contining");
            }

        }
}


/**
* @brief  一个占位函数
*
* @return None
*/
void Association::FunctionTest(){
    startHandshake();
}


/**
* @brief   pingTimeOut的响应
*
* @return None
*/
void Association::pingTimeOut(){
    static const QString message=QString("i am %1 ,please,accept my ping %2");
    const qint64 written=crypto.writeDatagramEncrypted(udpSocket,message.arg(name).arg(ping).toUtf8());
    if(written<=0){
        emit errorMessage(tr("%1 failed to send a ping %2").arg(name,crypto.dtlsErrorString()));
        PingTimer->stop();
        return;
    }
    ping++;
}


/**
* @brief  一个占位函数
*
* @return None
*/
void Association::TestHandshakeToServer(){
    emit errorMessage("*********Test Start************* ");
    QUdpSocket *parm_udpSocket=new QUdpSocket();
    bool status=parm_udpSocket->bind(QHostAddress("192.168.158.1"),55555);
    if(status){
        emit errorMessage("bind successed!");
    }
    parm_udpSocket->connectToHost(QHostAddress("192.168.158.1"),7755);
    if(parm_udpSocket->state()==QUdpSocket::ConnectedState){
        emit errorMessage("connect to host successed!");
    }
    QDtls *parm_dtls=new QDtls(QSslSocket::SslClientMode);
    QSslConfiguration conf=QSslConfiguration::defaultConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::DtlsV1_0);
    conf.setDtlsCookieVerificationEnabled(false);
    parm_dtls->setDtlsConfiguration(conf);
    parm_dtls->setPeer(QHostAddress("192.168.158.1"),7755);
    connect(udpSocket,&QUdpSocket::readyRead,this,&Association::readyRead);
    parm_dtls->doHandshake(udpSocket);
    connect(parm_dtls,&QDtls::pskRequired,this,&Association::pskRequired);
}





