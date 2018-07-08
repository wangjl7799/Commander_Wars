#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QVector>
#include <QMutex>


#include "network/NetworkInterface.h"

class TxTask;
class RxTask;
class QTcpServer;
class QTcpSocket;
class QNetworkSession;

class TCPServer : public NetworkInterface
{
    Q_OBJECT
public:
    TCPServer();
    virtual ~TCPServer();
public slots:
    virtual void connectTCP(const QString& adress);
    virtual void disconnectTCP();
    void onConnect();

    /**
     * @brief sendData send Data with this Connection
     * @param data
     */
    virtual void sendData(QByteArray data, Mainapp::NetworkSerives service, bool blocking);
    virtual void sessionOpened();
signals:
    void sig_sendData(QByteArray data, Mainapp::NetworkSerives service, bool blocking);
private:
    QMutex TaskMutex;
    QVector<RxTask*> pRXTasks;
    QVector<TxTask*> pTXTasks;
    QVector<QTcpSocket*> pTCPSockets;
    QTcpServer* pTCPServer;
};

#endif // TCPSERVER_H