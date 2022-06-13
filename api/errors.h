#ifndef ERRORS_H
#define ERRORS_H
#include <QException>
#include <cstddef>

class CoreException final : public QException
{
public:
    enum class CoreError : size_t
    {
        ERR_NO_ERROR = 0,
        ERR_BADPARAMS = 1,
        ERR_WRONG_TYPE = 2,

        /* database errors */
        ERR_BAD_CONNECTION = 404,
    };

    CoreException(CoreError err) : _ErrorCode(err) {    }
    CoreException(CoreError err, const QString & err_text) : _ErrorCode(err), _Descrition(err_text) {    }

    ~CoreException() = default;

    void raise() const override {
        throw *this;
    }

    QException * clone() const override{
        return new CoreException(*this);
    }

    const char * what() const throw() override {
        switch (_ErrorCode) {
            case CoreError::ERR_NO_ERROR:
                return "No error, just for fun";
        }
    }

private:
    CoreError _ErrorCode;
    QStringView _Descrition;
};


#endif // ERRORS_H



