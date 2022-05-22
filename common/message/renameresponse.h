#ifndef RENAMERESPONSE_H
#define RENAMERESPONSE_H

#include "responsebase.h"
class MessageManager;
class RenameResponse : public ResponseBase
{
    friend class MessageManager;
public:
    RenameResponse();
};

#endif // RENAMERESPONSE_H
