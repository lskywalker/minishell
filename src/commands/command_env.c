/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 17:22:17 by lsmit         #+#    #+#                 */
/*   Updated: 2022/02/10 13:24:23 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char *var, char *value, int fd)
{
	if (!var || !value)
		return ;
	write(fd, var, ft_strlen(var));
	write(fd, "=", 1);
	write(fd, value, ft_strlen(value));
	write(fd, "\n", 1);
}

void	execute_env(t_list *envp, int fd)
{
	while (envp)
	{
		print_env(envp->var, envp->value, fd);
		envp = envp->next;
	}
}
