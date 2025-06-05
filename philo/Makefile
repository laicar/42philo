CC = cc
CFLAGS = -Wall -Wextra -Werror
CLEAKS = -fsanitize=address -g
CTHREADS = -fsanitize=thread -g

NAME = philo
SRC = main.c \
		ft_exit_free.c \
		ft_parse_arg.c \
		ft_philo_print.c \
		ft_time.c \
		init.c \
		monitor_routine.c \
		philo_routine.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

leaks_debug: $(OBJ)
	$(CC) $(CFLAGS) $(CLEAKS) -o $@ $(OBJ)

race_debug: $(OBJ)
	$(CC) $(CFLAGS) $(CTHREADS) -o $@ $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) -f $(OBJ)

fclean : clean
	$(RM) -f $(NAME) leaks_debug race_debug

re : fclean all

.PHONY: clean fclean re all