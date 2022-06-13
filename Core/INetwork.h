#ifndef INETWORK_H
#define INETWORK_H

#include <QObject>
#include "api/IAgent.h"
#include "ServiceTime.h"

class INetwork : public QObject
{
    Q_OBJECT
public:
    virtual ~INetwork() {}

    // virtual void CreateAgent(api::IAgent ** ptr) = 0;
    virtual void AddAgent(api::IAgent * pA) = 0;

public slots:
    virtual void NextStep(ServiceTime *) = 0;

signals:
    virtual void NotifyFinishStep() = 0;

};

Q_DECLARE_INTERFACE(INetwork, "INetwork")

#endif // INETWORK_H
