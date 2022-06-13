#include "MainWidget.h"
#include "ui_MainWidget.h"

#include <QSharedPointer>
#include <QtDebug>
#include <QThread>
#include <QImage>

#include "HeaderWidget.h"
#include "Core/BaseMapAgent.h"

#include "MapGeoObject.h"
#include "Core/Logger.h"

MainWidget::MainWidget(api::IMessageHandler* message_handler, QWidget * graphics_widget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget), _pGraphicsWidget(graphics_widget)
{
    ui->setupUi(this);
    Logger::setLogger(ui->log_browser);
    _pSimThread = new QThread(this);


    _localServ = new LocalService(message_handler);
    _syncServ = new SyncService(_localServ);

    _localServ->moveToThread(_pSimThread);
    _syncServ->moveToThread(_pSimThread);


//    _pSimThread->start();

    if (nullptr != _pGraphicsWidget) {
        this->ui->mapGraphics_layout->addWidget(_pGraphicsWidget);
    } else {
        MapGraphicsAPI * pMapGraphics = new MapGraphicsAPI(this);
        this->ui->dockWidget->setWidget(pMapGraphics->GetTileConfigWidget());
    //    this->ui->dockWidget->toggleViewAction()->setText("&Layers");
//        connect(pMapGraphics, &MapGraphicsAPI::GeoObjectAdded,
//                _localServ, &LocalService::addAgent);
        connect(this->ui->tools_layout, &HeaderWidget::startSimulation,
                this, &MainWidget::resumeSimulation);
        connect(this->ui->tools_layout, &HeaderWidget::stopSimulation,
                this, &MainWidget::stopSimulation);
        connect(_syncServ, &SyncService::setDateTimeOnWidget,
                this->ui->tools_layout, &HeaderWidget::setDatetime);
        connect(this, &MainWidget::SyncServiceStart, _syncServ, &SyncService::startStep);
        connect(this, &MainWidget::SyncServiceStop, _syncServ, &SyncService::stopStep);
        _pGraphicsWidget = pMapGraphics;
        this->ui->mapGraphics_layout->addWidget(_pGraphicsWidget);
    }
}

MainWidget::~MainWidget()
{
    stopSimulation();
    _pSimThread->wait();

    delete _localServ;
    delete _syncServ;
    delete _pSimThread;
    delete ui;
}

void MainWidget::AddAgent(api::IAgent * agent)
{
    _localServ->AddAgent(agent);
}

QMap<QString, api::IAgent *> *MainWidget::GetMapOfAgents()
{
    return _localServ->GetAgets();
}

QWidget *MainWidget::GetGraphicsWidget() const
{
    return _pGraphicsWidget;
}

void MainWidget::LogMessage(QString text)
{
    Logger() << text;
}

void MainWidget::stopSimulation()
{
    _pSimThread->requestInterruption();
    emit SyncServiceStop();
    _pSimThread->quit();
}

void MainWidget::resumeSimulation()
{
    _pSimThread->start();
    emit SyncServiceStart();
}

//void MainWidget::logMessage(const QString &msg)
//{
//    this->ui->log_browser->append(msg);
//}
