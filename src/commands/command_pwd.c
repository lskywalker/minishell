/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsmit <lsmit@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 13:30:06 by lsmit         #+#    #+#                 */
/*   Updated: 2022/04/13 14:55:57 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pwd(void)
{
	char	cwd[PATH_MAX];

	g_data->exit_status = 0;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		stderr_print("getcwd() error", 0, 0);
}
