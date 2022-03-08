/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 18:35:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Data structures */
typedef enum e_token_type
{
	NONE,
	WORD,
	VAR,
	DQUOTE,
	SQUOTE,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
}	t_token_type;
/*
Note that only WORD and VAR token have malloc'd data attributes.
*/
# define TERM_CHARS "<>|\"\'$"
# define TERM_N_SPACE " <>|\"\'$"

typedef enum e_abstract_type
{
	COMMAND,
	ARGUMENT,
	REDIRECT,
	EXPANSION
}	t_abstract_type;

typedef struct s_token
{
	size_t			index;
	char			*data;
	t_token_type	type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	const char	*str;
	size_t		index;
	bool		dquoted;
	bool		squoted;
}	t_input;

/* Prototypes */
t_token	*lexer(char *input);
t_token	*scanner(const char *str);
t_token	*analyzer(t_token *token_list, t_data *env_data);

char	*my_strcat(char *dest, char *str);
char	*find_envar(char *envar, t_data *env_data);

size_t	find_char_set(const char *str, char *charset);
size_t	is_closed(t_token *elem, t_token_type elem_type);

int		free_toklist(t_token *list);

bool	create_token(t_token_type type, char *data, t_token **list);
bool	categorizer(t_input *input, t_token **token_list);
bool	checker_words(t_token *token_list);
bool	checker_reidr(t_token *token_list);

void	display_toklist(t_token *token_list);
void	checker_quotes(t_token *token_list, t_data *env_data);
void	expand(t_token *elem, t_data *env_data);
void	matriochka(t_token *elem, t_data *env_data);
void	lst_pop(t_token *elem);
void	reduce_all(t_token *elem, size_t end);
void	reduce(t_token *elem, size_t end, t_data *env_data);
void	reduce_words(t_token *elem, size_t end);

int		categ_1(t_input *input, t_token **token_list);
int		categ_2(t_input *input, t_token **token_list);
int		categ_3(t_input *input, t_token **token_list);
int		categ_4(t_input *input, t_token **token_list);
int		categ_5(t_input *input, t_token **token_list);

#endif
