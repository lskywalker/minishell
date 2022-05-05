/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:41:53 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 14:48:55 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoinjoin(char *path, char *c, char *cmd)
{
	path = ft_strjoin(0, path, ft_strdup(c));
	path = ft_strjoin(0, path, cmd);
	return (path);
}

char	**list_to_array(t_list *list, int type)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (listsize(list) + 1));
	i = 0;
	while (list)
	{
		if (type == 1)
			array[i] = list->var;
		else if (list->value)
			array[i] = strjoinjoin(ft_strdup(list->var), "=", \
			ft_strdup(list->value));
		else
			array[i] = NULL;
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	exec_basiccommands(char **path, t_list *cmd, int i)
{
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		status;

	status = 0;
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
		if (execve(strjoinjoin((path[i]), "/", \
		ft_strdup(cmd->var)), argv, envp) == -1)
			exit(errno);
		exit(g_data->exit_status);
	}
	ft_free(envp);
	free(argv);
	ft_free(path);
}

int	last_occurance(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}

int	check_dir(char *str)
{
	struct stat	stats;

	if (stat(str, &stats))
	{
		stderr_print("minishell: ", str, ": No such file or directory");
		g_data->exit_status = 127;
		return (1);
	}
	if (S_ISDIR(stats.st_mode))
	{
		stderr_print("minishell: ", str, ": is a directory");
		g_data->exit_status = 127;
		return (1);
	}
	return (0);
}
