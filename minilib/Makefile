# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 15:04:14 by mevangel          #+#    #+#              #
#    Updated: 2023/10/30 01:54:03 by mevangel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minilib.a

CFLAGS := -Wall -Wextra -Werror
CC := cc

SRCS := ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_split.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_free_2darr.c

OBJS := $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re
