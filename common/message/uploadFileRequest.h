#pragma once

#include "common/globalmarco.h"
#include "common/message/requestbase.h"
class MessageManager;
class UploadFileRequest{
    friend class MessageManager;
public:
    explicit UploadFileRequest();
    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    const QByteArray &getFileName() const;
    void setFileName(const QByteArray &newFileName);
    const QByteArray &getFileKey() const;
    void setFileKey(const QByteArray &newFileKey);
    const QString &getHash() const;
    void setHash(const QString &newHash);
    qint64 getSize() const;
    void setSize(qint64 newSize);

    QIODevice *getIODevice() const;
    void setIODevice(QIODevice *newIODevice);

private:
    QString     directoryID;
    QByteArray  fileName;
    QByteArray  fileKey;
    QIODevice   *IODevice;
    QString     hash;
    qint64      size;
signals:

};

