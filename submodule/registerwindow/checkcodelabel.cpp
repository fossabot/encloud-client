#include "checkcodelabel.h"
#include "common/networkmanager.h"
#include <QMouseEvent>
CheckCodeLabel::CheckCodeLabel(QWidget *parent)
    : QLabel{parent}
{
    this->setText("请检查网络配置");
    setCheckCode();
}

void CheckCodeLabel::setCheckCode(){
    QNetworkRequest request;
    request.setUrl(QUrl(CHECK_CODE_PATH));
    QNetworkReply *reply =  NetworkManager::self()->getHttpMgr()->get(request);
    connect(reply, &QNetworkReply::finished, [this,reply](){
        QPixmap img;
        img.loadFromData(reply->readAll());
        this->setPixmap(img);
    });
}

void CheckCodeLabel::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
        setCheckCode();
    }

}
