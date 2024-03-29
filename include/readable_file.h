#ifndef READABLEFILE_H
#define READABLEFILE_H

#include "file.h"

namespace SS
{
    class ReadableFile : public File {
    public:

        ReadableFile(std::string path) : File(path) { }

        /* read method reads a file with the given path on object creation
        *
        *  @return std::string with file data.
        */
        std::string read();

    };
}
 
#endif
