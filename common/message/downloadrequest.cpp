#include "downloadrequest.h"

DownloadRequest::DownloadRequest()
{

}

const QString &DownloadRequest::getItemID() const
{
    return itemID;
}

void DownloadRequest::setItemID(const QString &newItemID)
{
    itemID = newItemID;
}
