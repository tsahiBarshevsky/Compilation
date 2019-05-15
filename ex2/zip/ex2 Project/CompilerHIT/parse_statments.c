#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_statments() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		parse_statment();
		match(TOKEN_SEMICOLON);
		parse_statments_clean();
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		parse_statment();
		match(TOKEN_SEMICOLON);
		parse_statments_clean();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		parse_statment();
		match(TOKEN_SEMICOLON);
		parse_statments_clean();
		break;
	default:
		error_recovery(STATEMENTS, expected, NUM_OF_EXPECTED);
		break;
	}
}