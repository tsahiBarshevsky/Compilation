#include "Parser.h"

void parser() { /*main parser methond*/
	parse_program(); /*parser start rule of grammar*/
	match(TOKEN_EOF); /*check that parser is actually is finished on EOF*/
}

void parse_program() { /*one case rule*/
	print_parser_rule("PROGRAM -> program VAR_DEFINITIONS ; STATMENTS end FUNC_DEFINITIONS");
	match(TOKEN_PROGRAM);
	parse_var_definitions();
	match(TOKEN_SEMICOLON);
	parse_statments();
	match(TOKEN_END);
	parse_func_definitions();
}

void parse_var_definitions() {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_var_definition();
		parse_var_definitions_clean();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_var_definition();
		parse_var_definitions_clean();
		break;
	default:
		error_recovery(VAR_DEFINITIONS, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_var_definitions_clean() {
	next_token();
	Token *peek = next_token();
	eTOKENS expected[2] = { TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	cur_token = back_token();
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		if (peek->kind == TOKEN_REAL || peek->kind == TOKEN_INTEGER) {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
			parse_var_definitions();
		}
		else {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
			cur_token = back_token();
		}
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VAR_DEFINITIONS_CLEAN, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_var_definition() {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		cur_token = back_token();
		parse_type();
		parse_variables_list();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		cur_token = back_token();
		parse_type();
		parse_variables_list();
		break;
	default:
		error_recovery(VAR_DEFINITION, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_type() {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("TYPE -> real");
		break;
	case TOKEN_INTEGER:
		print_parser_rule("TYPE -> integer");
		break;
	default:
		error_recovery(TYPE, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_variables_list() { /*one case rule*/
	print_parser_rule("VARIABLES_LIST -> VARIABLE VARIABLES_LIST_CLEAN");
	match(TOKEN_ID);
	cur_token = back_token();
	parse_variable();
	parse_variables_list_clean();
}

void parse_variables_list_clean() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_COMMA:
		print_parser_rule("VARIABLES_LIST_CLEAN -> , VARIABLE VARIABLES_LIST_CLEAN");
		parse_variable();
		parse_variables_list_clean();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLES_LIST_CLEAN, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_variable() { /*one case rule*/
	print_parser_rule("VARIABLE -> id VARIABLE_CLEAN");
	match(TOKEN_ID);
	parse_variable_clean();
}

void parse_variable_clean() {
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_OPEN_SQUER_PAR, TOKEN_ASSIGNMENT, TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("VARIABLE_CLEAN -> [ int_number ]");
		match(TOKEN_INT_NUMBER);
		match(TOKEN_CLOSE_SQUER_PAR);
		//cur_token = next_token();
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_COMMA:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLE_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
}

void parse_func_definitions() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_func_definitions_celan() {
	cur_token = next_token();
	eTOKENS expected[4] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID, TOKEN_EOF }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_EOF:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS_CLEAN, expected, 4); /*print error and try to recover*/
		break;
	}
}

void parse_func_definition() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		parse_block();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		parse_block();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		parse_block();
		break;
	default:
		error_recovery(FUNC_DEFINITION, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_returned_type() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		parse_type();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		parse_type();
		break;
	case TOKEN_VOID:
		print_parser_rule("RETURNED_TYPE -> void");
		break;
	default:
		error_recovery(RETURNED_TYPE, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_param_definitions() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("PARAM_DEFINITIONS -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(PARAM_DEFINITIONS, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_statments() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR }; /*expected tokens for error printing purpose*/
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
		error_recovery(STATEMENTS, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_statments_clean() {
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR, TOKEN_END, TOKEN_CLOSE_CURLY_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_END:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(STATEMENTS_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
}

void parse_statment() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENT -> id ID_STATEMENT_CLEAN");
		parse_id_statment_clean();
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENT -> return RETURN_STATEMENT_CLEAN");
		parse_return_statment_clean();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENT -> BLOCK");
		cur_token = back_token();
		parse_block();
		break;
	default:
		error_recovery(STATEMENT, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_return_statment_clean() {
	cur_token = next_token();
	eTOKENS expected[4] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER, TOKEN_SEMICOLON }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		parse_expression();
		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		parse_expression();
		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		parse_expression();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(RETURN_STATEMENT_CLEAN, expected, 4); /*print error and try to recover*/
		break;
	}
}

void parse_id_statment_clean() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_OPEN_SQUER_PAR, TOKEN_OPEN_CIRCULAR_PAR, TOKEN_ASSIGNMENT }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("ID_STATEMENT_CLEAN -> VARIABLE_CLEAN = EXPRESSION");
		cur_token = back_token();
		parse_variable_clean();
		match(TOKEN_ASSIGNMENT);
		parse_expression();
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("ID_STATEMENT_CLEAN -> VARIABLE_CLEAN = EXPRESSION");
		cur_token = back_token();
		parse_variable_clean();
		match(TOKEN_ASSIGNMENT);
		parse_expression();
		break;
	case TOKEN_OPEN_CIRCULAR_PAR:
		print_parser_rule("ID_STATEMENT_CLEAN -> ( PARAMETERS_LIST )");
		parse_parameters_list();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		break;
	default:
		error_recovery(ID_STATEMENT_CLEAN, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_block() { /*one case rule*/
	print_parser_rule("BLOCK -> { VAR_DEFINITIONS ; STATMENTS }");
	match(TOKEN_OPEN_CURLY_PAR);
	parse_var_definitions();
	match(TOKEN_SEMICOLON);
	parse_statments();
	match(TOKEN_CLOSE_CURLY_PAR);
}

void parse_parameters_list() {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_ID, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("PARAMETERS_LIST -> VARIABLES_LIST");
		cur_token = back_token();
		parse_variables_list();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("PARAMETERS_LIST -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(PARAMETERS_LIST, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_expression() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("EXPRESSION -> id EXPRESSION_CLEAN");
		parse_expression_clean();
		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("EXPRESSION -> int_number");
		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("EXPRESSION -> real_number");
		break;
	default:
		error_recovery(EXPRESSION, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_expression_clean() {
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_SEMICOLON, TOKEN_OPEN_SQUER_PAR, TOKEN_MUL, TOKEN_DIV, TOKEN_ASSIGNMENT }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
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
	case TOKEN_SEMICOLON:
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		cur_token = back_token();
		parse_variable_clean();
		break;
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		cur_token = back_token();
		parse_variable_clean();
		break;
	default:
		error_recovery(EXPRESSION_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
}