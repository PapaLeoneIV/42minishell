# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rileone <rileone@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 14:02:36 by rileone           #+#    #+#              #
#    Updated: 2024/05/14 12:58:32 by rileone          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = libft
PRINTF_DIR = ./libft/printf
GNL_DIR = ./libft/gnl
SRCDIR = ./src
INCLUDES = ./includes
UTILS_ENV = ./utils/env
READ_SDTIN = ./utils/read_stdin
TOKENIZER = $(PARSER)/tokenizer
SYNTAX_HANDLER = $(PARSER)/syntax_analizer
QUOT_TOKENIZER = $(PARSER)/quoted_tokenizer
PARSER = ./utils/parser
VAR_EXPANS = $(PARSER)/var_expansion
EVERY_INCLUDES=-I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I$(INCLUDES) -I$(SRCDIR) -I$(UTILS_ENV) -I$(READ_SDTIN)


RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
COMPILE = $(CC) $(CFLAGS)
ARCHIVE = ar rcs

SRC =   $(addprefix $(UTILS_ENV)/, path_utils.c set_env.c) \
                $(addprefix $(READ_SDTIN)/, read_input.c) \
                $(addprefix $(TOKENIZER)/, tokenizer_state_methods.c tokenizer.c tokenizer_utils.c tokenizer_helpers.c tokenizer_slice_methods.c) \
                $(addprefix $(QUOT_TOKENIZER)/,quot_tokenizer.c quot_tokenizer_utils.c ) \
                $(addprefix $(SYNTAX_HANDLER)/, syntax_analizer.c syntax_analizer_helpers.c) \
                $(addprefix $(VAR_EXPANS)/, var_expansion_helpers.c)  \

all: $(NAME)


$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(COMPILE) $(CFLAGS) $(SRCDIR)/main.c $(EVERY_INCLUDES) $(SRC) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(PRINTF_DIR) -lftprintf -lreadline -o $(NAME)
clean:	
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

valgrind: all
	$(VALGRIND) ./$(NAME)

GDB = gdb

gdb: all
	$(GDB) ./$(NAME)


re: fclean all

.PHONY: all clean fclean