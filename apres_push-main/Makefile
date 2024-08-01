CC = cc
NAME = minishell
SRS = parsing/ft_split.c parsing/linked_list.c parsing/heredoc_expand.c parsing/free_memory.c parsing/print.c parsing/expand1.c parsing/utils.c parsing/validators1.c parsing/ft_itoa.c parsing/parsing.c\
		parsing/syntax_errors.c parsing/validators.c parsing/length.c parsing/expand.c parsing/creat_node.c parsing/signals.c parsing/exit_status.c parsing/about_dollar.c\
		execution/builtins_util.c execution/echo.c execution/exit.c  execution/fonction_random.c parsing/ft_substr.c execution/SHLVL.c parsing/lenght1.c execution/unset.c execution/cd.c \
		execution/env.c execution/split.c execution/execution.c execution/export.c execution/pwd.c execution/exec_builtin.c execution/main.c\
		execution/tab_unset.c execution/export1.c execution/export2.c execution/export3.c \
		execution/execution1.c execution/execution2.c execution/execution3.c execution/execution4.c execution/env1.c\
		execution/cd1.c execution/env_reserv.c execution/save_varible.c execution/minishell.c execution/permessio.c execution/newfile.c\
		parsing/about_dollar1.c parsing/print1.c
OBJCTS = $(SRS:.c=.o)
CFLAGS = 

all : $(NAME)

$(NAME) : $(OBJCTS)
	$(CC) $(CFLAGS) $(OBJCTS) -o $(NAME) -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -rf $(OBJCTS)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY:clean
