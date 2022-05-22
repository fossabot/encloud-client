#include "filewindowtreewidget.h"
#include "ui_filewindowtreewidget.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QSignalMapper>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
FileWindowTreeWidget::FileWindowTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWindowTreeWidget)
{
    ui->setupUi(this);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //初始化上下文菜单
    void (QSignalMapper::*map)() = &QSignalMapper::map;
    QSignalMapper *mapper = new QSignalMapper(this);
    int actionSeq = 0;
    QList<QString> actionTextList = {
        "下载", "删除","上传","重命名","分享给好友","新建目录"};
    for(QString actionText : actionTextList){
        QAction *action = new QAction(actionText,this);
        m_actionMap.insert(actionText,action);
        connect(action,&QAction::triggered,mapper,map);
        mapper->setMapping(action, actionSeq++);
    }
    connect(mapper, &QSignalMapper::mappedInt,
            this, &FileWindowTreeWidget::contextMenuActionProcess);

    //初始化双击操作
    connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,
            this, &FileWindowTreeWidget::doubleClickedActionProcess);
}

FileWindowTreeWidget::~FileWindowTreeWidget()
{
    delete ui;
}

void FileWindowTreeWidget::contextMenuEvent(QContextMenuEvent *event){
    QMenu qm(this);
    for( QAction* action : m_actionMap.values()){
        qm.addAction(action);
    }
    qm.exec(event->globalPos());
}

void FileWindowTreeWidget::contextMenuActionProcess(int indx){
    if(indx == 0){
        QString downloadDirPath = QFileDialog::getExistingDirectory(this,"下载到","/home/vick");
        if(downloadDirPath.isEmpty()) {
            return;
        }
        QList<QTreeWidgetItem*> seletedItems =  ui->treeWidget->selectedItems();
        if(seletedItems.isEmpty()) {
            return;
        }
        QList<const DirectoryItem*> dirItems;
        for(QTreeWidgetItem *listItem : seletedItems ){
            QVariant data =  listItem->data(0,Qt::UserRole);
            const DirectoryItem* dirItem = data.value<const DirectoryItem*>();
            dirItems.append(dirItem);
        }
        emit this->downloadFile(m_currentDir,dirItems, downloadDirPath);
    }

    if(indx == 1){
        QList<QTreeWidgetItem*> seletedItems =  ui->treeWidget->selectedItems();
        if(seletedItems.isEmpty()) {
            return;
        }
        QList<const DirectoryItem*> dirItems;
        for(QTreeWidgetItem *treeItem : seletedItems ){
            QVariant data =  treeItem->data(0,Qt::UserRole);
            const DirectoryItem* dirItem = data.value<const DirectoryItem*>();
            dirItems.append(dirItem);
        }
        emit this->deleteFile(m_currentDir,dirItems);
    }

    if(indx == 2){
        QStringList pathList = QFileDialog::getOpenFileNames(NULL,"选择上传文件","/home/vick","*");
        emit this->uploadFile(m_currentDir, pathList);
    }

    if(indx == 3){
        QList<QTreeWidgetItem*> seletedItems =  ui->treeWidget->selectedItems();
        if(seletedItems.isEmpty()) return;
        QVariant variant = seletedItems[0]->data(0,Qt::UserRole);
        const DirectoryItem *item = variant.value<const DirectoryItem*>();
        QString newName = QInputDialog::getText(NULL,"重命名","请输入新名称");
        if(newName.isEmpty()) return;
        emit this->renameFile(m_currentDir, item,newName);
    }
    if(indx == 4){

    }
    if(indx == 5){
        QString newDirName = QInputDialog::getText(NULL,"新建目录","请输入目录名称");
        if(newDirName.isEmpty())return;
        stdoutput << "新建目录输入内容" << newDirName;
        emit this->makeDirectory(m_currentDir, newDirName);
    }
}

void FileWindowTreeWidget::doubleClickedActionProcess(QTreeWidgetItem *item, int column){
    QVariant pDirItemVariant = item->data(0,Qt::UserRole);
    const DirectoryItem *pDirItem = pDirItemVariant.value<const DirectoryItem*>();
    stdoutput << "双击信息";
    stdoutput << " "<< pDirItem->getItemID();
    stdoutput << " "<< pDirItem->getItemType();
    stdoutput << " "<< pDirItem->getItemName();
    if(pDirItem->getItemType() == DIR_TYPE){
        emit this->enterFolder(m_currentDir,pDirItem);
    }
    if(pDirItem->getItemType() == FILE_TYPE){
        QString downloadDirName = QFileDialog::getExistingDirectory(this,"下载到","/home/vick");
        if(downloadDirName.isEmpty()) return;
        QList<const DirectoryItem*> dirItemList;
        dirItemList.append(pDirItem);
        emit this->downloadFile(m_currentDir, dirItemList, downloadDirName);
    }
}

void FileWindowTreeWidget::setDirectory(const Directory *dir){
    ui->treeWidget->clear();
    m_currentDir = dir;
    this->refresh();
}

void FileWindowTreeWidget::refresh(){
    const QList<DirectoryItem> &dirItems = m_currentDir->getItems();
    stdoutput << "解析目录项";
    stdoutput << "目录项个数" << dirItems.count();
    for(int i =0; i < dirItems.count(); ++i){
        QTreeWidgetItem * treeWdigetItem = new QTreeWidgetItem();
        stdoutput << "  目录项名称" << dirItems[i].getItemName().data();
        treeWdigetItem->setText(0,dirItems[i].getItemName().split('/').last());
        treeWdigetItem->setText(1,QString::number(dirItems[i].getItemSize()));
        treeWdigetItem->setText(2,dirItems[i].getCreateDate().toString());
        treeWdigetItem->setData(0,Qt::UserRole, QVariant::fromValue<const DirectoryItem*>(&dirItems[i]));
        if(dirItems[i].getItemType() == DIR_TYPE){
            treeWdigetItem->setIcon(0,QIcon(":/icons/folder.png"));
        }
        if(dirItems[i].getItemType() == FILE_TYPE){
            treeWdigetItem->setIcon(0,QIcon(":/icons/file2.png"));
        }
        ui->treeWidget->addTopLevelItem(treeWdigetItem);
    }
}

void FileWindowTreeWidget::clear(){
    ui->treeWidget->clear();
}



