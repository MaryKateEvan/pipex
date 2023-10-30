# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mevangel <mevangel@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 15:07:21 by mevangel          #+#    #+#              #
#    Updated: 2023/10/29 21:51:28 by mevangel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

SRC		=	pipex.c utils.c
OBJ		=	$(SRC:%.c=%.o)
LIBFT	=	minilib/minilib.a

$(NAME): $(OBJ)
		@cd minilib && make
		@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)pipex compiled!$(WHITE)"

all:	$(NAME)

clean:	
		@cd minilib && make clean
		@rm -f $(OBJ)
		@echo "$(CYAN)object files cleaned!$(WHITE)"

fclean:	clean
		@cd minilib && make fclean
		@rm -f $(NAME)
		@echo "$(CYAN)pipex executable file, object files and minilib.a cleaned!$(WHITE)"

re:		fclean all

.PHONY: all clean fclean re