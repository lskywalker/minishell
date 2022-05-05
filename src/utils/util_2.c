/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:17:40 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:36:45 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	void	*ptr;

	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

static char	*fill(int n, int len, char *str)
{
	int		i;
	int		sign;

	i = len;
	sign = 1;
	str[i] = '\0';
	i--;
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

static int	nb_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = nb_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (fill(n, len, str));
}
