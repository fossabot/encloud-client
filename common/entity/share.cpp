#include "share.h"

Share::Share()
{

}

qint64 Share::getShareID() const
{
    return shareID;
}

void Share::setShareID(qint64 newShareID)
{
    shareID = newShareID;
}

qint64 Share::getAccountID() const
{
    return accountID;
}

void Share::setAccountID(qint64 newAccountID)
{
    accountID = newAccountID;
}

qint64 Share::getDestAccountID() const
{
    return destAccountID;
}

void Share::setDestAccountID(qint64 newDestAccountID)
{
    destAccountID = newDestAccountID;
}

const QDateTime &Share::getShareDate() const
{
    return shareDate;
}

void Share::setShareDate(const QDateTime &newShareDate)
{
    shareDate = newShareDate;
}

const QDateTime &Share::getCloseDate() const
{
    return closeDate;
}

void Share::setCloseDate(const QDateTime &newCloseDate)
{
    closeDate = newCloseDate;
}

const QByteArray &Share::getShareKey() const
{
    return shareKey;
}

void Share::setShareKey(const QByteArray &newShareKey)
{
    shareKey = newShareKey;
}

const QByteArray &Share::getFileKeys() const
{
    return fileKeys;
}

void Share::setFileKeys(const QByteArray &newFileKeys)
{
    fileKeys = newFileKeys;
}
