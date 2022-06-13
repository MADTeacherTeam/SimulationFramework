#include "SyncService.h"
#include <QDebug>

#include <iostream>
#include <QThread>
SyncService::SyncService(INetwork *network, QObject *parent) : QObject(parent), _pNetwork(network), _pTime(ServiceTime::getInstance()), _isRuning(true)
{

}

void SyncService::syncPulse()
{
//    while (true) {
//        foreach(auto test, asd) {

//        }
//    }

}

void SyncService::startStep()
{
    // TODO: Check eq time and sim time
    while (!QThread::currentThread()->isInterruptionRequested()) {
        ++(*_pTime);
        emit setDateTimeOnWidget(_pTime);
        QThread::usleep(1);
        _pNetwork->NextStep(_pTime);
        QThread::msleep(10);
    }
}

void SyncService::stopStep()
{
    _isRuning = false;
}

void SyncService::pauseStep()
{

}

void SyncService::resumeStep()
{
    _isRuning = true;
}


