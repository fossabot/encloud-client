#ifndef MKDIRREQUEST_H
#define MKDIRREQUEST_H

#include "requestbase.h"
class MessageManager;
class MkdirRequest : public RequestBase
{
    friend class MessageManager;
public:
    MkdirRequest();



    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    const QByteArray &getDirectoryName() const;
    void setDirectoryName(const QByteArray &newDirectoryName);

private:
    QString     directoryID;
    QByteArray  directoryName;
};

#endif // MKDIRREQUEST_H
