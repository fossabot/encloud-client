#include "mkdirrequest.h"

MkdirRequest::MkdirRequest()
{

}

const QString &MkdirRequest::getDirectoryID() const
{
    return directoryID;
}

void MkdirRequest::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

const QByteArray &MkdirRequest::getDirectoryName() const
{
    return directoryName;
}

void MkdirRequest::setDirectoryName(const QByteArray &newDirectoryName)
{
    directoryName = newDirectoryName;
}

