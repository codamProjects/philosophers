
#valgrind --tool=helgrind / --tool=drd

CC= cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
LFLAGS = -pthread
RM= rm -r

HEADER= philosophers.h
NAME= philo

ODIR= obj

SOURCE= main.c \
			init.c \
			utils.c \
			threads.c \
			printing.c \
			error_free.c \

OBJECT= $(addprefix $(ODIR)/,$(SOURCE:.c=.o))

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(ODIR)" ]; then \
		$(RM) $(ODIR); \
	fi

fclean: clean
	@if [ -x "$(NAME)" ]; then \
		$(RM) $(NAME); \
	fi

re: fclean all

.PHONY: all clean fclean re
