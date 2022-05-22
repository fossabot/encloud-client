#pragma once

#include "common/globalmarco.h"
#include "common/message/responsebase.h"
class MessageManager;
class UploadFileResponse : public ResponseBase{
    friend class MessageManager;
public:
    UploadFileResponse();
private:

};


