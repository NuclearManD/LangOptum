
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
#include "expression.h"

bool is_valid_reference(char* s){
	if (*s == 0 || !((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s == '_')))
		return false;
	while(*(++s))
		if (!((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
			|| (*s >= '0' && *s <= '9') || (*s == '_')))
			return false;
	return true;
}

bool is_type(char* s){
	if (*s == 'u')
		s++;
	if (!(strcmp(s, "int8") && strcmp(s, "int16") && strcmp(s, "int32") && strcmp(s, "int64")))
		return true;
	if (!strcmp(s, "bool"))
		return true;
	return false;
}

int get_operator_of(t_token_list* tokens){
	char c;

	if (tokens == NULL)
		return -2;
	if (strlen(tokens->token) == 1){
		c = tokens->token[0];
		switch(c){
			case '*':
				return OPERATOR_MUL;
			case '/':
				return OPERATOR_DIV;
			case '%':
				return OPERATOR_MOD;
			case '+':
				return OPERATOR_ADD;
			case '-':
				return OPERATOR_SUB;
			case ',':
				return TOKEN_COMMA;
			case '(':
				return TOKEN_LPAREN;
			case ')':
				return TOKEN_RPAREN;
			case '=':
				return OPERATOR_ASSIGN;
			case ';':
				return TOKEN_SEMICOLON;
		}
	}
	if (is_type(tokens->token))
		return TOKEN_TYPE;
	if (is_valid_reference(tokens->token))
		return OPERATOR_REF;
	
	return -1;
}
/*
// This function is intended to be recursive.
t_expression* parser_process_tokens(t_token_list* tokens){
	
}

t_expression* parser_gen_expr(int fd){
	t_token_list* tokens = preprocessor_extract_command(fd);

	if (tokens == NULL)
		return NULL;
	return parser_process_tokens(tokens);
}
*/


void main(int ac, char** av){
	t_token_list* li;
	while (1){
		li = preprocessor_extract_command(0);
		printf("\n----- TOKEN TYPES -----\n");
		while (li != 0){
			printf("%s : %i\n", li->token, get_operator_of(li));
			li = li->next;
		}
		free_token_list(li);
	}
}
