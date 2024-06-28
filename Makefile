SRC		= philo.c init.c routine.c utils.c
OBJ		= $(SRC:.c=.o)
HEADER	= philo.h
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: utils $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -lpthread  $(OBJ) -o $(NAME) libft/libft.a

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

utils:
	cd libft && make

clean:
	$(RM) $(OBJ)

fclean: clean
	cd libft && make fclean
	$(RM) $(NAME)

re: fclean all
