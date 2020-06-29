#ifndef _DAK_SCRIPT_AST_TYPE_H
#define _DAK_SCRIPT_AST_TYPE_H
#include <dak_script/ast/ast.h>
#include <dak_std/vector.h>

namespace dak_script
{
enum Type_Kind
{
	TYPE_KIND_STRUCT,
	TYPE_KIND_ENUM,
	TYPE_KIND_U8,
	TYPE_KIND_U16,
	TYPE_KIND_U32,
	TYPE_KIND_I8,
	TYPE_KIND_I16,
	TYPE_KIND_I32,
	TYPE_KIND_F32,
	TYPE_KIND_F64
};

struct Type_Struct
{
};

struct Type_Enum
{
};

struct Type
{
	Type_Kind kind;
	union {
		Type_Struct *struct_type;
		Type_Enum *enum_type;
	};
};

} // namespace dak_script

#endif