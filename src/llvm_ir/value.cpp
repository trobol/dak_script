#include <dak_script/llvm_ir/value.h>

namespace dak_script
{
const LLVM_IR_Type LLVM_IR_Type::reference =
    LLVM_IR_Type(LLVM_IR_TYPE_REFERENCE);

const LLVM_IR_Type LLVM_IR_Type::i8 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 3, true);
const LLVM_IR_Type LLVM_IR_Type::i16 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 4, true);
const LLVM_IR_Type LLVM_IR_Type::i32 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 5, true);

const LLVM_IR_Type LLVM_IR_Type::u8 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 3, false);
const LLVM_IR_Type LLVM_IR_Type::u16 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 4, false);
const LLVM_IR_Type LLVM_IR_Type::u32 = LLVM_IR_Type(LLVM_IR_TYPE_INT, 5, false);

} // namespace dak_script
