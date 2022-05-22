#pragma once

#include "common/globalmarco.h"
#include "common/message/responsebase.h"
#include <QDateTime>
class MessageManager;
class RegResponse: public ResponseBase{
    friend class MessageManager;
public:
    explicit RegResponse();


private:


signals:

};

