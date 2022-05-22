#pragma once

#include "common/globalmarco.h"
#include <QDateTime>
class Share{
public:
    explicit Share();
    qint64 getShareID() const;
    void setShareID(qint64 newShareID);
    qint64 getAccountID() const;
    void setAccountID(qint64 newAccountID);
    qint64 getDestAccountID() const;
    void setDestAccountID(qint64 newDestAccountID);
    const QDateTime &getShareDate() const;
    void setShareDate(const QDateTime &newShareDate);
    const QDateTime &getCloseDate() const;
    void setCloseDate(const QDateTime &newCloseDate);
    const QByteArray &getShareKey() const;
    void setShareKey(const QByteArray &newShareKey);
    const QByteArray &getFileKeys() const;
    void setFileKeys(const QByteArray &newFileKeys);

private:
    qint64          shareID;
    qint64          accountID;
    qint64          destAccountID;
    QByteArray      shareKey;
    QByteArray      fileKeys;
    QDateTime       shareDate;
    QDateTime       closeDate;


};

