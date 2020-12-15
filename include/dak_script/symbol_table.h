#ifndef _DAK_SCRIPT_SYMBOL_TABLE_H
#define _DAK_SCRIPT_SYMBOL_TABLE_H


#include <unordered_map>
#include <dak_std/vector.h>
#include <dak_std/string.h>

namespace dak_script {
    
    class Symbol_Table {
        std::unordered_map<dak_std::string, uint32_t> m_symbol_map;
        dak_std::vector<dak_std::string> m_symbol_table;
        public:
            uint32_t get_or_append(dak_std::string& symbol);
            dak_std::string& find(uint32_t index);
    };  
};


#endif