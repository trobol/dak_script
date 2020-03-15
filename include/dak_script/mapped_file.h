#ifndef _DAK_SCRIPT_MAPPED_FILE_H
#define _DAK_SCRIPT_MAPPED_FILE_H

#include <string>

namespace dak::script {

    struct MappedFile {
        size_t length;
        const char* contents;
        
    };
}

#endif