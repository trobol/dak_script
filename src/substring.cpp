#include <dak_script/substring.h>
#include <cassert>

namespace dak::script {

    substring::substring(const std::string &src, size_t start, size_t size) : mSize{size}, mPtr{(src.c_str()+start)} {
        assert((start+size) <= src.size());
    }

}