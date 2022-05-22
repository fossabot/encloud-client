#pragma once
#include "common/globalmarco.h"
#include <QDateTime>
class User{
public:
    explicit User();
    void  operator=(const User& other);
    qint64 getUserID() const;
    void setUserID(qint64 newUserID);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getEmail() const;
    void setEmail(const QString &newEmail);
    const QDateTime &getRegistrationDate() const;
    void setRegistrationDate(const QDateTime &newRegistrationDate);

private:
    qint64      userID;
    QString     name;
    QString     phone;
    QString     email;
    QDateTime   registrationDate;
};


