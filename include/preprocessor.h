
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

typedef struct s_token_list{
	char*					token;
	struct s_token_list*	next;
} t_token_list;

t_token_list*	new_token(char* text, int text_len);
void			free_token_list(t_token_list* li);


#endif
