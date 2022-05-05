/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mcamps <mcamps@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 15:26:43 by mcamps        #+#    #+#                 */
/*   Updated: 2022/04/14 12:35:35 by mcamps        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>

typedef enum e_lex
{
	DEFAULT,
	ARGUMENT,
	PIPE,
	REDIRECT,
	HERE_DOC,
	COMMAND,
	FILEPATH,	
}			t_lex;

typedef struct s_list
{
	t_lex			type;
	char			*var;
	char			*value;
	struct s_list	*next;	
	struct s_list	*prev;
}				t_list;

typedef struct s_data
{
	t_list			*envp;
	t_list			*lexer;
	int				lex_i;
	t_list			*lex_start;
	int				exit_status;
	char			*last_dir;
	char			*prompt;
	char			*line;
	int				n_flag;
}			t_data;

t_data	*g_data;

/* Error */
void	error_exit(char *exitcode);

/* Ft Utilities */
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	ft_free(char **array);

/* List Util */
t_list	*ft_lstnew(void *var, void *value);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
int		listsize(t_list *list);
char	**list_to_array(t_list *list, int type);
void	del(void *del);
void	ft_freenode(t_list *node);
void	ft_del_node(t_list *lst);

/* Lexer */
void	lexer(t_data *data);
int		has_dollar(char *str);
char	*insert_env_var(char *str, int i, int start);
void	set_type(t_data *data);
void	lexer_del_space(t_data *data);
void	lexer_edit_redir(t_data *data);
void	lexer_dollar(t_data *data);
char	*strip_quotes(char *line);
char	*parse_error(t_data *data);

/* Env */
void	init_env(char **envp, t_data *data);
char	*ft_get_env(char *str, t_list *env);
void	replace_env(char *var, char *value);

/* Parser */
void	parse(t_list *tokens);
void	pipe_in(t_list *start, int *pipe);
void	redirect_parser(t_list *start, t_list *end, int *old_fd);
void	redirect_loop(t_list *start, t_list *end);
t_list	*make_cmd_list(t_list **start, t_list *end);

/* Exec */
void	exec(t_list *cmd);
char	*strjoinjoin(char *path, char *c, char *cmd);
void	exec_basiccommands(char **path, t_list *cmd, int i);
int		last_occurance(char *str, char c);
int		check_dir(char *str);
int		ft_strcmp_special(const char *s1, const char *s2);

/* Here Doc */
void	here_doc(char *filepath, int *old_fd);
int		has_dollar(char *str);

/* Signals */
void	interupt(int sig);
void	quit(int sig);
void	ignore_sig(void);
void	here_doc_signal(int signal);

/* Commands */
void	execute_cd(t_list *cmd);
void	execute_echo(t_list *cmd);
void	execute_pwd(void);
void	execute_unset(t_list *cmd, t_list *envp);
void	execute_export(t_list *cmd);
char	*get_var(char *str);
char	*get_value(char *str);
int		validinput_check(char *str);
void	execute_env(t_list *envp, int fd);
void	execute_exit(t_list *cmd);

/* Util */
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(int i, char const *s1, char const *s2);
char	*ft_itoa(int n);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strchr(const char *str, int c);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	rl_replace_line(const char *text, int clear_undo);
void	stderr_print(char *prefix, char *value, char *suffix);
int		check_status(int status);

#endif