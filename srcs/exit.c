/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/03/14 17:38:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_digit(char *arg)
{
	if (*arg == '-')
		return (1);
	if (*arg == '+')
		++arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static void	free_exit(char **arg, t_data *data, int opt)
{
	if (arg)
		free_tab(arg);
	if (data->line)
		free(data->line);
	if (data->path)
		free_tab(data->path);
	if (data->export)
		free_tab(data->export);
	if (data->env)
		ft_lstclear(&data->env, free);
	clear_history();
	exit(opt);
}

void	exit_ms(char **arg, t_data *data)
{
	int	nb_arg;

	nb_arg = count_str(arg);
	if (nb_arg == 1)
		free_exit(arg, data, EXIT_SUCCESS);
	else if (nb_arg == 2)
	{
		if (only_digit(arg[1]))
			free_exit(arg, data, ft_atoi(arg[1]));
		else
		{
			printf("Minishell: exit: %s: numeric argument required\n", arg[1]);
			free_exit(arg, data, EXIT_SUCCESS);
		}
	}
	else
		printf("Minishell: exit: too many argument\n");
}
