#ifndef IAUCTION_H
#define IAUCTION_H

#include "IAgent.h"
#include <QDateTime>
#include <QJsonObject>

namespace api {

class IAuction{
public:
    virtual ~IAuction() {};
    virtual void OfferPrice(IAgent *, quint32) = 0;
    virtual void Refuse(IAgent *) = 0;
    virtual QJsonObject GetLot() = 0;
    virtual void FinishAuction() = 0;
    virtual QDateTime& GetFinishTime() = 0;
    virtual quint32 GetPrice() = 0;
    virtual bool IsFinish() = 0;
    virtual std::pair<quint32, IAgent *> GetResult() = 0;
protected:
    QJsonObject _lot;
    IAgent * _owner;
    QDateTime _finishTime;
    quint32 _price;
    std::vector<std::pair<quint32, IAgent*>> _candidates;
    bool _isFinish;
};
}

#endif // IAUCTION_H
