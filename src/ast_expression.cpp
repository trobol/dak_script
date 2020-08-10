#include <cstdio>
#include <dak_script/ast.h>
#include <dak_script/ast_expression.h>
namespace dak_script
{

#define MAX_INDENT 50
void print_expression(AST_Expression *expr, int indent)
{
	char buffer[MAX_INDENT] = {};

	if (indent > MAX_INDENT)
		indent = MAX_INDENT;

	for (unsigned i = 0; i < indent; i++)
	{
		buffer[i] = '\t';
	}
	printf("%s", buffer);
	if (expr == nullptr)
	{
		printf("nullptr \n");
		return;
	}
	switch (expr->type)
	{
		case AST_EXPRESSION_TYPE_BOP:
		{
			AST_BOP_Expression *bop_expr =
			    dynamic_cast<AST_BOP_Expression *>(expr);
			char c;
			switch (bop_expr->bop)
			{
				case AST_BOP_ADD:
					c = '+';
					break;
				case AST_BOP_SUB:
					c = '-';
					break;
				case AST_BOP_DIV:
					c = '/';
					break;
				case AST_BOP_MULT:
					c = '*';
					break;
				default:
					c = '?';
					break;
			}
			printf("BOP EXPRESSION: %c \n", c);
			print_expression(bop_expr->lhs, indent + 1);
			print_expression(bop_expr->rhs, indent + 1);
		}
		break;
		case AST_EXPRESSION_TYPE_LITERAL:
		{
			AST_Literal_Expression *lit_expr =
			    dynamic_cast<AST_Literal_Expression *>(expr);

			printf("LITERAL EXPRESSION: \n");
		}
		break;
		case AST_EXPRESSION_TYPE_VARIABLE:
		{
			AST_Variable_Expression *var_expr =
			    dynamic_cast<AST_Variable_Expression *>(expr);
			printf("VARIABLE EXPRESSION: %s \n",
			       var_expr->ptr->name.data());
		}
		break;
		case AST_EXPRESSION_TYPE_PAREN:
		{
			printf("PAREN EXPRESSION: \n");
			AST_Paren_Expression *paren_expr =
			    dynamic_cast<AST_Paren_Expression *>(expr);
			print_expression(paren_expr->expr, indent + 1);
		}
		break;
		default:
			printf("UNKNOWN EXPRESSION \n");
			break;
	}
}
} // namespace dak_script
