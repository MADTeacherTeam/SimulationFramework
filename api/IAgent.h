#ifndef IAGENT_H
#define IAGENT_H

#include <QObject>
#include <QJsonObject>
#include "SimulationCore_global.h"

#include "api/IMessage.h"

class ServiceTime;

namespace api {

class SIMULATION_CORE_SHARED_EXPORT IAgent : public QObject
{
    Q_OBJECT
public:
    enum class AgentType : quint8 {
        Shop,
        Storage,
        Transport
    };
    virtual ~IAgent(){};
    virtual QString& GetAgentName() = 0;
    virtual QPointF GetPosition() = 0;

public slots:
    virtual void Step(ServiceTime *) = 0;
    virtual void SendMessage() = 0;
    virtual void ReciveMessage(api::IMessage *) = 0;
    virtual void Serialize() = 0;
    virtual void Deserialize() = 0;
    virtual AgentType GetType() = 0;

signals:
    void SendMessageToNetwork(api::IMessage *);
};
};
#endif // IAGENT_H
