SRC		= libft/ft_atoi.c libft/ft_putstr_fd.c philo_main.c philo_init.c philo_routine.c philo_utils.c
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
