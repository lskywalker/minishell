/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 18:30:10 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/12 18:36:51 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	listsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

void	ft_del_node(t_list *lst)
{
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prev)
		lst->prev->next = lst->next;
	ft_lstdelone(lst, &del);
}

void	del(void *del)
{
	free(del);
}
