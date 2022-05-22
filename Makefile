# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:16:59 by bnidia            #+#    #+#              #
#    Updated: 2021/10/26 16:05:02 by bnidia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Manual for Makefile
# https://www.gnu.org/software/make/manual/html_node/index.html
NAME 	= philo

SRCDIR = ./src/
OBJDIR = ./obj/

SRC	= main.c init.c time.c print.c process_eat_sleep_think.c
OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))
D_FILES = $(addprefix $(OBJDIR), $(notdir$(SRC:.c=.d)))
HEADER = ./src/philo.h

CC = gcc -Werror -Wall -Wextra -fsanitize=address -pthread
DEBUG_SWITCH = TRUE
ifeq ($(DEBUG_SWITCH), TRUE)
	DEBUG = -g
else
	OPTIMIZATION = -O1
endif

all: $(NAME)

# translation of assembly language code into machine code
# -c, stops after assembly stage
# -MD lists both system header files and user header files, dependencies
# -MMD lists only user header files, dependencies
# $< the first prerequisite (usually a source file) main.c (dependency %.c)
# $@ is the name of the target being generated main.o (target %.o)
$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) | obj
	$(CC) $(DEBUG) $(OPTIMIZATION) -c $< -o $@ -MMD

# linking stage
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

obj:
	mkdir -p $(OBJDIR)

include $(wildcard $(D_FILES))

bonus: all

norm:
	norminette $(SRC) $(HEADER)

# rule for the cleaning
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(OBJDIR) $(NAME)

# rule for rebuild a project
re: fclean all

# directory exceptions
.PHONY: all clean fclean norm re bonus
