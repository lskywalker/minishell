/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 13:29:34 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/11 21:18:17 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	n_flagcheck(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	if (!ft_strcmp(str, "-n"))
		return (true);
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		if (str[i] == 'n' && str[i + 1])
		{
			i++;
			while (str[i])
			{
				if (str[i] != 'n')
					return (false);
				i++;
			}
		}
	}
	if (i > 1)
		return (true);
	return (false);
}

void	execute_echo(t_list *cmd)
{
	bool	n_flag;

	g_data->exit_status = 0;
	if (cmd->next == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	cmd = cmd->next;
	n_flag = n_flagcheck(cmd->var);
	while (n_flagcheck(cmd->var) == true)
	{
		cmd = cmd->next;
		if (!cmd)
			break ;
	}
	while (cmd)
	{
		write(1, cmd->var, ft_strlen(cmd->var));
		if (cmd->next)
			write(1, " ", 1);
		cmd = cmd->next;
	}
	if (n_flag == false)
		write(1, "\n", 1);
}
