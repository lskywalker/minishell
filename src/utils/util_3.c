/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:27:47 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 14:48:26 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(int i, char const *s1, char const *s2)
{
	char	*str;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (str);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;

	if (!dst)
		return (0);
	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (dstsize > 0)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*st;

	i = 0;
	st = (char *)str;
	while (st[i] != '\0')
	{
		if (st[i] == c && c != '\0')
			return (&st[i]);
		i++;
	}
	if (c == '\0')
		return (&st[i]);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	total;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	total = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (sign * total);
}
