/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 17:09:41 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/14 12:07:34 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

void	exec_executable(char *path, char *executable, t_list *cmd)
{
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		status;

	status = 0;
	free(cmd->var);
	cmd->var = ft_strdup(executable);
	argv = list_to_array(cmd, 1);
	envp = list_to_array(g_data->envp, 2);
	pid = fork();
	if (pid)
	{
		waitpid(pid, &status, WUNTRACED);
		g_data->exit_status = check_status(status);
	}
	else
	{
		if (execve(ft_strjoin(0, path, executable), argv, envp) == -1)
			exit(errno);
		exit(g_data->exit_status);
	}
	ft_free(envp);
	free(argv);
}

void	executable(t_list *cmd)
{
	char	*path;
	char	*executable;
	int		i;
	int		j;

	i = 0;
	j = last_occurance(cmd->var, '/');
	path = (char *)ft_calloc(j, sizeof(char *));
	executable = (char *)ft_calloc(ft_strlen(cmd->var) - j + 1, sizeof(char *));
	while (i <= j)
	{
		path[i] = cmd->var[i];
		i++;
	}
	j = 0;
	while (cmd->var[i])
	{
		executable[j] = cmd->var[i];
		i++;
		j++;
	}
	if (!check_dir(cmd->var))
		exec_executable(path, executable, cmd);
	free(path);
	free(executable);
}

int	basic_cmds_loop(t_list *cmd, char **path, int i)
{
	struct dirent	*dir;
	DIR				*d;

	while (path[i] != NULL)
	{
		d = opendir(path[i]);
		if (d)
		{
			dir = readdir(d);
			while (dir != NULL)
			{
				if (!ft_strcmp(cmd->var, dir->d_name))
				{
					exec_basiccommands(path, cmd, i);
					closedir(d);
					return (0);
				}
				dir = readdir(d);
			}
			closedir(d);
		}
		i++;
	}
	return (1);
}

int	basic_cmds(t_list *cmd, int i)
{
	char			**path;

	g_data->exit_status = 0;
	if (ft_strchr(cmd->var, '/'))
	{
		executable(cmd);
		return (0);
	}
	else
	{
		if (ft_get_env("PATH", g_data->envp) == NULL)
			return (1);
		path = ft_split(ft_get_env("PATH", g_data->envp), ':');
		if (basic_cmds_loop(cmd, path, i) == 0)
			return (0);
		ft_free(path);
	}
	return (1);
}

void	exec(t_list *cmd)
{
	signal(SIGINT, interupt);
	signal(SIGQUIT, quit);
	if (!(ft_strcmp_special(cmd->var, "echo")))
		execute_echo(cmd);
	else if (!(ft_strcmp_special(cmd->var, "cd")))
		execute_cd(cmd->next);
	else if (!(ft_strcmp_special(cmd->var, "pwd")))
		execute_pwd();
	else if (!(ft_strcmp(cmd->var, "export")))
		execute_export(cmd);
	else if (!(ft_strcmp(cmd->var, "unset")))
		execute_unset(cmd->next, g_data->envp);
	else if (!(ft_strcmp_special(cmd->var, "env")))
		execute_env(g_data->envp, STDOUT_FILENO);
	else if (!(ft_strcmp(cmd->var, "exit")))
		execute_exit(cmd);
	else if (!ft_strcmp(cmd->var, ""))
		return ;
	else if (!basic_cmds(cmd, 0))
		return ;
	else
	{
		stderr_print("minishell: ", cmd->var, ": command not found");
		g_data->exit_status = 127;
	}
}
