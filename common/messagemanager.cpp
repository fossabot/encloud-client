#include "messagemanager.h"
#include "settingmanager.h"
#include <QHttpPart>
MessageManager *MessageManager::s_msgMgr = new MessageManager();
MessageManager::MessageManager(QObject *parent)
    : QObject{parent}
{

}

QJsonValue MessageManager::getRegRequestJson(RegRequest *regInfo){
    QJsonObject jsonObject;
    jsonObject.insert("userName",regInfo->getUserName());
    jsonObject.insert("phone",regInfo->getPhone());
    jsonObject.insert("email",regInfo->getEmail());
    jsonObject.insert("accountName",regInfo->getAccountName());
    jsonObject.insert("accountPassword",QString(regInfo->getPassword()));
    jsonObject.insert("checkCode", regInfo->getCheckCode());
    jsonObject.insert("mainKey",QString(regInfo->getMainKey()));
    jsonObject.insert("publicKey",QString(regInfo->getPublicKey()));
    jsonObject.insert("privateKey",QString(regInfo->getPrivateKey()));
    return jsonObject;
}

void MessageManager::phraseRegResponseJson(QJsonValue *responJson, RegResponse *response){
    QVariantMap  map =  responJson->toVariant().toMap();
    phraseResponseBaseFields(&map, response);
}


QJsonValue MessageManager::getLoginRequestJson(LoginRequest *info){
    QJsonObject jsonObject;
    jsonObject.insert("accountName", info->getAccount());
    jsonObject.insert("accountPassword",QString(info->getPassword()));
    return jsonObject;
}

void MessageManager::phraseLoginResponseJson(QJsonValue *responJson, LoginResponse *response){
    QVariantMap  map =  responJson->toVariant().toMap();
    phraseResponseBaseFields(&map, response);
    response->token = map.value("token").toString();

    QVariantMap accountMap = map.value("account").toMap();
    phraseAccountFields(&accountMap,&response->account);
}

QJsonValue MessageManager::getRequestBaseJson(RequestBase *info){
    QJsonObject jsonObject;
    fillRequestBaseFields(&jsonObject, info);
    return jsonObject;
}

void MessageManager::phraseUserSyncResponseJson(QJsonValue *responseJson, UserSyncResponse *response){
    QVariantMap  map =  responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);

    QVariantMap userMap = map.value("user").toMap();
    phraseUserFields(&userMap, &response->user);
}

void MessageManager::phraseAccountSyncResponseJson(QJsonValue *responseJson, AccountSyncResponse *response){
    QVariantMap  map =  responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map, response);

    QVariantMap accountMap = map.value("account").toMap();
    phraseAccountFields(&accountMap,&response->account);
}

void MessageManager::phraseMessageSyncResponseJson(QJsonValue *responseJson, MessageSyncResponse *response){
    QVariantMap  map =  responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map, response);

    QVariantList messagesList = map.value("messages").toList();
    QVariantMap variantMapTemp;
    Message messageTemp;
    for( QVariant messageVariant : messagesList){
        variantMapTemp = messageVariant.toMap();
        phraseMessageFields(&variantMapTemp, &messageTemp);
        response->messages.push_back(messageTemp);
    }
}

QJsonValue MessageManager::getDirectoryRequestJson(DirectoryRequest *info){
    QJsonObject  jsonObject;
    fillRequestBaseFields(&jsonObject,info);
    jsonObject.insert("dirID",info->getDirID());
    return jsonObject;
}

void MessageManager::phraseDirectoryResponseJson(QJsonValue *responseJson, DirectoryResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map, response);

    QVariantMap directoryMap =  map.value("directory").toMap();
    phraseDirectoryFilds(&directoryMap, &response->directory);
}

