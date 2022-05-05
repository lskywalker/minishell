/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 13:03:57 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:49:30 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command(char *str)
{
	if (!ft_strcmp("echo", str))
		return (1);
	else if (!ft_strcmp("cd", str))
		return (1);
	else if (!ft_strcmp("pwd", str))
		return (1);
	else if (!ft_strcmp("export", str))
		return (1);
	else if (!ft_strcmp("unset", str))
		return (1);
	else if (!ft_strcmp("env", str))
		return (1);
	else if (!ft_strcmp("exit", str))
		return (1);
	return (0);
}

t_lex	type_select(t_list *prev, char *str)
{
	if (!ft_strcmp("|", str))
		return (PIPE);
	if (prev)
	{
		if (prev->type == REDIRECT && !(!ft_strcmp(">", str) || \
		!ft_strcmp(">>", str) || !ft_strcmp("<", str) || !ft_strcmp("<<", str)))
			return (FILEPATH);
	}
	if (!ft_strcmp(">", str) || !ft_strcmp("<", str))
		return (REDIRECT);
	else if (!ft_strcmp(">>", str) || !ft_strcmp("<<", str))
		return (REDIRECT);
	else if (check_command(str))
		return (COMMAND);
	else
		return (ARGUMENT);
	return (0);
}

void	set_type(t_data *data)
{
	t_list	*lexer;

	lexer = data->lexer;
	while (lexer)
	{
		lexer->type = type_select(lexer->prev, lexer->var);
		lexer = lexer->next;
	}
}
