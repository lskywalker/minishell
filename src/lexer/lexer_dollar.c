/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_dollar.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 13:03:22 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:49:24 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*get_env_var(char *var, t_list **start)
{
	t_list	*tmp;

	tmp = *start;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
		{
			free(var);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	if (!ft_strcmp(var, "?"))
	{
		free(var);
		return (ft_itoa(g_data->exit_status));
	}
	free(var);
	return (ft_strdup(""));
}

char	*insert_env_var(char *str, int i, int start)
{
	char	*ret;

	while (str[i] != '$')
		i++;
	ret = ft_substr(str, start, i);
	i++;
	start = i;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\'' && \
	str[i] != '=' && str[i] != '?' && str[i] != '$' && str[i] != '\"')
		i++;
	if (str[i] == '?')
	{
		ret = ft_strjoin(0, ret, get_env_var(ft_substr(str, start, 1), \
		&g_data->envp));
		i++;
	}
	else
		ret = ft_strjoin(0, ret, get_env_var(ft_substr(str, start, i - start), \
		&g_data->envp));
	ret = ft_strjoin(0, ret, ft_substr(str, i, ft_strlen(str)));
	free(str);
	return (ret);
}

char	*strip_quotes(char *line)
{
	char	*ret;

	ret = NULL;
	if (line[0] == '\"')
	{
		ret = ft_substr(line, 1, ft_strlen(line) - 2);
		while (has_dollar(ret) == 1)
			ret = insert_env_var(ret, 0, 0);
	}
	else if (line[0] == '\'')
		ret = ft_substr(line, 1, ft_strlen(line) - 2);
	else
	{
		ret = ft_strdup(line);
		while (has_dollar(ret) == 1)
			ret = insert_env_var(ret, 0, 0);
	}
	if (!ret)
		error_exit("Malloc Failed");
	free(line);
	return (ret);
}
