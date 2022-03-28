/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/28 14:46:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
static void	redirection_handler(t_token *token_list, char **envp, t_data *data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (pipe(tmp->pipefd) == -1)
			{
				perror("pipe failed.");
				exit_ms(NULL, data);
			}
			tmp->previous->out = tmp->pipefd[1];
			tmp->next->in = tmp->pipefd[0];
		}
		tmp = tmp->next;
	}
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
			fork_exec(tmp, envp, data);
		tmp = tmp->next;
	}
}

/*
Launch the execution of the whole token_list, and frees it.
*/
bool	executor(char **envp, t_data *data)
{
	if (data->token_list == NULL)
		return (false);
	if (data->token_list->next == NULL)
		fork_exec(data->token_list, envp, data);
	else
		redirection_handler(data->token_list, envp, data);
	if (data->token_list)
		free_toklist(&data->token_list);
	return (true);
}
