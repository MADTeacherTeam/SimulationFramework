#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QtGlobal>
#include <QByteArray>

class QJsonObject;
class QString;

namespace api {

class IMessage{
public:
    virtual ~IMessage(){};
    virtual void SetSenderName(const QString&) = 0;
    virtual void SetReceiverName(const QString&) = 0;
    virtual void SetTypeMessage(quint8) = 0;
    virtual void ClearMessage() = 0;
    virtual quint8 GetType() = 0;
};

};
#endif // IMESSAGE_H
