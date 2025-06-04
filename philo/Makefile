CC = cc
CFLAGS = -Wall -Wextra -Werror
CLEAKS = -fsanitize=address -g
CTHREADS = -fsanitize=thread -g

NAME = philo
SRC = main.c \
		ft_exit.c \
		ft_parse.c \
		ft_philo_print.c \
		ft_time.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

debug_leaks: $(OBJ)
	$(CC) $(CFLAGS) $(CLEAKS) -o $@ $(OBJ)

debug_race: $(OBJ)
	$(CC) $(CFLAGS) $(CTHREADS) -o $@ $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) -f $(OBJ)

fclean : clean
	$(RM) -f $(NAME) debug_leaks debug_race

re : fclean all

.PHONY: clean fclean re all