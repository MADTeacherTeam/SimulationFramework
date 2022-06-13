#include "LocalService.h"

LocalService::LocalService()
{

}

LocalService::LocalService(api::IMessageHandler* pMsgHndl) :
    _messageHandler(pMsgHndl)
{
//    connect(this, &LocalService::NotifyFinishStep,
//            _pSync, &SyncService::syncPulse);


}

LocalService::~LocalService()
{
    delete _messageHandler;
    for (auto& agent: _agents)
        delete agent;
    _agents.clear();
}

void LocalService::NextStep(ServiceTime * ptr)
{
    for (const auto & agent : _agents) {
//        for (const auto & agent : *population) {
//            agent->Step(ptr);
//        }
        agent->Step(ptr);
    }
}

QMap< QString, api::IAgent * >* LocalService::GetAgets()
{
    return &_agents;
}

void LocalService::AddAgent(api::IAgent *pAgent)
{
    connect(pAgent, &api::IAgent::SendMessageToNetwork,
            this, &LocalService::messageProcessing);
    _agents.insert(_agents.end(), pAgent->GetAgentName(), pAgent);
}

void LocalService::acceptAnswer()
{
//    static quint64 counter = 0;
//    counter++;
//    if (_agentsList.size() == counter) {
//        counter = 0;
//        emit NotifyFinishStep();
//    }
}

void LocalService::messageProcessing(api::IMessage * msg)
{
    _messageHandler->MessageHandle(msg, &_agents);
}
