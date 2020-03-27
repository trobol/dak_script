#ifndef _DAK_SCRIPT_READER_H
#define _DAK_SCRIPT_READER_H

#include <vector>
#include <string>

namespace dak::script {
    class Reader {
        public:

            void open(std::string name);
            void close();
            std::vector<std::string> tokenize();

            const char* contents() {
                return m_contents;
            }

            size_t length() {
                return m_length;
            }

            
        private:
            size_t m_length;
            const char* m_contents;
            static const char* map_file(const char* fname, size_t& length);
            static void unmap_file(void* addr, size_t length);
    };
}

#endif