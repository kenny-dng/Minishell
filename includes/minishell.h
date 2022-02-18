/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/02/18 18:41:12 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

//	TYPEDEF
typedef struct s_data
{
	char	*line;
	char	**path;
	char	**export;
	int		newenv;
	int		newpath;
	t_list	*env;
}			t_data;

//	UTILS
int		count_str(char **str);
void	free_tab(char **tab);
char	*grep_path(t_list *env);
bool	is_in_charset(char c, char *charset);

//	PARSING
void	parse_line(char **envp, t_data *data);

//	BUILTINS
void	exit_ms(char **arg, t_data *data);
void	fork_exec(char **arg, char **envp, t_data *data);
void	print_env(t_list *env);
void	print_export(t_data *data);

#endif