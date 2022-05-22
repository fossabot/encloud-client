#include "settingmanager.h"

SettingManager *SettingManager::s_settingMgr = new SettingManager();
SettingManager::SettingManager(QObject *parent)
    : QObject{parent}
{
    m_configFilePath = "~/home/.config/encloud/config.conf";
    m_serverName = "192.168.3.240";
    m_serverPort = "8080";
    m_uploadConcurrentThreadCount = 2;
    m_downloadConcurrentThreadCount = 2;
}

SettingManager *SettingManager::self(){
    return s_settingMgr;
}
