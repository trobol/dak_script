#ifndef _DAK_SCRIPT_LLVM_IR_SERIALIZER_H
#define _DAK_SCRIPT_LLVM_IR_SERIALIZER_H

#include "line.h"
#include <fstream>

namespace dak_script
{
class LLVM_IR_Module;

class LLVM_IR_Serializer
{
public:
	void serialize(LLVM_IR_Module *);

private:
	unsigned int m_reg_index;
	void serialize_context(std::ofstream &, LLVM_IR_Context *);
	void serialize_line(std::ofstream &output, const LLVM_IR_Line &line);
};
}; // namespace dak_script
#endif