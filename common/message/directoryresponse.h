#ifndef DIRECTORYRESPONSE_H
#define DIRECTORYRESPONSE_H

#include "responsebase.h"
#include "common/entity/directory.h"

class MessageManager;
class DirectoryResponse : public ResponseBase{
    friend class MessageManager;
public:
    DirectoryResponse();

    const Directory &getDirectory() const;
    void setDirectory(const Directory &newDirectory);

private:
    Directory directory;

};

#endif // DIRECTORYRESPONSE_H
