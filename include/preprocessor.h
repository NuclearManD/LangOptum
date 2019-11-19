
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

typedef struct s_token_list{
	char*					token;
	struct s_token_list*	next;
} t_token_list;

void			free_token_list(t_token_list* li);
t_token_list*	preprocessor_extract_command(int fd);

#endif
