/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 13:54:11 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/14 13:20:48 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	execute_exit(t_list *cmd)
{
	if (cmd->next == NULL)
	{
		printf("exit\n");
		exit(g_data->exit_status);
	}
	else
	{
		if (cmd->next->next != NULL)
		{
			stderr_print("minishell: exit: too many arguments", 0, 0);
			g_data->exit_status = 1;
			return ;
		}
		if (ft_isdigit(cmd->next->var))
			exit(atoi(cmd->next->var));
		else
		{
			write(1, "exit\n", 5);
			stderr_print("minishell: exit: ", cmd->next->var, ": numeric \
			argument required");
			exit(255);
		}
	}
}
