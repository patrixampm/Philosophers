NAME    = philo
USER    = ppeckham
CFLAGS  = -Wall -Wextra -Werror -fsanitize=address -g
CC      = clang

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

SRCS	:=	src/main.c src/arg_check.c src/init_structs.c \
			src/monitor.c src/philo_routine.c src/utils.c \
			src/threads.c

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
			@echo "$(YELLOW)Linking: $(RESET)$(NAME)"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(MAGENTA)philosophers compiled!$(RESET)"

%.o: %.c
			@echo "$(BLUE)Compiling: $(RESET)$(notdir $<)"
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -rf $(OBJS)
			@echo "$(RED)Cleaning philosophers object files.$(RESET)"

fclean: clean
			@rm -rf $(NAME)
			@echo "$(RED)Cleaning philosophers executable.$(RESET)"

re: fclean all
			@echo "$(YELLOW)philosophers recompiled$(RESET)"

.PHONY: all clean fclean re
