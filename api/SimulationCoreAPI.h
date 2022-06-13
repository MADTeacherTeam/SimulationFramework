#ifndef SIMULATIONCOREAPI_H
#define SIMULATIONCOREAPI_H

#include "../MainWidget.h"
#include "../SimulationCore_global.h"
#include <QWidget>
#include <QDebug>

class SIMULATION_CORE_SHARED_EXPORT SimulationCoreAPI {


public:
    SimulationCoreAPI(api::IMessageHandler* message_handler, QWidget * graphics_widget = nullptr, QWidget * parent = nullptr) : _Main(new MainWidget(message_handler,graphics_widget)) {}

    MainWidget* getMainWidget();
    void run();
    void AddAgent(api::IAgent* agent);
    QMap<QString, api::IAgent *> * GetAgentsMap();

private:
    MainWidget* _Main;
};

inline void SimulationCoreAPI::run() {

}

inline void SimulationCoreAPI::AddAgent(api::IAgent *agent) {
    _Main->AddAgent(agent);
}

inline QMap<QString, api::IAgent *> *SimulationCoreAPI::GetAgentsMap()
{
    _Main->GetMapOfAgents();
}

inline MainWidget *SimulationCoreAPI::getMainWidget() {
        return _Main;
}

#endif // SIMULATIONCOREAPI_H
