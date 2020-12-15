#ifndef _DAK_SCRIPT_MODULE_IMPORT_H
#define _DAK_SCRIPT_MODULE_IMPORT_H

namespace dak_script
{
/*
In order to allow for unknown types/functions to be used
a system of 'expectations' from the imported modules

types:
name
members
member functions?


functions:
name
parameters
overloads



TODO:
a large issue is that some types may never be explicitly used in the code


*/

class Function_Import
{
};
class Module_Import
{
};

} // namespace dak_script
#endif