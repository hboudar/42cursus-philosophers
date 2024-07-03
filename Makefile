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
#  question : my program hangs when i run it, is there any flag to help me debug it?
#  answer : yes, you can use -g flag to compile your program with debug information, and then use gdb to debug it.
# how to use gdp?
# gdb is a powerful debugger, here are some common commands you can use with gdb:
# - run: run the program
# - break: set a breakpoint
# - next: execute the next line of code
# - step: step into a function
# - print: print the value of a variable
# - backtrace: print the call stack
# - quit: exit gdb
# how to lanch gdb?
# you can launch gdb by running gdb <program>, for example gdb ./philo
