#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stddef.h>
#include <stdint.h>

#define OPERATOR_INC	0
#define OPERATOR_DEC	1
#define OPERATOR_ADD	2
#define OPERATOR_MUL	3
#define OPERATOR_SUB	4
#define OPERATOR_DIV	5
#define OPERATOR_ASSIGN	6
#define OPERATOR_LITRL	7
#define OPERATOR_LONG	8
#define OPERATOR_CALL	9
#define OPERATOR_DECLRE	10
#define OPERATOR_REF	11
#define OPERATOR_MOD	12
#define TOKEN_LPAREN	13
#define TOKEN_RPAREN	14
#define TOKEN_COMMA		15
#define TOKEN_SEMICOLON	16
#define TOKEN_TYPE		17

typedef struct s_expression{
	int operator;
	struct s_expression* left;
	struct s_expression* right;
	int64_t extra_i;
	char*	extra_ref;
} t_expression;

t_expression*	new_string_literal(char* text);
t_expression*	new_variable_ref(char* text);
t_expression*	new_integer_literal(uint64_t val);
t_expression*	new_dualarg_expression(t_expression* left, t_expression* right, int operator);
t_expression*	new_onearg_expression(t_expression* left, int operator);
void			free_expression(t_expression* ex);

#endif
