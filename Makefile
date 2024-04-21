# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 16:05:51 by pibouill          #+#    #+#              #
#    Updated: 2024/04/21 13:59:01 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
## ARGUMENTS

NAME 		= minitalk
SERVER		= server
SERVER_BONUS = server_bonus
CLIENT		= client
CLIENT_BONUS = client_bonus
CFLAGS 		= -Wall -Werror -Wextra -g
CC 			= cc
RM			= rm
SRC_DIR 	= src
INC			= -I ./inc/
INC_BONUS	= -I ./inc/minitalk_bonus.h
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

SERVER_SRC_FILES		= server
SERVER_SRC_FILES_BONUS	= server_bonus
CLIENT_SRC_FILES		= client
CLIENT_SRC_FILES_BONUS	= client_bonus

SERVER_SRC			=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SERVER_SRC_FILES)))
SERVER_OBJ			=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SERVER_SRC_FILES)))
SERVER_SRC_BONUS	=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SERVER_SRC_FILES_BONUS)))
SERVER_OBJ_BONUS	=   $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SERVER_SRC_FILES_BONUS)))

CLIENT_SRC			=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(CLIENT_SRC_FILES)))
CLIENT_OBJ			=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(CLIENT_SRC_FILES)))
CLIENT_SRC_BONUS	=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(CLIENT_SRC_FILES_BONUS)))
CLIENT_OBJ_BONUS	=   $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(CLIENT_SRC_FILES_BONUS)))

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

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_OBJ_BONUS)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(SERVER_BONUS) $(SERVER_OBJ_BONUS) -L $(LIB_DIR) -l $(LIB_CUT)
	+@echo "$(GREEN)$(SERVER_BONUS) compiled.$(END_COLOR)"

$(CLIENT_BONUS): $(CLIENT_OBJ_BONUS)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(CLIENT_BONUS) $(CLIENT_OBJ_BONUS) -L $(LIB_DIR) -l $(LIB_CUT)
	+@echo "$(GREEN)$(CLIENT_BONUS) compiled.$(END_COLOR)"

clean:
	+@rm -rf $(BIN_DIR)
	+@echo "$(BLUE)$(NAME) object files cleaned.$(END_COLOR)"
	+@make clean -C libft --no-print-directory

fclean: clean
	+@rm -f $(SERVER) $(SERVER_BONUS) $(CLIENT) $(CLIENT_BONUS)
	+@echo "$(YELLOW)$(NAME) executable files cleaned.$(END_COLOR)"
	+@rm -f libft/libft.a
	+@echo "$(YELLOW)$(LIB_DIR).a file cleaned.$(END_COLOR)"

re: fclean all
	+@echo "$(RED)Cleaned all and rebuilt $(NAME) and $(LIB_DIR)$(END_COLOR)"

################################################################################
## PHONY

.PHONY: all clean fclean re
