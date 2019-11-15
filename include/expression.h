#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stddef.h>

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

typedef struct s_expression{
	int operator;
	t_expression* left;
	t_expression* right;
	int64_t extra_i;
	char*	extra_ref;
} t_expression;

#endif
