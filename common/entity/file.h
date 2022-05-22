#pragma once
#include "common/globalmarco.h"
#include <QDateTime>
class File{
public:
    explicit File();
    qint64 getFileID() const;
    void setFileID(qint64 newFileID);
    qint64 getAccountID() const;
    void setAccountID(qint64 newAccountID);
    const QString &getFileName() const;
    void setFileName(const QString &newFileName);
    const QByteArray &getHash() const;
    void setHash(const QByteArray &newHash);
    const QByteArray &getFileKey() const;
    void setFileKey(const QByteArray &newFileKey);
    qint64 getFileSize() const;
    void setFileSize(qint64 newFileSize);
    const QDateTime &getUploadDate() const;
    void setUploadDate(const QDateTime &newUploadDate);
    bool getIsFromShare() const;
    void setIsFromShare(bool newIsFromShare);

private:
    qint64      fileID;
    qint64      accountID;
    QString     fileName;
    QByteArray  hash;
    QByteArray  fileKey;
    qint64      fileSize;
    QDateTime   uploadDate;
    bool        isFromShare;
signals:

};

