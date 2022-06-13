#ifndef LOGGER_H
#define LOGGER_H
#include "MainWidget.h"
#include <QObject>
#include <QTextBrowser>
#include "SimulationCore_global.h"
#include <array>
#include <string_view>
#include <QString>
#include <QStringView>

#define LOG_DEBUG() \
    if (kDebug >= CurrentLogLevel()) Logger{}.AsLValue()

//static constexpr size_t LOGGER_BUFFER_SIZE{ 1024U };


/**
 * @brief The LogHelperBuffer class
 */
class SIMULATION_CORE_SHARED_EXPORT LogHelperBuffer final {
    using char_buff = std::array<char, 1024>;

public:
    void put(std::string_view view) {
        std::copy(std::begin(view), std::end(view), m_buffer.data() + std::char_traits<char>::length(m_buffer.data()));
    }

//    void putQString(QStringView str) {
//        std::copy(std::begin(str), std::end(str), m_buffer.data() + std::char_traits<char>::length(m_buffer.data()));
//    }

    void putException(std::exception * ex) {
        put(ex->what());
    }

    template<typename TNumber>
    void putArithmetic(TNumber const val) {
        put(std::to_string(val));
    }

    char_buff * getBuffer() noexcept {
        return &m_buffer;
    }

private:
    char_buff m_buffer{};
};


/**
 * @brief The BufferStd struct
 */
struct SIMULATION_CORE_SHARED_EXPORT BufferStd final : public std::streambuf {
    explicit BufferStd(LogHelperBuffer& impl) : m_bufImpl(impl) {}

private:
    int_type overflow(int_type c) override { };
    std::streamsize xsputn(const char_type* s, std::streamsize n) override {};
    LogHelperBuffer& m_bufImpl;
};


/**
 * @brief The Logger class
 */
class SIMULATION_CORE_SHARED_EXPORT Logger
{
//    Q_OBJECT
public:
    explicit Logger(/*QObject *parent = nullptr*/);
    ~Logger();
//    Logger& operator << (const QString& s);

    static void setLogger(QTextBrowser *);

    template<typename Type>
    Logger& operator << (const Type& value){
        if constexpr (std::is_constructible<std::string_view, Type>::value) {
            m_buffer.put(value);
        } else if constexpr (std::is_constructible<QString, Type>::value){
            m_buffer.put(value.toStdString());
        } else if constexpr (std::is_base_of<std::exception, Type>::value) {
            m_buffer.putException(value);
        } else if constexpr (std::is_integral<Type>::value) {
            m_buffer.putArithmetic(value);
        } else {
            Stream() << value;
        }
        return *this;
    }

//    Logger& operator << (const char * str);

//    Logger& operator << (const QString& str);
signals:

private:
//    void WriteBuffer();
    std::ostream& Stream() {
        if (!m_lazyStream) {
            m_lazyStream.emplace(m_buffer);
        }
        return m_lazyStream->m_ostream;
    }

private:
//    QString _sBuffer;

    LogHelperBuffer m_buffer;
    struct LazyStream {
        BufferStd m_stdBuffer;
        std::ostream m_ostream;
        explicit LazyStream(LogHelperBuffer& buf) : m_stdBuffer(buf), m_ostream(&m_stdBuffer) {}
    };
    std::optional<LazyStream> m_lazyStream;


    static QTextBrowser * m_pLogBrowser;
};

#endif // LOGGER_H
