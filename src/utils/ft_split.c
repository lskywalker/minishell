/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 10:31:20 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/12 18:49:40 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 2;
	while (s[i] == c)
	{
		if (s[i + 1] == '\0')
			return (1);
		i++;
	}
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				count++;
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	if (s[0] == '\0')
		return (1);
	return (count);
}

static int	ft_freemem(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (0);
}

static int	ft_sublen(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			return (count);
		i++;
		count++;
	}
	return (count);
}

static int	ft_newstr(char **str, char const *s, char c, int i)
{
	int	a;
	int	b;

	a = 0;
	while (s[i])
	{
		b = 0;
		str[a] = malloc(sizeof(char) * ft_sublen(&s[i], c) + 1);
		if (str[a] == NULL)
			return (ft_freemem(str, a - 1));
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			str[a][b] = s[i];
			b++;
			i++;
		}
		str[a][b] = '\0';
		a++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	int		count;
	char	**str;

	if (s == 0)
		return (0);
	size = ft_countword(s, c);
	str = malloc(size * sizeof(char *));
	if (!str)
		return (0);
	count = ft_newstr(str, s, c, 0);
	if (!count)
		str[size - 1] = NULL;
	return (str);
}
