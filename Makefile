NAME		= philo
CC		= gcc -g
CFLAGS		= -Werror -Wall -Wextra
SRCS		= main.c  ft_utils.c init_data.c philo_algo.c timephilo.c
OBJCS		= $(SRCS:.c=.o)
RM		= rm -f
PTHREAD_INC	= -lpthread
all	: $(NAME)

$(NAME) : $(OBJCS) 
	$(CC) $(PTHREAD_INC) $(CFLAGS) -o $(NAME) $(OBJCS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "compilation seccesfuly"
clean:
		@$(RM) $(OBJCS)

fclean:	clean
		@$(RM) $(NAME)
		@echo "all is clean now"

re:		fclean all
