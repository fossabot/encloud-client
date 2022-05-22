#ifndef MKDIRRESPONSE_H
#define MKDIRRESPONSE_H

#include "responsebase.h"
class MessageManager;
class MkdirResponse : public ResponseBase
{
    friend class MessageManager;
public:
    MkdirResponse();
};

#endif // MKDIRRESPONSE_H
