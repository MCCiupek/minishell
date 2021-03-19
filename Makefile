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

SRC =			main.c

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
				@echo "Compiled "$(NAME)" successfully!"

$(NAME) :		$(OBJS)
				@$(MAKE) -C ./libft bonus
				@cp ./libft/$(LIBFT) $(LIBFT) && cp ./libft/libft.h $(DIR_HEADERS)/libft.h
				@$(CC) $(COMPIL) $(OS) $(OBJS) -L $(LIB)libft -lft  -I $(DIR_HEADERS) -o $(NAME)

%.o: %.c
				@$(CC) $(FLAGS) $(OS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

bonus:			$(OBJS_BONUS)
				@$(MAKE) -C ./libft bonus
				@cp ./libft/$(LIBFT) $(LIBFT) && cp ./libft/libft.h $(DIR_HEADERS)/libft.h
				@$(CC) $(COMPIL) $(OS) $(OBJS_BONUS) -L $(LIB)libft -lft  -I $(DIR_HEADERS) -o $(NAME)

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)
				norminette ./libft/

clean:
				$(MAKE) -C ./libft clean
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(MAKE) -C ./libft fclean
				$(RM) $(LIBFT)
				$(RM) $(NAME)

git:			fclean
				git add .
				git commit -m "$(shell date)"
				git push

re:				fclean all

.PHONY:			all, clean, fclean, re, norme, git, bonus
