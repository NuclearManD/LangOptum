
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "preprocessor.h"


t_token_list*	new_token(char* text, int text_len){
	char* copy;
	t_token_list* nova;

	copy = malloc(text_len + 1);
	strncpy(copy, text_len);
	copy[text_len] = 0;

	nova = malloc(sizeof(t_token_list));
	nova->token = copy;
	nova->next = NULL;

	return nova;
}

void			free_token_list(t_token_list* li){
	if (li == NULL)
		return;
	if (li->next)
		free_token_list(li);
	if (li->token)
		free(li->token);
	free(li);
}

void			add_token(t_token_list** li, char* text, int text_len){
	t_token_list* tli;

	if (*li == NULL)
		*li = new_token(text, text_len);
	else{
		tli = *li;
		while (tli->next)
			tli = tli->next;
		tli->next = new_token(text, text_len);
	}
}

bool	is_space(char c){
	return (c == ' ') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\f');
}

bool	is_invalid_char(char c){
	return (c < 9) || (c > 13 && c < 32) || (c > 126);
}

t_token_list*	preprocessor_extract_command(int fd){
	char	last_char = 0;
	char	c;
	char*	buffer;
	char*	tmp;
	int		length = 0;
	bool	in_c_comment = false;
	bool	in_cpp_comment = false;
	bool	in_dquote = false;

	t_token_list* tokens;

	while (read(fd, &c, 1) == 1){
		if (is_space(c)){
			last_char = c;
			continue;
		}
		if (c == ';'){
			add_token(buffer, length);
			return tokens;
		}
	}
	if (length == 0)
		return tokens;
	printf("Syntax Error: Bad line termination\n");
	return 0;
}