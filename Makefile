# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 16:05:51 by pibouill          #+#    #+#              #
#    Updated: 2024/04/10 15:49:34 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
## ARGUMENTS

NAME 		= minitalk
SERVER		= server
CLIENT		= client
CFLAGS 		= -Wall -Werror -Wextra -g
CC 			= cc
RM			= rm
SRC_DIR 	= src
INC			= -I ./inc/
BIN_DIR 	= bin
LIB_INC 	= -I ./libft/inc/
LIB_DIR 	= libft
LIB_CUT		= $(shell echo $(LIB_DIR) | cut -c 4-)

################################################################################
## COLORS

GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
RED			= \033[0;91m
END_COLOR	= \033[0;39m

################################################################################
## SOURCES

SERVER_SRCS	= server
CLIENT_SRCS	= client

SERVER_SRC	= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SERVER_SRCS)))
SERVER_OBJ	= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SERVER_SRCS)))

CLIENT_SRC	= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(CLIENT_SRCS)))
CLIENT_OBJ	= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(CLIENT_SRCS)))

################################################################################
## RULES

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(SERVER) $(SERVER_OBJ) -L $(LIB_DIR) -l $(LIB_CUT)
	+@echo "$(GREEN)$(SERVER) compiled.$(END_COLOR)"

$(CLIENT): $(CLIENT_OBJ)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(CLIENT) $(CLIENT_OBJ) -L $(LIB_DIR) -l $(LIB_CUT)
	+@echo "$(GREEN)$(CLIENT) compiled.$(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	+@$(CC) -c $(CFLAGS) $(INC) $(LIB_INC) $< -o $@
	+@echo "$(BLUE)Compiling... $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	+@mkdir $(BIN_DIR)
	+@echo "$(YELLOW)Created $(BIN_DIR)/ directory at $(NAME)/$(END_COLOR)"

clean:
	+@rm -rf $(BIN_DIR)
	+@echo "$(BLUE)$(NAME) object files cleaned.$(END_COLOR)"
	+@make clean -C libft --no-print-directory

fclean: clean
	+@rm -f $(NAME)
	+@echo "$(YELLOW)$(NAME) executable files cleaned.$(END_COLOR)"
	+@rm -f libft/libft.a
	+@echo "$(YELLOW)$(LIB_DIR).a file cleaned.$(END_COLOR)"

re: fclean all
	+@echo "$(RED)Cleaned all and rebuilt $(NAME) and $(LIB_DIR)$(END_COLOR)"

################################################################################
## PHONY

.PHONY: all clean fclean re
