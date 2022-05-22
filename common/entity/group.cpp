#include "group.h"

Group::Group()
{

}

qint64 Group::getGroupID() const
{
    return groupID;
}

void Group::setGroupID(qint64 newGroupID)
{
    groupID = newGroupID;
}

const QString &Group::getGroupName() const
{
    return groupName;
}

void Group::setGroupName(const QString &newGroupName)
{
    groupName = newGroupName;
}

const QDateTime &Group::getCreateDate() const
{
    return createDate;
}

void Group::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}
