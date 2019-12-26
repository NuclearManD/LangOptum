
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"


t_token_list*	new_token(char* text, int text_len){
	char* copy;
	t_token_list* nova;

	if (text_len == 0)
		return NULL;
	copy = malloc(text_len + 1);
	strncpy(copy, text, text_len);
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
		free_token_list(li->next);
	if (li->token)
		free(li->token);
	free(li);
}

void			add_token(t_token_list** li, char* text, int text_len){
	t_token_list* tli;

	if (text_len == 0)
		return;
	if (*li == NULL)
		*li = new_token(text, text_len);
	else{
		tli = *li;
		if (tli)
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

bool	is_operator(char c){
	return	(c == '&') || (c == '|') || (c == '+') || (c == '-') || (c == '*') ||
			(c == '(') || (c == ')') || (c == ',') || (c == '[') || (c == ']') ||
			(c == '=') || (c == '!');
}

void	syntax_error(char* message){
		printf("Syntax Error: %s\n", message);
}

int		scan_backslash_escape(int fd, char* buffer, int length){
	char c;

	if (read(fd, &c, 1) == 1){
		switch (c){
			case 'n':
				c = '\n';
				break;
			case 't':
				c = '\t';
				break;
			case 'r':
				c = '\r';
				break;
			default:
				c = c;
				buffer[length++] = '\\';
		};
		buffer[length++] = c;
	}else{
		syntax_error("EOF while scanning backslash escape");
		length = -1;
	}
	return length;
}

t_token_list*	preprocessor_extract_command(int fd){
	char	last_char = 0;
	char	c;
	char	buffer[256];
	char*	tmp;
	int		length = 0;
	bool	in_c_comment = false;
	bool	in_cpp_comment = false;
	bool	in_dquote = false;

	t_token_list* tokens = NULL;

	while (read(fd, &c, 1) == 1){
		if (in_dquote){
			if (c == '"'){
				in_dquote = false;
				add_token(&tokens, buffer, length);
				length = 0;
			}else if (c == '\n'){
				syntax_error("Double quote does not go past end of line");
				length = -1;
				break;
			}else if (c == '\\'){
				if ((length = scan_backslash_escape(fd, buffer, length)) == -1)
					break;
			}else
				buffer[length++] = c;
		}else{
			if (last_char == '/' && c != '/'){
				add_token(&tokens, buffer, length);
				buffer[0] = '/';
				add_token(&tokens, buffer, 1);
			}
			if (is_space(c)){
				add_token(&tokens, buffer, length);
				length = 0;
				last_char = c;
				continue;
			}else if (c == '"'){
				add_token(&tokens, buffer, length);
				buffer[0] = '"';
				add_token(&tokens, buffer, 1);
				length = 0;
				in_dquote = true;
			}else if (c == '/'){
				add_token(&tokens, buffer, length);
				length = 0;
				if (last_char == '/'){
					while (read(fd, &c, 1) == 1)
						if (c == '\n')
							break;
					last_char = '\n';
				}
			}else if (is_operator(c)){
				add_token(&tokens, buffer, length);
				buffer[0] = c;
				add_token(&tokens, buffer, 1);
				length = 0;
			}else if (c == '\''){
				add_token(&tokens, buffer, length);
				buffer[0] = '\'';
				length = 1;
				if (read(fd, buffer + 1, 1) != 1){
					syntax_error("EOF while scanning single quote");
					break;
				}else if(buffer[1] == '\\'){
					if ((length = scan_backslash_escape(fd, buffer, length)) == -1)
						break;
				}else
					length++;
				if (read(fd, buffer + length, 1) != 1){
					syntax_error("EOF while scanning single quote");
					break;
				}else if(buffer[length] != '\''){
					syntax_error("Can only have on character inside single quotes");
					length = 0;
					break;
				}
				add_token(&tokens, buffer, length + 1);
				length = 0;
			}else if ((c == ';') || (c == '{') || (c == '}')){
				add_token(&tokens, buffer, length);
				buffer[0] = c;
				add_token(&tokens, buffer, 1);
				return tokens;
			}else
				buffer[length++] = c;
		}
		last_char = c;
	}
	if (in_dquote){
		syntax_error("EOF while scanning double quote");
	}else if (length == 0)
		return tokens;
	syntax_error("Bad line termination");
	free_token_list(tokens);
	return 0;
}

/*
void main(int ac, char** av){
	t_token_list* li;
	while (1){
		li = preprocessor_extract_command(0);
		printf("\n----- TOKENS -----\n");
		while (li != 0){
			printf("%s\n", li->token);
			li = li->next;
		}
		free_token_list(li);
	}
}
*/