QJsonValue MessageManager::getRenameRequestJson(RenameRequest *info){
    QJsonObject jsonObject;
    fillRequestBaseFields(&jsonObject,info);

    jsonObject.insert("type",QString::number(info->type));
    jsonObject.insert("directoryID", info->directoryID);
    jsonObject.insert("itemID",info->itemID);
    jsonObject.insert("newName", QString(info->newName));
    return jsonObject;
}

void MessageManager::phraseRenameResponseJson(QJsonValue *responseJson, RenameResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);

}

QHttpMultiPart *MessageManager::getUploadMultiPart(UploadFileRequest *info){
    //封装json
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart jsonPart;
    jsonPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"%1\"")
                       .arg("uploadRequest"));
    jsonPart.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));
    QJsonObject jsonObject;
    jsonObject.insert("directoryID", info->directoryID);
    jsonObject.insert("fileName", QString(info->fileName));
    jsonObject.insert("fileKey", QString(info->fileKey));
    jsonObject.insert("hash",QString(info->hash));
    jsonObject.insert("size", QString::number(info->size));
    jsonPart.setBody(QJsonDocument(jsonObject).toJson());
    multiPart->append(jsonPart);

    //封装文件
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"%1\"; filename=\"%2\"" )
                       .arg("uploadFile")
                       .arg(QString(info->fileName)));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/octet-stream"));
    filePart.setBodyDevice(info->IODevice);
    multiPart->append(filePart);
    return multiPart;
}

void MessageManager::phraseUploadResponseJson(QJsonValue *responseJson, UploadFileResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);

}

QJsonValue MessageManager::getDownloadRequestJson(DownloadRequest *info){
    QJsonObject jsonObject;
    fillRequestBaseFields(&jsonObject,info);
    jsonObject.insert("itemID", info->getItemID());
    return jsonObject;
}

void MessageManager::phraseDownloadResponse(QJsonValue *responseJson, DownloadResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);
}

QJsonValue MessageManager::getMkdirRequestJson(MkdirRequest *info){
    QJsonObject jsonObject;
    fillRequestBaseFields(&jsonObject,info);
    jsonObject.insert("directoryID", info->directoryID);
    jsonObject.insert("directoryName",QString(info->directoryName));
    return jsonObject;
}

void MessageManager::phraseMkdirResponseJson(QJsonValue *responseJson, MkdirResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);
}

QJsonValue MessageManager::getDeleteRequestJson(DeleteRequest *info){
    QJsonObject jsonObject;
    fillRequestBaseFields(&jsonObject,info);
    jsonObject.insert("type",QString::number(info->type));
    jsonObject.insert("directoryID",  info->directoryID);
    jsonObject.insert("itemID", info->itemID);
    return jsonObject;
}

void MessageManager::phraseDeleteResponseJson(QJsonValue *responseJson, DeleteResponse *response){
    QVariantMap map = responseJson->toVariant().toMap();
    phraseResponseBaseFields(&map,response);
}

void MessageManager::fillRequestBaseFields(QJsonObject *jsonObject, RequestBase *info){
    jsonObject->insert("token", info->token);
}

void MessageManager::phraseResponseBaseFields(QVariantMap *map, ResponseBase *response){
    response->statusCode = map->value("statusCode").toInt();
    response->date = QDateTime::fromMSecsSinceEpoch(map->value("date").toLongLong());
    response->serverMessage =  map->value("serverMessage").toString();
}

void MessageManager::phraseAccountFields(QVariantMap *map, Account *account){
    account->setAccountID(map->value("accountID").toInt());
    account->setPassword(map->value("password").toByteArray());
    account->setAccountName(map->value("accountName").toString());
    account->setUserID(map->value("userID").toInt());
    account->setCreateDate(QDateTime::fromMSecsSinceEpoch(map->value("createDate").toLongLong()));
    account->setRootDirID(map->value("rootDirID").toString());
    account->setMainKey(map->value("mainKey").toByteArray());
    account->setPublicKey(map->value("publicKey").toByteArray());
    account->setPrivateKey(map->value("privateKey").toByteArray());
    account->setPublicKey(map->value("publicKey").toByteArray());
}

