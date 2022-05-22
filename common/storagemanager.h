#pragma once

#include "globalmarco.h"
#include <QFile>
#include <QFileInfo>

class StorageManager : public QObject{
    Q_OBJECT

//非静态成员
private:
    explicit StorageManager(QObject *parent = nullptr);
public:


private:


//静态成员
public:
    static StorageManager *self();
private:
    static StorageManager *s_storageMgr;


signals:

};

