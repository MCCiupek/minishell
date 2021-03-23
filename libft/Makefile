# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 15:18:07 by mciupek           #+#    #+#              #
#    Updated: 2021/01/11 17:03:29 by mciupek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
SRCS		= ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strlen.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_strlcpy.c\
		ft_strcat.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_atof.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		get_next_line.c\
		get_next_line_utils.c\
		get_next_line_utils2.c\
		ft_arraysize.c\

BONUS		= ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

DIR		= ./
CC		= clang
FLAGS		= -Wall -Wextra -Werror
OBJ		= $(addprefix $(DIR), $(SRCS:.c=.o))
OBJBONUS	= $(addprefix $(DIR), $(BONUS:.c=.o))

$(DIR)%.o:	$(DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus:		$(OBJ) $(OBJBONUS)
	ar rcs $(NAME) $(OBJ) $(OBJBONUS)

all:		$(NAME)

clean:
	rm -f $(OBJ) $(OBJBONUS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
