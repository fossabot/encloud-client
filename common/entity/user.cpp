#include "user.h"

User::User()
{

}

void User::operator=(const User &other)
{

}

qint64 User::getUserID() const
{
    return userID;
}

void User::setUserID(qint64 newUserID)
{
    userID = newUserID;
}

const QString &User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}

const QString &User::getPhone() const
{
    return phone;
}

void User::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &newEmail)
{
    email = newEmail;
}

const QDateTime &User::getRegistrationDate() const
{
    return registrationDate;
}

void User::setRegistrationDate(const QDateTime &newRegistrationDate)
{
    registrationDate = newRegistrationDate;
}
