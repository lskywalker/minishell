/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 13:47:53 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:47:58 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_pipe(int *pipe)
{
	*pipe = 0;
}

void	parse(t_list *tokens)
{
	int	pipe;

	first_pipe(&pipe);
	if (tokens)
		pipe_in(tokens, &pipe);
	if (pipe != 0)
		close(pipe);
}
