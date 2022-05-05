/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 15:41:25 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/13 15:17:01 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir(char *file, int flags, int io)
{
	int	fd_filepath;

	fd_filepath = open(file, flags, 0777);
	if (fd_filepath == -1)
		error_exit("redirect failed");
	else
	{
		dup2(fd_filepath, io);
		close(fd_filepath);
	}
}

void	make_redirect(char *redirect, char *filepath, int *old_fd)
{
	if (!ft_strcmp(redirect, ">"))
		redir(filepath, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (!ft_strcmp(redirect, "<"))
		redir(filepath, O_RDONLY | O_CREAT, 0);
	else if (!ft_strcmp(redirect, ">>"))
		redir(filepath, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (!ft_strcmp(redirect, "<<"))
		here_doc(filepath, old_fd);
	old_fd = NULL;
}

void	redirect_parser(t_list *start, t_list *end, int *old_fd)
{
	while (start != end)
	{
		if (!start->next)
			break ;
		if (start->type == REDIRECT)
		{
			make_redirect(start->var, start->next->var, old_fd);
			start = start->next;
		}
		start = start->next;
	}
}

void	redirect_loop(t_list *start, t_list *end)
{
	t_list	*cmd;

	if (start->type != REDIRECT)
	{
		cmd = make_cmd_list(&start, end);
		if (cmd)
		{
			exec(cmd);
			ft_lstclear(&cmd, &del);
		}
	}
	else
		start = start->next;
}
