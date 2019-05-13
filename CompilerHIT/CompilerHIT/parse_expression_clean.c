#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 5

void parse_expression_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_SEMICOLON, TOKEN_OPEN_SQUER_PAR, TOKEN_MUL, TOKEN_DIV, TOKEN_ASSIGNMENT };
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON: 
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		parse_variable_clean();
		break;
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		parse_variable_clean();
		break;
	case TOKEN_MUL:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		parse_expression();
		break;
	case TOKEN_DIV:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		parse_expression();
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		parse_expression();
		break;
	default:
		error_recovery(EXPRESSION_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}