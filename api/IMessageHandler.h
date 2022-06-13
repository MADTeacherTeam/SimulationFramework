#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H

#include "IAgent.h"
#include "IMessage.h"
#include "SimulationCore_global.h"

namespace  api {

class IMessageHandler {
public:
    virtual ~IMessageHandler(){};
    virtual void MessageHandle(IMessage* msg, QMap<QString, api::IAgent * >*) = 0;
};

};
#endif // IMESSAGEHANDLER_H
