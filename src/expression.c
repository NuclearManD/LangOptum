
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "expression.h"

t_expression*	new_variable_ref(char* text){
	char* copy;
	t_expression* nova;

	copy = malloc(strlen(text) + 1);
	strcpy(copy, text);

	nova = malloc(sizeof(t_expression));
	nova->operator = OPERATOR_VAR;
	nova->extra_ref = copy;
	nova->left = NULL;
	nova->right = NULL;

	return nova;
}

t_expression*	new_string_literal(char* text){
	char* copy;
	t_expression* nova;

	copy = malloc(strlen(text) + 1);
	strcpy(copy, text);

	nova = malloc(sizeof(t_expression));
	nova->operator = OPERATOR_LITRL;
	nova->extra_ref = copy;
	nova->left = NULL;
	nova->right = NULL;

	return nova;
}

t_expression*	new_integer_literal(uint64_t val){
	t_expression* nova;

	nova = malloc(sizeof(t_expression));
	nova->operator = OPERATOR_LONG;
	nova->extra_ref = NULL;
	nova->extra_i = val;
	nova->left = NULL;
	nova->right = NULL;

	return nova;
}

t_expression*	new_dualarg_expression(t_expression* left, t_expression* right, int operator){
	t_expression* nova;

	nova = malloc(sizeof(t_expression));
	nova->operator = operator;
	nova->extra_ref = NULL;
	nova->left = left;
	nova->right = right;

	return nova;
}

t_expression*	new_onearg_expression(t_expression* left, int operator){
	t_expression* nova;

	nova = malloc(sizeof(t_expression));
	nova->operator = operator;
	nova->extra_ref = NULL;
	nova->left = left;
	nova->right = NULL;

	return nova;
}

void			free_expression(t_expression* ex){
	if (ex == NULL)
		return;
	if (ex->left)
		free_expression(ex->left);
	if (ex->right)
		free_expression(ex->right);
	if (li->extra_ref)
		free(li->extra_ref);
	free(li);
}
