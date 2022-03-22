/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:53:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/22 12:09:24 by smagdela         ###   ########.fr       */
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
/*
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
*/

static bool	squote_manager(t_token *tmp, size_t *ends)
{
	t_token	*ends_elem;

	*ends = is_closed(tmp, SQUOTE);
	if (*ends != 0)
	{
		
		ends_elem = tmp;
		while (ends_elem != NULL && ends_elem->index < *ends)
			ends_elem = ends_elem->next;
		reduce_all(tmp, ends_elem);
		return (true);
	}
	return (false);
}

static bool	dquote_manager(t_token *tmp, size_t *endd, t_data *env_data)
{
	t_token	*endd_elem;

	*endd = is_closed(tmp, DQUOTE);
	if (*endd != 0)
	{
		endd_elem = tmp;
		while (endd_elem != NULL && endd_elem->index < *endd)
			endd_elem = endd_elem->next;
		reduce(tmp, endd_elem, env_data);
		return (true);
	}
	return (false);
}

/*
Deletes every WORD token which are only spaces.
*/
void	suppress_spaces(t_token *token_list)
{
	t_token	*tmp;
	t_token	*to_pop;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD
			&& !ft_strncmp(tmp->data, " ", ft_strlen(tmp->data)))
		{
			to_pop = tmp;
			tmp = tmp->next;
			lst_pop(to_pop);
		}
		else
			tmp = tmp->next;
	}
}

/*
Check if quotes are closed, and reduce everything in between accordingly,
or unclosed, and convert to non-special token WORD.
In the ends, calls "suppress_spaces" function in order to delete
any spaces which were not inside quotes, therefore unecessary.
*/
bool	checker_quotes(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;
	size_t	ends;
	size_t	endd;
	bool	ret;

	tmp = token_list;
	ends = 42;
	endd = 42;
	ret = true;
	while (tmp != NULL && ret == true)
	{
		if (tmp->type == SQUOTE)
			ret = squote_manager(tmp, &ends);
		else if (tmp->type == DQUOTE)
			ret = dquote_manager(tmp, &endd, env_data);
		tmp = tmp->next;
	}
	return (ret);
}
