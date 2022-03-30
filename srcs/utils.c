/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:54 by chduong           #+#    #+#             */
/*   Updated: 2022/03/30 19:50:11 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

t_list	*grep(char *varname, t_data *data)
{
	t_list *env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->var, varname) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*path_join(char *path, char *cmd)
{
	char	*p;
	int		len1;
	int		len2;

	if (!path || !cmd)
		return (NULL);
	len1 = ft_strlen(path);
	len2 = ft_strlen(cmd);
	p = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!p)
		return (NULL);
	ft_strlcpy(p, path, len1 + 1);
	ft_strlcat(p, "/", len1 + 2);
	ft_strlcat(p, cmd, len1 + len2 + 2);
	return (p);
}

char	*var_join(char *var, char *value)
{
	char	*p;
	int		len1;
	int		len2;

	if (!var || !value)
		return (NULL);
	len1 = ft_strlen(var);
	len2 = ft_strlen(value);
	p = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!p)
		return (NULL);
	ft_strlcpy(p, var, len1 + 1);
	ft_strlcat(p, "=", len1 + 2);
	ft_strlcat(p, value, len1 + len2 + 2);
	return (p);
}
