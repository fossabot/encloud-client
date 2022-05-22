#ifndef DIRECTORYREQUEST_H
#define DIRECTORYREQUEST_H

#include "requestbase.h"

class DirectoryRequest : public RequestBase{
public:
    DirectoryRequest();

    const QString &getDirID() const;
    void setDirID(const QString &newDirID);

private:
    QString dirID;

};

#endif // DIRECTORYREQUEST_H
