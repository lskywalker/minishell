/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 11:26:28 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/14 15:03:34 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	interupt(int sig)
{
	(void)sig;
	g_data->exit_status = 130;
	printf("\n");
}

void	prompt(int sig)
{
	(void)sig;
	g_data->exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit(int sig)
{
	char	*sig_str;

	sig_str = ft_itoa(sig);
	g_data->exit_status = 131;
	write(2, "Quit:", 5);
	write(2, sig_str, ft_strlen(sig_str));
	write(2, "\n", 1);
	free(sig_str);
}

void	ignore_sig(void)
{
	signal(SIGINT, prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	here_doc_signal(int signal)
{
	(void)signal;
	g_data->exit_status = 130;
	write(1, "\n", 1);
	exit(130);
}
