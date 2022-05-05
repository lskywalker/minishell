/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_5.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:45:18 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 13:00:50 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_special(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i] || s1[i] + 32 == s2[i]) && s1[i])
		i++;
	if (s1[i] - 32 == s2[i])
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	stderr_print(char *prefix, char *value, char *suffix)
{
	if (prefix)
		write(2, prefix, ft_strlen(prefix));
	if (value)
		write(2, value, ft_strlen(value));
	if (suffix)
		write(2, suffix, ft_strlen(suffix));
	write(2, "\n", 1);
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
