#ifndef LOCALSERVICE_H
#define LOCALSERVICE_H

#include <list>
#include <QPointer>
#include <QJsonObject>

#include "MapGeoObject.h"

#include "Core/INetwork.h"
#include "Cluster/ClusterSyncService.h"
#include "api/IAgent.h"
#include "api/IMessageHandler.h"
#include "api/IMessage.h"
#include "Core/SyncService.h"


class LocalService : public INetwork
{
    Q_OBJECT
    Q_INTERFACES(INetwork)
public:
    explicit LocalService();
    LocalService(api::IMessageHandler* pMsgHndl);
    ~LocalService();
    void NextStep(ServiceTime *) override;
    QMap< QString, api::IAgent * >* GetAgets();

public slots:
    void AddAgent(api::IAgent * pA) override;
    void acceptAnswer();
    void messageProcessing(api::IMessage *);

signals:
    void NotifyFinishStep() override;

private:
    api::IMessageHandler* _messageHandler;
    QMap< QString, api::IAgent * > _agents;
//    std::vector<api::IPopulation *> _agents;
};

#endif // LOCALSERVICE_H
