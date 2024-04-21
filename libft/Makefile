# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibouill <pibouill@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:56:08 by pibouill          #+#    #+#              #
#    Updated: 2024/04/10 15:48:58 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM 				= rm -rf
AR 				= ar rc
SRC_DIR			= src
INC_DIR			= inc
BIN_DIR			= bin

# **************************************************************************** #
# COLORS

GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
END_COLOR		= \033[0;39m

# **************************************************************************** #
# SOURCES

SRCS				= $(shell find ./src -type f -exec basename {} \; | rev | cut -d. -f2- | rev)
SRC					= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS)))
OBJ 				= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRCS)))

# **************************************************************************** #
# RULES

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) compiled. $(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BIN_DIR)
	@$(CC) -c $(CFLAGS) -I $(INC_DIR) $< -o $@
	@echo "$(BLUE)Compiling... $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@echo "$(YELLOW)Created $(BIN_DIR)/ directory$(END_COLOR)"

clean:
	@$(RM) $(BIN_DIR)
	@echo "$(BLUE)$(NAME) object files and bin/ cleaned.$(END_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(NAME) .a file cleaned.$(END_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME)$(END_COLOR)"

# **************************************************************************** #

.PHONY: all clean fclean re bonus
