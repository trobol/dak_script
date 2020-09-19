#ifndef _DAK_SCRIPT_LLVM_IR_WRITER_H
#define _DAK_SCRIPT_LLVM_IR_WRITER_H

#include <fstream>

namespace dak_script
{
class LLVM_IR_Writer
{
private:
	std::ofstream m_stream;

	int m_tmp_index;

public:
	void open_function();
	void close_function();
};
} // namespace dak_script

#endif