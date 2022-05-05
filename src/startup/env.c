/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 12:23:28 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/14 14:49:38 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env(char *var, char *value)
{
	t_list	*envp;

	envp = g_data->envp;
	while (envp)
	{
		if (!ft_strcmp(envp->var, var))
		{
			free(envp->var);
			free(envp->value);
			envp->value = value;
			envp->var = var;
			return ;
		}
		envp = envp->next;
	}
	ft_lstadd_back(&g_data->envp, ft_lstnew(var, value));
}

char	*ft_get_env(char *str, t_list *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*set_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*set_env_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

void	init_env(char **envp, t_data *data)
{
	t_list	*new;
	int		i;

	if (envp == NULL)
		return ;
	i = 1;
	if (!envp[0])
		return ;
	new = ft_lstnew(set_env_var(envp[0]), set_env_value(envp[0]));
	data->envp = new;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&new, ft_lstnew(set_env_var(envp[i]), \
		set_env_value(envp[i])));
		if (!new)
			error_exit("Malloc Failed");
		new = new->next;
		i++;
	}
	new->next = NULL;
}