void MessageManager::phraseUserFields(QVariantMap *map, User *user){
    user->setUserID(map->value("userID").toInt());
    user->setName(map->value("name").toString());
    user->setEmail(map->value("email").toString());
    user->setPhone(map->value("phone").toString());
    user->setRegistrationDate(QDateTime::fromMSecsSinceEpoch(map->value("registrationDate").toLongLong()));
}

void MessageManager::phraseFileFields(QVariantMap *map, File *file){
    file->setFileID(map->value("fileID").toInt());
    file->setAccountID(map->value("accountID").toInt());
    file->setFileName(map->value("fileName").toString());
    file->setHash(map->value("hash").toByteArray());
    file->setFileKey(map->value("fileKey").toByteArray());
    file->setFileSize(map->value("fileSize").toInt());
    file->setUploadDate(QDateTime::fromMSecsSinceEpoch(map->value("uploadDate").toLongLong()));
    file->setIsFromShare(map->value("isFromShare").toBool());
}

void MessageManager::phraseShareFields(QVariantMap *map, Share *share){
    share->setShareID(map->value("shareID").toInt());
    share->setAccountID(map->value("accountID").toInt());
    share->setDestAccountID(map->value("destAccountID").toInt());
    share->setShareKey(map->value("shareKey").toByteArray());
    share->setFileKeys(map->value("fileKeys").toByteArray());
    share->setShareDate(QDateTime::fromMSecsSinceEpoch(map->value("shareDate").toLongLong()));
    share->setCloseDate(QDateTime::fromMSecsSinceEpoch(map->value("closeDate").toLongLong()));
}

void MessageManager::phraseMessageFields(QVariantMap *map, Message *message){
    message->setMsgID(map->value("msgID").toInt());
    message->setMsgSenderID(map->value("msgSenderID").toInt());
    message->setMsgReceiverID(map->value("msgReceiverID").toInt());
    message->setMsgTypeID(map->value("msgTypeID").toInt());
    message->setMsgContent(map->value("msgContent").toString());
}

void MessageManager::phraseDirectoryFilds(QVariantMap *map, Directory *directory){
    directory->setDirectoryID(map->value("directoryID").toString());
    directory->setDirectoryName(map->value("directoryName").toByteArray());
    directory->setDirectorySize(map->value("directorySize").toInt());
    directory->setItemCount(map->value("itemCount").toInt());
    directory->setCreateDate(QDateTime::fromMSecsSinceEpoch(map->value("createDate").toLongLong()));
    directory->setAccessDate(QDateTime::fromMSecsSinceEpoch(map->value("accessDate").toLongLong()));
    directory->setModifyDate(QDateTime::fromMSecsSinceEpoch(map->value("modifyDate").toLongLong()));

    QVariantList itemsVariantList = map->value("items").toList();
    QList<DirectoryItem> dirItemListTemp;
    DirectoryItem  itemTemp;
    QVariantMap variantMapTemp;
    for(QVariant item : itemsVariantList ){
        variantMapTemp = item.toMap();
        phraseDirectoryItemFilds(&variantMapTemp, &itemTemp);
        dirItemListTemp.append(itemTemp);
    }
    directory->setItems(dirItemListTemp);
}

void MessageManager::phraseDirectoryItemFilds(QVariantMap *map, DirectoryItem *item){
    item->setItemType(map->value("itemType").toInt());
    item->setItemID(map->value("itemID").toString());
    item->setItemName(map->value("itemName").toByteArray());
    item->setCreateDate(QDateTime::fromMSecsSinceEpoch(map->value("createDate").toLongLong()));
    item->setItemSize(map->value("itemSize").toInt());
    item->setItemKey(map->value("itemKey").toByteArray());
    item->setItemHash(map->value("itemHash").toByteArray());
}

MessageManager *MessageManager::self(){
    return MessageManager::s_msgMgr;
}
