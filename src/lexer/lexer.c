/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:26:13 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:49:21 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	i_to_c(t_data *data, int i, int start)
{
	while (data->line[i] != '\0')
	{
		if ((data->line[i] == '\'' || data->line[i] == '\"') && start != i)
			return (i);
		if (data->line[i] == '\"')
		{
			i++;
			while (data->line[i] != '\"' && data->line[i] != '\0')
				i++;
			return (i + 1);
		}
		if (data->line[i] == '\'')
		{
			i++;
			while (data->line[i] != '\'' && data->line[i] != '\0')
				i++;
			return (i + 1);
		}
		if (data->line[i] == '|' || data->line[i] == '>' || \
		data->line[i] == '<' || data->line[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

int	quotes(t_data *data)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	if (!data->line)
		return (0);
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '\'')
			single_q++;
		else if (data->line[i] == '\"')
			double_q++;
		i++;
	}
	if (double_q % 2 == 0 && single_q % 2 == 0)
		return (1);
	g_data->exit_status = 1;
	printf("%s: quotes not closed\n", g_data->prompt);
	free(data->line);
	return (0);
}

char	*fill_tmp(char *line, int start, int i)
{
	char	*tmp;

	if (start == i)
		tmp = ft_substr(line, start, 1);
	else if (start == 0)
		tmp = ft_substr(line, start, i - start);
	else
		tmp = ft_substr(line, start, i - start);
	if (!tmp)
		error_exit("Malloc Failed");
	return (tmp);
}

void	lexer(t_data *data)
{
	t_list	*node;
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	start = 0;
	data->lexer = NULL;
	if (quotes(data) == 0)
		return ;
	while (data->line[i] != '\0')
	{
		i = i_to_c(data, i, i);
		tmp = fill_tmp(data->line, start, i);
		if (start == i)
			i++;
		node = ft_lstnew(tmp, NULL);
		if (!node)
			error_exit("Malloc Failed");
		ft_lstadd_back(&data->lexer, node);
		start = i;
	}
	free(data->line);
}
