/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:52:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/05 18:01:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_handlers(char *filepath, t_token **tmp, t_data *data)
{
	free(filepath);
	filepath = NULL;
	if ((*tmp)->previous)
	{
		*tmp = (*tmp)->previous;
		lst_pop((*tmp)->next, &data->token_list);
		merge_cmd(*tmp, data);
	}
}

void	less_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, R_OK) == 0)
	{
		fd = open(filepath, O_RDONLY);
		if ((*tmp)->previous == NULL && (*tmp)->next)
		{
			if ((*tmp)->next->in != -1)
				close((*tmp)->next->in);
			(*tmp)->next->in = fd;
		}
		else if ((*tmp)->previous)
		{
			if ((*tmp)->previous->in != -1)
				close((*tmp)->previous->in);
			(*tmp)->previous->in = fd;
		}
		else
			close (fd);
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

void	great_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if ((*tmp)->previous->out != -1)
			close((*tmp)->previous->out);
		(*tmp)->previous->out = fd;
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

void	dgreat_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*tmp)->previous->out != -1)
			close((*tmp)->previous->out);
		(*tmp)->previous->out = fd;
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

bool	is_redir_token(t_token *elem)
{
	if (elem == NULL)
		return (false);
	else if (elem->type == LESS || elem->type == DLESS
		|| elem->type == GREAT || elem->type == DGREAT)
		return (true);
	return (false);
}