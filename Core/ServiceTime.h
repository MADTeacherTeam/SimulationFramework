#ifndef SERVICETIME_H
#define SERVICETIME_H

#include <QObject>
#include <QDateTime>
#include "SimulationCore_global.h"

class SIMULATION_CORE_SHARED_EXPORT ServiceTime final
{
public:
    static ServiceTime * getInstance();

    quint32 getStepTime() const;
    quint32 getDays();
    quint8 getHours();
    quint8 getMinutes();
    quint8 getSeconds();
    quint8 getMonth();
    quint16 getYear();
    quint8 getDaysPerMonth();
    void setStepTime(const quint32 &value);
    float getCurrentTime() const;
    QDateTime getCurrentDateTime();

    QString getMonthName();

    void operator++();               // prefix
    void operator++(int);            // postfix

    ServiceTime() = default;
    ServiceTime(const ServiceTime&) = delete;
    ServiceTime(ServiceTime&&) = delete;

    void increaseStepTime();
    void decreaseStepTime();

private:
    static ServiceTime* _instance;
    QDateTime _dateTime {QDate::currentDate()};

    quint32 _stepTime = 1;               // stepTime counts in milliseconds (ms)
    const std::array<int, 12> _daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const std::array<int, 12> _daysPerMonthHigh = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

};


#endif // SERVICETIME_H
