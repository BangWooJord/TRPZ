#include <QException>
#include <QString>

class CustomQtExceptions : public QException
{
public:
    explicit CustomQtExceptions(const QString& msg)
        :m_message(msg){};

    void raise() const override { throw *this; };
    CustomQtExceptions *clone() const override
    { return new CustomQtExceptions(*this); };

    inline void setMessage(const QString& msg) { this->m_message = msg; }
    inline auto Message() { return this->m_message; }

private:
    QString m_message;
};

