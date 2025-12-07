
NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.c \
              init.c \
              thread.c \
              parse_utils.c \
              atoi.c \
              routine.c \
			  free_destroy.c \
			  monitor.c

OBJS        = $(SRCS:.c=.o)

HDRS        = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re