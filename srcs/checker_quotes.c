/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:53:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/09 17:53:55 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Finds the next "elem_type" element in toklist,
and returns its index in the list;
If there are none, returns 0;
*/
size_t	is_closed(t_token *elem, t_token_type elem_type)
{
	t_token	*tmp;

	if (elem == NULL)
		return (0);
	tmp = elem->next;
	while (tmp != NULL)
	{
		if (tmp->type == elem_type)
			return (tmp->index);
		tmp = tmp->next;
	}
	return (0);
}

/*
Trims every boundary space from each WORD token in the list,
starting from "elem".
*/
static void	trim_wordspaces(t_token *elem)
{
	t_token	*tmp;
	char	*to_del;

	tmp = elem;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			to_del = tmp->data;
			tmp->data = ft_strtrim(tmp->data, " \t\n\r\v\f");
			free(to_del);
		}
		tmp = tmp->next;
	}
}

static void	squote_manager(t_token *tmp, size_t *ends)
{
	*ends = is_closed(tmp, SQUOTE);
	if (*ends != 0)
		reduce_all(tmp, *ends);
}

static void	dquote_manager(t_token *tmp, size_t *endd, t_data *env_data)
{
	*endd = is_closed(tmp, DQUOTE);
	if (*endd != 0)
		reduce(tmp, *endd, env_data);
}

void	checker_quotes(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;
	size_t	ends;
	size_t	endd;

	tmp = token_list;
	ends = 42;
	endd = 42;
	while (tmp != NULL)
	{
		if (tmp->type == SQUOTE)
			squote_manager(tmp, &ends);
		else if (tmp->type == DQUOTE)
			dquote_manager(tmp, &ends, env_data);
		if (ends == 0 && endd == 0)
		{
			trim_wordspaces(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}