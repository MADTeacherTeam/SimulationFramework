#ifndef CLUSTERROUTINGSERVICE_H
#define CLUSTERROUTINGSERVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <list>
#include <QPointer>

#include "Cluster/ClusterSyncService.h"
#include "api/IAgent.h"
#include "Core/INetwork.h"

class ClusterRoutingService : public INetwork
{
    Q_OBJECT
    Q_INTERFACES(INetwork)

public:
    explicit ClusterRoutingService(QObject *parent = nullptr);

public slots:
    void NextStep(ServiceTime *) override;

signals:

private:
    QPointer<ClusterSyncService> _pSync;
    QTcpSocket* _socket;
    std::list< QPointer<api::IAgent> > _agentsList;
};

#endif // CLUSTERROUTINGSERVICE_H
