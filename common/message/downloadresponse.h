#pragma once
#include "common/globalmarco.h"
#include "common/message/responsebase.h"
class MessageManager;
class DownloadResponse : public ResponseBase
{
    friend class MessageManager;
public:
    DownloadResponse();
private:

};


