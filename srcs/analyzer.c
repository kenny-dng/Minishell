/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/22 11:01:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Displays an optional syntax error message "str", and delete token_list.
*/
static void	synerror(char *str, t_token **token_list)
{
	ft_putstr_fd("Minishell : Syntax Error", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (*token_list != NULL)
	{
		free_toklist(*token_list);
		*token_list = NULL;
	}
}

t_token	*analyzer(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	checker_quotes(token_list, env_data);
	expand_remaining_envar(token_list, env_data);
	suppress_spaces(token_list);
	if (checker_words(token_list) == false)
	{
		synerror(" : Near token word.", &token_list);
		return (token_list);
	}
	if (checker_redir(token_list) == false || token_list == NULL
		|| (token_list->next == NULL && token_list->type != WORD))
	{
		synerror(" : Near redirection token.", &token_list);
		return (token_list);
	}
	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == NONE || tmp->type == VAR || tmp->type == DQUOTE
			|| tmp->type == SQUOTE)
		{
			synerror(" : Analyzer failure.", &token_list);
			break ;
		}
		tmp = tmp->next;
	}
	return (token_list);
}
