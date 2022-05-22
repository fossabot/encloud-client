#include "file.h"

File::File()
{

}

qint64 File::getFileID() const
{
    return fileID;
}

void File::setFileID(qint64 newFileID)
{
    fileID = newFileID;
}

qint64 File::getAccountID() const
{
    return accountID;
}

void File::setAccountID(qint64 newAccountID)
{
    accountID = newAccountID;
}

const QString &File::getFileName() const
{
    return fileName;
}

void File::setFileName(const QString &newFileName)
{
    fileName = newFileName;
}

const QByteArray &File::getHash() const
{
    return hash;
}

void File::setHash(const QByteArray &newHash)
{
    hash = newHash;
}

const QByteArray &File::getFileKey() const
{
    return fileKey;
}

void File::setFileKey(const QByteArray &newFileKey)
{
    fileKey = newFileKey;
}

qint64 File::getFileSize() const
{
    return fileSize;
}

void File::setFileSize(qint64 newFileSize)
{
    fileSize = newFileSize;
}

const QDateTime &File::getUploadDate() const
{
    return uploadDate;
}

void File::setUploadDate(const QDateTime &newUploadDate)
{
    uploadDate = newUploadDate;
}

bool File::getIsFromShare() const
{
    return isFromShare;
}

void File::setIsFromShare(bool newIsFromShare)
{
    isFromShare = newIsFromShare;
}
