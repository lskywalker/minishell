/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 18:03:10 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/14 13:22:40 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freenode(t_list *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

t_list	*ft_delmiddle(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *list;
	tmp2 = (*list)->next;
	*list = (*list)->prev;
	(*list)->next = tmp2;
	tmp2->prev = *list;
	ft_freenode(tmp);
	return (*list);
}

void	ft_delnode(t_list **list)
{
	t_list	*tmp;

	if (!(*list)->prev && (*list)->next)
	{
		tmp = *list;
		*list = (*list)->next;
		(*list)->prev = NULL;
		ft_freenode(tmp);
	}
	else if (!(*list)->next && (*list)->prev)
	{
		tmp = *list;
		*list = (*list)->prev;
		(*list)->next = NULL;
		ft_freenode(tmp);
	}
	else
		*list = ft_delmiddle(list);
}

static int	valid_identifier(t_list *cmd)
{
	int		ret;

	ret = 0;
	while (cmd)
	{
		if (!validinput_check(cmd->var))
		{
			stderr_print("minishell: unset: '", cmd->var, \
			"': not a valid identifier");
			g_data->exit_status = 1;
			ret = 1;
		}
		cmd = cmd->next;
	}
	return (ret);
}

void	execute_unset(t_list *cmd, t_list *envp)
{
	if (valid_identifier(cmd))
		return ;
	while (cmd)
	{
		while (envp)
		{
			if (!ft_strcmp(cmd->var, envp->var))
			{
				ft_delnode(&envp);
				break ;
			}
			if (envp->next == NULL)
				break ;
			envp = envp->next;
		}
		while (envp->prev)
			envp = envp->prev;
		cmd = cmd->next;
	}
	g_data->envp = envp;
}
