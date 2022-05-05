# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mcamps <mcamps@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/05 15:26:27 by mcamps        #+#    #+#                  #
#    Updated: 2022/04/14 12:35:00 by mcamps        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = $(SRCS:%=src/%)
SRCS = main.c \
	startup/signal.c \
	startup/exec.c \
	startup/env.c \
	lexer/lexer.c \
	lexer/lexer_dollar.c \
	lexer/lexer_type.c \
	lexer/lexer_edit.c \
	parser/parser.c \
	parser/parser_pipe.c \
	parser/parser_redir.c \
	parser/parser_here_doc.c \
	commands/command_cd.c \
	commands/command_echo.c \
	commands/command_env.c \
	commands/command_exit.c \
	commands/command_export.c \
	commands/command_export_util.c \
	commands/command_pwd.c \
	commands/command_unset.c \
	utils/ft_split.c \
	utils/exec_util.c \
	utils/util_lst.c \
	utils/util.c \
	utils/util_2.c \
	utils/util_3.c \
	utils/util_4.c \
	utils/util_5.c

FLAGS =  -Wall -Werror -Wextra
RL = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I \
	/Users/$(USER)/.brew/opt/readline/include/
OBJS = ${SRC:%.c=%.o}

%.o: %.c
	gcc -c -o $@ $< $(FLAGS)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) $(RL) -o $(NAME)

all: $(NAME)

test: all
	./$(NAME)

debug:
	gcc $(FLAGS) $(RL) -g3 -fsanitize=address $(SRC) -o $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
