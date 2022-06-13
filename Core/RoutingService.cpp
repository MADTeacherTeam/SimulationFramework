#include "RoutingService.h"

template <typename T>
static inline QByteArray convertToBytes(T msg)
{
    QByteArray bytes;
    QDataStream data(&bytes, QIODevice::WriteOnly);
    data << msg;
    return bytes;
}

RoutingService::RoutingService(SyncService *sync) : _pSync(sync), _socket(nullptr),
    _server(new QTcpServer(this))
{
    if(_pSync)
        connect(this, &RoutingService::NotifyFinishStep, _pSync, &SyncService::syncPulse);
    _server ->listen(QHostAddress::Any, 4312);
    connect(_server, &QTcpServer::newConnection, this, &RoutingService::incomingConnectionHandler);
}

RoutingService::~RoutingService()
{
    /* Проверить нужно ли удалять сервер и сокет */
    delete _socket;
    delete _server;
}

void RoutingService::NextStep(ServiceTime *)
{
    for (QPointer<QTcpSocket>& sock : _socketsList)
        sendMessageToCluster(sock,api::msg_next_step);
}

void RoutingService::sendMessageToCluster(QTcpSocket* sock, api::typeMessage type)
{
    if (type == api::msg_next_step)
        sock->write(convertToBytes<api::typeMessage> (api::msg_next_step));

}

void RoutingService::incomingConnectionHandler()
{
    QPointer<QTcpSocket> temp_socket = _server->nextPendingConnection();
    connect(temp_socket, &QAbstractSocket::stateChanged, this, &RoutingService::changeSocketState);
    connect(temp_socket, &QAbstractSocket::readyRead, this, &RoutingService::acceptClusterMessage);
    _socketsList.emplace_back(temp_socket);

}

void RoutingService::changeSocketState(QAbstractSocket::SocketState state)
{
    QPointer<QTcpSocket> temp_socket = qobject_cast<QTcpSocket*>(sender());
    if(!temp_socket)
        return;

    if (state == QAbstractSocket::UnconnectedState)
        _socketsList.remove(temp_socket);
}

void RoutingService::acceptClusterMessage()
{
    static quint64 counter = 0;
    counter++;
    if (counter == _socketsList.size())
    {
        counter = 0;
        emit NotifyFinishStep();
    }
}

