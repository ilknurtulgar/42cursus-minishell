NAME = minishell
SRCS = main.c \
	   error.c \
	   error2.c \
	   free.c \
	   init.c \
	   signal.c \
	   parser/parser.c \
	   parser/p_quote.c \
	   parser/p_pipe.c \
	   parser/p_redirection.c \
	   utils/parser_util.c \
	   utils/parser_util_2.c \
	   lexer/lexer.c \
	   lexer/set_meta.c \
	   lexer/dolar_handler.c \
	   lexer/dolar_handler2.c \
	   lexer/dolar_handler3.c \
	   utils/lexer_util.c \
	   builtin/echo.c \
	   builtin/cd.c \
	   builtin/pwd.c \
	   builtin/env.c \
	   builtin/export_util.c \
	   builtin/export.c \
	   builtin/zi_unset.c \
	   builtin/builtin.c \
	   builtin/exit.c \
	   execute/exec.c \
	   execute/redirect.c \
	   execute/exec_util.c \
	   execute/exec_util2.c \
	   execute/heredoc.c \
	   execute/heredoc_util.c \
	   execute/redirect_util.c \
	   execute/cmd.c \
	   execute/run_redirect.c \
	   execute/exec_variable.c \
	   execute/pipe.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address #-fsanitize=leak -g
RM = rm -rf
LIBFT = ./includes/libft/libft.a
READLINE_DIR = readline
READLINE = $(READLINE_DIR)/lib/libreadline.a

all: $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=$(PWD)/$(READLINE_DIR)
	cd readline-8.2 && make install
	$(RM) readline-8.2 readline-8.2.tar.gz

$(LIBFT):
	make -C ./includes/libft -s
	make bonus  -C ./includes/libft -s
$(NAME): $(OBJS) $(LIBFT) $(READLINE)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBFT) -L$(PWD)/$(READLINE_DIR)/lib -I$(PWD)/$(READLINE_DIR)/include -lreadline  
#-lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(PWD)/$(READLINE_DIR)/include/

clean:
	make clean -C ./includes/libft -s
	make bonus  clean -C ./includes/libft -s
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./includes/libft -s
	make bonus fclean -C ./includes/libft -s
	$(RM) $(NAME)
	$(RM) $(READLINE_DIR)

re: fclean all

.PHONY: all clean fclean re
