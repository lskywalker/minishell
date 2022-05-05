/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_lst.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 15:40:02 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/12 18:36:54 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *var, void *value)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->type = DEFAULT;
	list->var = var;
	list->value = value;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	(*del)(lst->var);
	(*del)(lst->value);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (del == NULL)
		return ;
	while (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(current, *del);
	}
	*lst = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
