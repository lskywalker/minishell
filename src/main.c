/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 15:25:46 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/13 19:29:42 by lsmit         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_envlist(t_data *data)
{
	t_list	*cmd;

	cmd = ft_lstnew(ft_strdup("OLDPWD"), NULL);
	execute_unset(cmd, data->envp);
	ft_freenode(cmd);
}

void	lexer_norm(t_data *data)
{
	lexer(data);
	lexer_edit_redir(data);
	lexer_del_space(data);
	set_type(data);
}

void	get_argument(t_data *data)
{
	t_list	*lex_start;

	ignore_sig();
	data->line = readline(data->prompt);
	if (data->line == NULL)
		exit(data->exit_status);
	if (data->line && *data->line)
		add_history(data->line);
	lexer_norm(data);
	lex_start = data->lexer;
	if (!parse_error(data))
	{
		lexer_dollar(data);
		parse(data->lexer);
	}
	else
	{
		data->exit_status = 258;
		printf("syntax error near unexpected token '%s'\n", parse_error(data));
	}
	ft_lstclear(&lex_start, &del);
}

void	update_shlvl(t_data *data)
{
	t_list	*envp;
	int		nb;

	envp = data->envp;
	while (envp)
	{
		if (!ft_strcmp(envp->var, "SHLVL"))
		{
			nb = ft_atoi(envp->value);
			free(envp->value);
			envp->value = ft_itoa(nb + 1);
		}
		envp = envp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1 && argv)
		error_exit("Too many arguments");
	g_data = &data;
	ft_bzero(&data, sizeof(t_data));
	init_env(envp, &data);
	update_shlvl(&data);
	reset_envlist(&data);
	data.prompt = "minishell$ ";
	while (1)
		get_argument(&data);
	return (0);
}
