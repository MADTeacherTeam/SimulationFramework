#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QThread>

#include "SimulationCore_global.h"

#include "MapGraphicsAPI.h"
#include "api/IMessageHandler.h"
#include "Core/LocalService.h"

namespace Ui {
class MainWidget;
}

class SIMULATION_CORE_SHARED_EXPORT MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(api::IMessageHandler* message_handler, QWidget * graphics_widget = nullptr, QWidget *parent = nullptr);
    ~MainWidget();
    void AddAgent(api::IAgent*);
    QMap< QString, api::IAgent * >* GetMapOfAgents();
    QWidget * GetGraphicsWidget() const;
    void LogMessage(QString);

signals:
    void SyncServiceStart();
    void SyncServiceStop();
public slots:
//    void logMessage(const QString & msg);
    void stopSimulation();
    void resumeSimulation();

private:
    LocalService* _localServ;
    SyncService* _syncServ;
    Ui::MainWidget *ui;
    QWidget * _pGraphicsWidget;
    QThread * _pSimThread{nullptr};
};

#endif // MAINWIDGET_H
