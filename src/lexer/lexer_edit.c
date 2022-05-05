/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_edit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 17:36:30 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:49:27 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_edit_redir(t_data *data)
{
	t_list	*edit;

	edit = data->lexer;
	while (edit)
	{
		if (edit->next == NULL)
			break ;
		if (edit->var[0] == '>' && edit->next->var[0] == '>')
		{
			free(edit->var);
			edit->var = ft_strdup(">>");
			ft_del_node(edit->next);
		}
		else if (edit->var[0] == '<' && edit->next->var[0] == '<')
		{
			free(edit->var);
			edit->var = ft_strdup("<<");
			ft_del_node(edit->next);
		}
		edit = edit->next;
	}
}

void	lexer_del_space(t_data *data)
{
	t_list	*edit;
	t_list	*tmp_next;
	t_list	*tmp_prev;

	edit = data->lexer;
	while (edit)
	{
		if (edit->var[0] == ' ')
		{
			tmp_next = edit->next;
			tmp_prev = edit->prev;
			ft_del_node(edit);
			edit = tmp_next;
			if (tmp_prev == NULL)
				data->lexer = tmp_next;
		}
		else
			edit = edit->next;
	}
}

void	lexer_dollar(t_data *data)
{
	t_list	*edit;

	edit = data->lexer;
	while (edit)
	{
		edit->var = strip_quotes(edit->var);
		edit = edit->next;
	}
}

char	*parse_error(t_data *data)
{
	t_list	*parser;

	parser = data->lexer;
	while (parser)
	{
		if (parser->type == PIPE && (parser->next == NULL || \
		parser->prev == NULL))
			return (parser->var);
		if (parser->type == REDIRECT && parser->next == NULL)
			return ("newline");
		if (parser->next == NULL)
			break ;
		else if (parser->type == REDIRECT && parser->next->type != FILEPATH)
			return (parser->next->var);
		parser = parser->next;
	}
	return (NULL);
}
