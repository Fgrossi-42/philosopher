BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
PUR			= \033[0;35m
YLW			= \033[0;33m
RST			= \033[0m
END			= \e[0m

NAME		= philo_B

FILES = philo_B \
			philo_utils_B	\
			philo_utils_2_B	\
			controls_B	\

PROJECT_H	= Incl/philo_B.h
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

SRCS_DIR = ./Src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./Src/
OBJS = $(addprefix $(SRCS_DIR), $(addsuffix .o, $(FILES)))

PTHEAD_FLAG = -pthread
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)src
	@$(CC) $(CC_FLAGS) $(PTHEAD_FLAG) -c $< -o $@
	@printf	"\033[2K\r${GRN}[COMPILING]${RST} '$<' $(END)\n"

$(NAME): $(OBJECTS_PREFIXED)
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS)
	@printf "\033[2K\r${PUR}[CREATED]\033[0m $(NAME)$(END)\n"

all: $(NAME)

clean:
	@rm -rf $(addprefix $(OBJS_DIR), $(SRCS_DIR))
	@printf "\033[2K\r${YLW}[CLEAN]${RST} done$(END)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[2K\r${RED}[DESTROYED]${RST} $(NAME)$(END)\n"

re: fclean all

.PHONY:		all clean fclean re