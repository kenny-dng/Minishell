/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:21:12 by chduong           #+#    #+#             */
/*   Updated: 2022/03/15 20:17:09 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *envp, char *var, char *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	if (envp)
		a->line = ft_strdup(envp);
	if (var)
		a->var = ft_strdup(var);
	if (content)
		a->content = ft_strdup(content);
	a->prev = NULL;
	a->next = NULL;
	return (a);
}
