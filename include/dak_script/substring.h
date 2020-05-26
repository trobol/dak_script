#ifndef _DAK_SCRIPT_SUBSTRING_H
#define _DAK_SCRIPT_SUBSTRING_H

#include <string>

namespace dak_script {
    /*
        a string that reuses the memory from the original string
    */
    class substring {
        private:
            const char* mPtr;
            size_t mSize;

        public:
            substring(const std::string& src, size_t start, size_t size);
            //returns a copy of the substring
            std::string get();
            //size of the string
            size_t size();

    };
}

#endif