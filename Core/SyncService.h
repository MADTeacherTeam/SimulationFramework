#ifndef SYNCSERVICE_H
#define SYNCSERVICE_H

#include <QObject>
#include <list>
#include <QPointer>

#include "INetwork.h"
#include "ServiceTime.h"

class SyncService : public QObject
{
    Q_OBJECT
public:
    explicit SyncService(INetwork * network, QObject *parent = nullptr);

public slots:
    void syncPulse();
    void startStep();
    void stopStep();
    void pauseStep();
    void resumeStep();

signals:
    void setDateTimeOnWidget(ServiceTime *);
private:
    QPointer<INetwork> _pNetwork;
    ServiceTime * _pTime;
    bool _isRuning;
};

#endif // SYNCSERVICE_H
