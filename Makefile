SHELL :=		/bin/bash

CC =			clang

FLAGS =			-Wall -Wextra -Werror -g

RM =			rm -rf

DIR_HEADERS =	./includes/

DIR_SRCS =		./srcs/

MLX_DIR = 		./

MLX_HEADER = 	/usr/local/include/

MLX_LIB = 		/usr/local/lib/

MLX_FLAGS	=	-lmlx

MACOS_FLAGS =	-framework OpenGL -framework AppKit

LINUX_FLAGS =	-lXext -lX11 -lm

LIBMLX =		libmlx.a

LIBFT =			libft.a

FSAN =			-fsanitize=address

SRC =			main.c \
				\
				prompt_utils.c \
				\
				builtin/builtin.c \
				builtin/builtin_cd.c \
				builtin/builtin_pwd.c \
				builtin/builtin_env.c \
				builtin/builtin_echo.c \
				builtin/builtin_echo_replace.c \
				builtin/builtin_echo_sep.c \
				builtin/builtin_echo_sep_utils.c \
				builtin/builtin_echo_utils.c \
				builtin/builtin_export.c \
				builtin/builtin_export_sort.c \
				builtin/builtin_export_utils.c \
				builtin/builtin_unset.c \
				builtin/builtin_unset_utils.c \
				builtin/builtin_exit.c \
				\
				parsing/parsing.c \
				parsing/check_line.c \
				parsing/utils.c \
				parsing/tokenize.c \
				parsing/redir.c \
				\
				utils/utils_1.c \
				utils/error.c \
				\
				env/env.c \
				env/var.c \
				env/replace.c \
				\
				hist/hist.c \
				\
				read_edit/read.c \
				read_edit/edit.c \
				read_edit/cursor.c \
				read_edit/arrows.c \
				read_edit/display.c \
				\
				signal.c \
				\
				exec/exec.c \
				exec/exec2.c \
				exec/pipe.c \
				exec/pipe2.c \
				exec/fds.c \
				exec/path.c

SRC_BONUS =		main.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

SRCS_BONUS =	$(addprefix $(DIR_SRCS), $(SRC_BONUS))

COMPIL =		$(FLAGS)# $(FSAN)

OBJS =			$(SRCS:.c=.o)

OBJS_BONUS =	$(SRCS_BONUS:.c=.o)

NAME =			minishell

UNAME := 		$(shell uname)

ifeq ($(UNAME),Darwin)
	OS = -D MACOS
endif

ifeq ($(UNAME),Linux)
	OS = -D LINUX
endif

all:			$(NAME)

$(NAME) :		echoCL $(OBJS) echoOK echoCS
				$(MAKE) -C ./libft bonus
				cp ./libft/$(LIBFT) $(LIBFT)
				$(CC) $(COMPIL) $(OS) $(OBJS) -L $(LIB)libft -lft -lncurses -o $(NAME)

%.o: %.c
				$(CC) $(FLAGS) $(OS) -I $(DIR_HEADERS) -c $< -o $@
				printf "$(GREEN)██"

bonus:			echoCL $(OBJS_BONUS) echoOK echoCS
				$(MAKE) -C ./libft bonus
				cp ./libft/$(LIBFT) $(LIBFT)
				$(CC) $(COMPIL) $(OS) $(OBJS_BONUS) -L $(LIB)libft -lft -lncurses -o $(NAME)

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)
				norminette ./libft/

clean:			echoCLEAN
				$(MAKE) -C ./libft clean
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(MAKE) -C ./libft fclean
				$(RM) $(LIBFT)
				$(RM) $(NAME)

git:			fclean
				git pull
				git add .
				git commit -m "$(shell date)"
				git push

re:				fclean all

.PHONY:			all, clean, fclean, re, norme, git, bonus
.SILENT:

# COLOR
#----------------reset----------------#
NC = \033[0m

#-----------Regular Colors------------#
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[0;37m

###########################ECHO
echoCL:
	printf "\n$(YELLOW)===> Compiling $(RED)$(NAME)$(NC)\n"
echoOK:
	printf "$(GREEN) OK$(NC)\n"
echoCS :
	printf "$(GREEN)===> Compilation Success$(NC)\n"
echoCLEAN :
	printf "$(PURPLE)$(NAME) ===> Cleanning$(NC)\n"
echoFCLEAN :
	printf "$(PURPLE)$(NAME) ===> Cleanning Exec & Lib$(NC)\n"