/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:47:38 by chduong           #+#    #+#             */
/*   Updated: 2022/03/25 10:33:59 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}
