#include "ServiceTime.h"


ServiceTime * ServiceTime::_instance = nullptr;

ServiceTime *ServiceTime::getInstance() {
    if (_instance == 0)
    {
        _instance = new ServiceTime;


    }
    return _instance;
}

quint32 ServiceTime::getStepTime() const
{
    return _stepTime;
}

void ServiceTime::setStepTime(const quint32 &value)
{
    _stepTime = value;
}

quint32 ServiceTime::getDays()
{
    return _dateTime.toString("dd").toInt();
}

quint8 ServiceTime::getHours()
{
    return _dateTime.toString("hh").toInt();;
}

quint8 ServiceTime::getMinutes()
{
    return _dateTime.toString("mm").toInt();
}

quint8 ServiceTime::getSeconds()
{
    return _dateTime.toString("ss").toInt();
}

quint8 ServiceTime::getMonth()
{
    return _dateTime.toString("MM").toInt();
}

quint16 ServiceTime::getYear()
{
    return _dateTime.toString("yyyy").toInt();
}

quint8 ServiceTime::getDaysPerMonth()
{
//    if (_year % 4 == 0)
//        return _daysPerMonthHigh[_month - 1];
//    else
//        return _daysPerMonth[_month - 1];
    return 0;
}

float ServiceTime::getCurrentTime() const
{
    return _dateTime.toString("hh").toInt() + (float)_dateTime.toString("mm").toInt() / 60 + (float)_dateTime.toString("ss").toInt() / 3600;
}

void ServiceTime::operator++()
{
   _dateTime =  _dateTime.addSecs(_stepTime);
}

void ServiceTime::increaseStepTime()
{
    _stepTime += _stepTime;
}

void ServiceTime::decreaseStepTime()
{
    if (_stepTime - _stepTime / 2 >=1)
        _stepTime -= _stepTime / 2;
}

void ServiceTime::operator++(int)
{
    this->operator++();
}



QDateTime ServiceTime::getCurrentDateTime()
{
    return _dateTime;
}

QString ServiceTime::getMonthName()
{
    return _dateTime.toString("MMM");
}
