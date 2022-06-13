#ifndef ROUTINGSERVICE_H
#define ROUTINGSERVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>

#include "INetwork.h"
#include "SyncService.h"
#include "../api/types.h"

class RoutingService : public INetwork
{
    Q_OBJECT
public:
    explicit RoutingService(SyncService *sync = nullptr);
    ~RoutingService();
    void NextStep(ServiceTime *) override;
    void sendMessageToCluster(QTcpSocket* sock, api::typeMessage type);

public slots:
    void incomingConnectionHandler();
    void changeSocketState(QAbstractSocket::SocketState state);
    void acceptClusterMessage();
signals:

private:
    QPointer <SyncService> _pSync;
    QTcpSocket* _socket;
    QTcpServer* _server;
    std::list <QPointer <QTcpSocket>> _socketsList;

};

#endif // ROUTINGSERVICE_H
