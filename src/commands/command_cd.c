/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 13:30:44 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/13 14:40:05 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str(t_list	*cmd, char *str)
{
	if (cmd == NULL || !ft_strcmp(cmd->var, "~\0"))
	{
		str = ft_get_env("HOME", g_data->envp);
		if (str == NULL)
		{
			g_data->exit_status = 1;
			stderr_print("minishell: cd: HOME not set", 0, 0);
			return (NULL);
		}
	}
	else if (!ft_strcmp(cmd->var, "-\0"))
	{
		if (ft_get_env("OLDPWD", g_data->envp) == NULL)
		{
			g_data->exit_status = 1;
			stderr_print("minishell: cd: OLDPWD not set", 0, 0);
			return (NULL);
		}
		str = ft_get_env("OLDPWD", g_data->envp);
	}
	else
		str = cmd->var;
	return (str);
}

void	execute_cd(t_list *cmd)
{
	char	cwd[PATH_MAX];
	char	*str;

	str = NULL;
	str = get_str(cmd, str);
	if (!str)
		return ;
	replace_env(ft_strdup("OLDPWD"), ft_strdup(getcwd(cwd, sizeof(cwd))));
	if (chdir(str))
	{
		stderr_print("minishell: cd: ", str, ": No such file or directory");
		g_data->exit_status = 1;
	}
	replace_env(ft_strdup("PWD"), ft_strdup(getcwd(cwd, sizeof(cwd))));
}
