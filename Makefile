NAME= minishell

SOURCE=	srcs/split_m.c \
		srcs/split_m1.c \
		srcs/lists.c \
		srcs/stack.c \
		srcs/parser.c \
		srcs/signal.c \
		srcs/ft_trim.c \
		srcs/equally.c \
		srcs/dequote.c \
		srcs/env_var.c \
		srcs/env_var2.c \
		srcs/env_var3.c \
		srcs/env_var4.c \
		srcs/minishell.c \
		srcs/command_cd.c \
		srcs/parser_help.c \
		srcs/parser_pipe.c \
		srcs/parser_pipe1.c \
		srcs/parser_help2.c \
		srcs/command_echo.c \
		srcs/parser_help1.c \
		srcs/command_exit.c \
		srcs/help_function.c \
		srcs/all_zero_free.c \
		srcs/command_unset.c \
		srcs/get_next_line.c \
		srcs/standart_split.c \
		srcs/help_function2.c \
		srcs/command_export.c \
		srcs/help_function3.c \
		srcs/help_function4.c \
		srcs/help_function5.c \
		srcs/command_export2.c \
		srcs/command_equally.c \
		srcs/get_next_line_mini.c


OSOURCE= $(SOURCE:.c=.o)

all: $(NAME) pepe

%.o: %.c
	@gcc -Wall -Werror -Wextra -c $< -o $@ -I ./includes

$(NAME): $(OSOURCE)
	@gcc -g $(OSOURCE) -o $(NAME)

pepe:
	@echo "⠄⠄⠄⡯⢿⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄"
	@echo "⠄⠄⠄⡯⣗⠄⠄⠄⠄⠄⢀⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄"
	@echo "⠄⠄⠄⡯⣳⠄⢀⣤⣾⣿⣿⣿⣿⣶⣄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄"
	@echo "⠄⠄⠄⢿⡖⢤⣿⣿⣿⣭⣿⣿⣯⣭⣛⢾⡿⠿⠿⣿⣦⠄⠄⠄⠄⠄⠄⠄"
	@echo "⠄⠄⣰⣾⣿⣿⣿⣿⣿⣿⠭⣽⣽⣯⠭⣔⢿⣿⣿⣷⣾⣄⠄⠄⠄⠄⠄⠄"
	@echo "⢀⣼⣿⣿⣿⣿⣿⣷⣭⣛⢿⣿⣿⣿⣿⣷⡧⣶⣤⣴⣶⣫⡵⡀⠄⠄⠄⠄"
	@echo "⣾⣿⣿⣿⣿⣿⣟⢿⣿⣿⣓⡩⠽⠛⠛⠛⠣⣿⣿⣿⣿⣿⣿⣷⠄⠄⠄⠄"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⡿⢷⣾⣯⣭⡭⠍⠋⠄⠄⠄⠄"
	@echo "⣿⣿⣿⣿⣿⣿⣫⣭⣽⣛⡿⢿⣿⣿⣿⣿⣿⣷⣶⣶⣆⠄⠄⠄⠄⠄⠄⠄"
	@echo "⢙⠻⣿⣿⣿⣷⣽⣛⡾⢭⣿⣛⡶⢭⣝⣻⠿⣿⣿⣿⠿⠇⠄⠄⠄⠄⠄⠄"
	@echo "⣯⣉⠎⡭⣛⠻⢿⣿⣿⣿⣶⣭⣛⡳⠶⣯⣭⣿⣛⣛⠻⠃⠄⠄⠄⠄⠄⠄"
	@echo "⣿⣿⣿⣷⣧⣭⣄⣚⠭⠙⢛⡛⡿⠿⠿⠷⠶⠊⠉⠉⠄⠄⠄⠄⠄⠄⠄⠄"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣿⣦⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄"

clean:
	@rm -rf $(OSOURCE)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all
