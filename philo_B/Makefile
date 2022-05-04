NAME = philo_B

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PTHEAD_FLAG = -pthread
FILES = philo_B \
			philo_utils_B	\
			philo_utils_2_B	\
			controls_B	\

SRCS_DIR = ./Src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./Src/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o: $(SRCS)
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(PTHEAD_FLAG) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re