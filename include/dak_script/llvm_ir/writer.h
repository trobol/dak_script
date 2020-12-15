#ifndef _DAK_SCRIPT_LLVM_IR_WRITER_H
#define _DAK_SCRIPT_LLVM_IR_WRITER_H

#include <dak_std/string.h>
#include <fstream>

namespace dak_script
{
class LLVM_IR_Writer
{
private:
	std::ofstream m_stream;

	int m_tmp_index;

public:
	void open_function(dak_std::string &name, dak_std::string &type);
	int write_add(dak_std::string lhs, dak_std::string rhs);

	void close_function();
};
} // namespace dak_script

#endif