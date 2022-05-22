#include "directoryrequest.h"

DirectoryRequest::DirectoryRequest()
{

}

const QString &DirectoryRequest::getDirID() const
{
    return dirID;
}

void DirectoryRequest::setDirID(const QString &newDirID)
{
    dirID = newDirID;
}
