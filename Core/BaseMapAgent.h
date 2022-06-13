#ifndef BASEMAPAGENT_H
#define BASEMAPAGENT_H

#include <QObject>
#include <QPointer>
#include <QImage>

#include "api/IAgent.h"
#include "api/IMessage.h"
#include "SimulationCore_global.h"
#include "MapGeoObject.h"

class SIMULATION_CORE_SHARED_EXPORT BaseMapAgent : public api::IAgent
{
    Q_OBJECT
public:
    BaseMapAgent(MapGeoObject*);
    virtual ~BaseMapAgent(){};
    virtual QString& GetAgentName() = 0;
    virtual QPointF GetPosition() = 0;
    void RedrawMObject();
    void SetMObjectPos(QPointF);
    MapGeoObject *getGeoObject();

public slots:
    virtual void Step(ServiceTime *) = 0;
    virtual void SendMessage() = 0;
    virtual void ReciveMessage(api::IMessage *) = 0;
    virtual void Serialize() = 0;
    virtual void Deserialize() = 0;
    virtual AgentType GetType() = 0;

protected:
     MapGeoObject * _pMapObject;

};

#endif // BASEMAPAGENT_H
