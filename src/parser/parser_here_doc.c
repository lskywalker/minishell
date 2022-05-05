/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_here_doc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 16:48:12 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:48:01 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_tmp(void)
{
	int	fd;

	fd = open("/tmp/minishell_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error_exit("redirect failed.");
	return (fd);
}

char	*eof_loop(int tmp_fd, char *eof, char *input)
{
	if (eof[0] != '\'' || eof[0] != '\"')
	{
		while (has_dollar(input) == 1)
			input = insert_env_var(input, 0, 0);
	}
	write(tmp_fd, input, ft_strlen(input));
	write(tmp_fd, "\n", 1);
	return (input);
}

void	get_input(int tmp_fd, char *eof)
{
	char	*input;

	signal(SIGINT, here_doc_signal);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			close(tmp_fd);
			exit(0);
		}
		if (ft_strcmp(input, eof))
			input = eof_loop(tmp_fd, eof, input);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

void	make_input(void)
{
	int	tmp_fd;

	tmp_fd = open("/tmp/minishell_tmp", O_RDONLY);
	unlink("/tmp/minishell_tmp");
	dup2(tmp_fd, 0);
	close(tmp_fd);
}

void	here_doc(char *eof, int *old_fd)
{
	int	tmp_fd;
	int	old_fd_out;
	int	pid;
	int	status;

	tmp_fd = make_tmp();
	old_fd_out = dup(1);
	dup2(old_fd[1], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(open("/tmp/minishell_tmp", O_WRONLY | O_TRUNC, 0600));
		g_data->exit_status = 130;
	}
	make_input();
	dup2(old_fd_out, STDOUT_FILENO);
	close(old_fd_out);
}
