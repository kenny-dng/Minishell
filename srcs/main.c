/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/02/18 19:24:54 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	data_init(t_data *data, char **envp)
{
	int		i;

	data->newenv = 0;
	data->newpath = 0;
	data->export = NULL;
	data->line = NULL;
	data->env = NULL;
	i = 0;
	while (envp[i])
		ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(envp[i++])));
	data->path = ft_split(grep_path(data->env), ':');
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 1)
	{
		data_init(&data, envp);
		while (1)
		{
			data.line = readline("\e[1;35mMiniShell >: \e[0m");
			if (data.line && *data.line)
        		add_history(data.line);
			parse_line(envp, &data);
			free(data.line);
			data.line = NULL;
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
