NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g -O0
RM			= rm -f

SRC			= main.c check_valid_input.c utils.c init.c thread_monitor.c cleanup.c \
			  routine/routine.c \
			  routine/thinking.c \
			  routine/sleeping.c \
			  routine/eating.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
