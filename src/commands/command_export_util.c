/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_export_util.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:20:18 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 13:06:34 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	if (str[i] == '=')
		return (ft_strdup("="));
	while (str[i])
	{
		if (str[i] == '=')
		{
			ret = malloc(i * sizeof(char *));
			j = 0;
			while (j < i)
			{
				ret[j] = str[j];
				j++;
			}
			ret[j] = '\0';
			return (ret);
		}
		i++;
	}
	return (ft_strdup(str));
}

char	*get_value(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			ret = malloc((ft_strlen(str) - i + 1) * sizeof(char *));
			j = 0;
			i++;
			while (str[i])
			{
				ret[j] = str[i];
				j++;
				i++;
			}
			ret[j] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	validinput_check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
