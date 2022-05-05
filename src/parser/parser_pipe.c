/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_pipe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 15:40:17 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/13 15:16:49 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_pipe(int *old_pipe)
{
	int	new_pipe[2];

	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*old_pipe = dup(new_pipe[0]);
	close(new_pipe[0]);
}

t_list	*make_cmd_list(t_list **start, t_list *end)
{
	t_list	*node;
	t_list	*cmd;
	t_list	*tmp;

	if (!*start)
		return (0);
	tmp = *start;
	cmd = ft_lstnew(ft_strdup(tmp->var), NULL);
	tmp = tmp->next;
	while (tmp != end)
	{
		if (!tmp || tmp->type == REDIRECT)
			break ;
		node = ft_lstnew(ft_strdup(tmp->var), NULL);
		if (!node)
			error_exit("Malloc Failed");
		ft_lstadd_back(&cmd, node);
		tmp = tmp->next;
	}
	return (cmd);
}

void	make_fork(t_list *start, t_list *end, int *old_fd)
{
	t_list	*cmd;
	int		pid;
	int		status;

	pid = fork();
	if (pid)
		pid = waitpid(pid, &status, WUNTRACED);
	else
	{
		redirect_parser(start, end, old_fd);
		if (start->type != REDIRECT)
		{
			cmd = make_cmd_list(&start, end);
			if (cmd)
			{
				exec(cmd);
				ft_lstclear(&cmd, &del);
			}
		}
		g_data->exit_status = 0;
		exit(g_data->exit_status);
	}
}

void	pipe_parser(t_list *start, t_list *end, int *pipe)
{
	int		old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	dup2(*pipe, STDIN_FILENO);
	if (*pipe != 0)
		close(*pipe);
	if (end)
	{
		make_pipe(pipe);
		make_fork(start, end, old_fd);
	}
	else
	{
		redirect_parser(start, end, old_fd);
		redirect_loop(start, end);
	}
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
}

void	pipe_in(t_list *start, int *pipe)
{
	t_list	*cur_tok;

	cur_tok = start;
	while (cur_tok)
	{
		if (cur_tok->type == PIPE)
		{
			pipe_parser(start, cur_tok, pipe);
			start = cur_tok->next;
			pipe_in(start, pipe);
			break ;
		}
		cur_tok = cur_tok->next;
	}
	if (!cur_tok)
		pipe_parser(start, cur_tok, pipe);
}
