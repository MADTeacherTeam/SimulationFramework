#ifndef CLUSTERSYNCSERVICE_H
#define CLUSTERSYNCSERVICE_H

#include <QObject>

class ClusterSyncService : public QObject
{
    Q_OBJECT
public:
    explicit ClusterSyncService(QObject *parent = nullptr);

signals:

};

#endif // CLUSTERSYNCSERVICE_H
