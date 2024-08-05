SRC		= ft_atoi.c ft_putstr_fd.c main.c init.c routine.c utils.c monitor.c
OBJ		= $(SRC:.c=.o)
HEADER	= philo.h
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -lpthread  $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
