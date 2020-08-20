#ifndef _DAK_SCRIPT_AST_TYPE_H
#define _DAK_SCRIPT_AST_TYPE_H

#include <dak_std/assert.h>
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <unordered_map>

namespace dak_script
{
enum AST_Type_Kind
{
	TYPE_KIND_STRUCT,
	TYPE_KIND_ENUM,
	TYPE_KIND_ALIAS,
	TYPE_KIND_U8,
	TYPE_KIND_U16,
	TYPE_KIND_U32,
	TYPE_KIND_I8,
	TYPE_KIND_I16,
	TYPE_KIND_I32,
	TYPE_KIND_F32,
	TYPE_KIND_F64
};
struct AST_Type_Struct_Data
{
};
struct AST_Type_Enum_Data
{
};
struct AST_Type_Alias_Data
{
};

class AST_Type_Map;
// in theory this should improve speed over a ptr
// most of the time all that is needed is the kind of the type
// which should already be in cache
class AST_Type_Ref
{
	AST_Type_Kind m_kind;
	union {
		AST_Type_Struct_Data *mp_struct;
		AST_Type_Enum_Data *mp_enum;
		AST_Type_Alias_Data *mp_alias;
		void *mp_ptr;
	};

public:
	AST_Type_Ref(AST_Type_Kind kind, void *ptr)
	    : m_kind{kind}, mp_ptr{ptr} {};
	AST_Type_Struct_Data *get_struct()
	{
		_dak_assert(m_kind == TYPE_KIND_STRUCT);
		return mp_struct;
	}
	AST_Type_Enum_Data *get_enum()
	{
		_dak_assert(m_kind == TYPE_KIND_ENUM);
		return mp_enum;
	}
	AST_Type_Alias_Data *get_alias()
	{
		_dak_assert(m_kind == TYPE_KIND_ALIAS);
		return mp_alias;
	}
	AST_Type_Ref(const AST_Type_Ref &r)
	{
		m_kind = r.m_kind;
		mp_ptr = r.mp_ptr;
	}
};

class AST_Type_Map
{

	dak_std::vector<AST_Type_Struct_Data *> m_struct;
	dak_std::vector<AST_Type_Alias_Data *> m_alias;
	dak_std::vector<AST_Type_Enum_Data *> m_enum;
	std::unordered_map<dak_std::string, AST_Type_Ref> m_types;

public:
	AST_Type_Ref add_new(AST_Type_Kind kind)
	{
		void *ptr = nullptr;
		switch (kind)
		{
			case TYPE_KIND_STRUCT:
			{
				AST_Type_Struct_Data *p =
				    new AST_Type_Struct_Data();
				m_struct.push_back(p);
				ptr = p;
			}
			break;
			case TYPE_KIND_ENUM:
			{
				AST_Type_Enum_Data *p =
				    new AST_Type_Enum_Data();
				m_enum.push_back(p);
				ptr = p;
			}
			break;

			case TYPE_KIND_ALIAS:
			{
				AST_Type_Alias_Data *p =
				    new AST_Type_Alias_Data();
				m_alias.push_back(p);
				ptr = p;
			}
			break;
			case TYPE_KIND_U8:
			case TYPE_KIND_U16:
			case TYPE_KIND_U32:
			case TYPE_KIND_I8:
			case TYPE_KIND_I16:
			case TYPE_KIND_I32:
			case TYPE_KIND_F32:
			case TYPE_KIND_F64:
				ptr = nullptr;
				break;
		}

		return AST_Type_Ref(kind, ptr);
	}
};

} // namespace dak_script

#endif