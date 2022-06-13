#include "Logger.h"
#include <QDebug>
#include <iostream>
#include <ctime>

//MainWidget* Logger::pLog = nullptr;

QTextBrowser * Logger::m_pLogBrowser = nullptr;

Logger::Logger(/*QObject *parent*/) //: QObject(parent)
{
    std::time_t result = std::time(nullptr);
    m_buffer.put(std::asctime(std::localtime(&result)));
//    _sBuffer.reserve(Logger::BUFFER_SIZE);
}

Logger::~Logger()
{
//    WriteBuffer();
//    if (m_pLogBrowser != nullptr) {
//        m_pLogBrowser->append(QString(m_buffer.getBuffer()->data()));
//    }
    std::cerr << m_buffer.getBuffer()->data();
}

//Logger &Logger::operator <<(const QString &s)
//{
//    if (_sBuffer.length() + s.length() > LOGGER_BUFFER_SIZE) {
//        WriteBuffer();
//    }

//    _sBuffer += s;
//    return *this;
//}

void Logger::setLogger(QTextBrowser * browser)
{
    Logger::m_pLogBrowser = browser;
}

//Logger &Logger::operator <<(const char *str)
//{
//    m_buffer.put(str);
//}

//Logger &Logger::operator <<(const QString &str)
//{
//    m_buffer.put(str.toStdString());
//}

//void Logger::WriteBuffer()
//{
////    qDebug() << _sBuffer;
////    Logger::pLog->logMessage(_sBuffer);
//    if (m_pLogBrowser != nullptr) {
//        m_pLogBrowser->append(_sBuffer);
//    }
//    _sBuffer.clear();
//}

//template<typename Type>
//SIMULATION_CORE_SHARED_EXPORT Logger &Logger::operator <<(const Type &value)
//{

//}
