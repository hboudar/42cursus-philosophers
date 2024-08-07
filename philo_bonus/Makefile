SRC		=	ft_atoi_bonus.c ft_putstr_fd_bonus.c main_bonus.c utils_bonus.c init_bonus.c philo_bonus.c \
			monitor_bonus.c
OBJ		= $(SRC:.c=.o)
HEADER	= philo_bonus.h
NAME	= philo_bonus
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
