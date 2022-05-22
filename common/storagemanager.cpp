#include "storagemanager.h"

StorageManager *StorageManager::s_storageMgr = new StorageManager();
StorageManager::StorageManager(QObject *parent)
    : QObject{parent}
{

}

StorageManager* StorageManager::self(){
    return  s_storageMgr;
}
