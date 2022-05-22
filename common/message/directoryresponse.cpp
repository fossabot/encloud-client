#include "directoryresponse.h"

DirectoryResponse::DirectoryResponse(){

}

const Directory &DirectoryResponse::getDirectory() const
{
    return directory;
}

void DirectoryResponse::setDirectory(const Directory &newDirectory)
{
    directory = newDirectory;
}
