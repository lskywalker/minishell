/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 14:57:21 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 20:17:54 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_array(t_list *list)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (listsize(list) + 1));
	i = 0;
	while (list)
	{
		if (list->value != NULL)
		{
			array[i] = ft_strjoin(0, ft_strdup(list->var), ft_strdup("=\""));
			array[i] = ft_strjoin(0, array[i], ft_strdup(list->value));
		}
		else
			array[i] = ft_strdup(list->var);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	envlist_alphabetic(int i)
{
	int		j;
	char	**list;

	list = env_to_array(g_data->envp);
	while (list[i])
	{
		j = 0;
		while (list[j])
		{
			if (ft_strcmp(list[i], list[j]) < 0)
				ft_swap(&list[i], &list[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (list[i])
	{
		write(1, "declare -x ", 11);
		write(1, list[i], ft_strlen(list[i]));
		write(1, "\"\n", 2);
		i++;
	}
	ft_free(list);
}

int	precheck_input(t_list *cmd, int ret)
{
	char	*var;

	if (cmd == NULL)
	{
		envlist_alphabetic(0);
		return (1);
	}
	while (cmd)
	{
		var = get_var(cmd->var);
		if (!ft_strcmp(var, "=") || !validinput_check(var))
		{
			stderr_print("minishell: export: '", cmd->var, \
			"': not a valid identifier");
			g_data->exit_status = 1;
			ret = 1;
		}
		free(var);
		cmd = cmd->next;
	}
	return (ret);
}

void	execute_export(t_list *cmd)
{
	char	*var;
	char	*value;

	if (precheck_input(cmd->next, 0))
		return ;
	g_data->exit_status = 0;
	var = NULL;
	value = NULL;
	cmd = cmd->next;
	while (cmd)
	{
		var = get_var(cmd->var);
		value = get_value(cmd->var);
		replace_env(var, value);
		cmd = cmd->next;
	}
}
