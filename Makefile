# Project
NAME		= minishell

# Directories
SRC_DIR		= source
BUILD_DIR	= build
BIN_DIR		= bin
INCLUDE_DIR	= include
LIB_DIR		= libs/libft

# Source files organized by modules
SOURCES		= main.c \
			  utils.c \
			  \
			  tokens/split.c \
			  tokens/quoting.c \
			  tokens/quoting_utils.c \
			  tokens/utils.c \
			  tokens/operator_split.c \
			  tokens/split_utils.c \
			  tokens/word_split.c \
			  tokens/split_helpers.c \
			  \
			  commands/parse.c \
			  commands/redirections.c \
			  commands/pipes.c \
			  commands/syntax_utils.c \
			  commands/syntax_handlers.c \
			  commands/syntax_check.c \
			  \
			  signals/config.c \
			  \
			  expand_dollar/expand_dollar.c \
			  expand_dollar/command_substitution.c \
			  expand_dollar/late_expansion.c \
			  \
			  environment/environment.c \
			  environment/env_simple.c \
			  \
			  builtins/cd.c \
			  builtins/echo.c \
			  builtins/env.c \
			  builtins/exit.c \
			  builtins/export.c \
			  builtins/pwd.c \
			  builtins/unset.c \
			  builtins/builtins_utils.c \
			  builtins/true_false.c \
			  \
			  pipes/inputs_bonus.c \
			  pipes/pipes_bonus.c \
			  pipes/split_bonus.c \
			  pipes/utils_bonus.c \
			  pipes/utils_fd_bonus.c \
			  pipes/integration.c \
			  pipes/path_utils.c \
			  pipes/args_utils.c \
			  pipes/redirection_handlers.c \
			  pipes/redirection_setup.c \
			  pipes/exec_utils.c \
			  pipes/pipe_utils.c \
			  pipes/pipe_exec.c \
			  pipes/multi_pipe_utils.c \
			  pipes/multi_pipe_exec.c \
			  pipes/env_prep.c \
			  pipes/exec_helpers.c \
			  pipes/path_getters.c \
			  pipes/path_search.c

# Object files
OBJECTS		= $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Libraries
LIBFT		= $(LIB_DIR)/libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I$(INCLUDE_DIR) -I$(LIB_DIR)/include
RM			= rm -rf

# System detection for readline
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	# macOS
	READLINE_PATH = $(shell brew --prefix readline 2>/dev/null || echo "/opt/homebrew")
	INCLUDES += -I$(READLINE_PATH)/include
	LDFLAGS = -L$(READLINE_PATH)/lib -L$(LIB_DIR)
else
	# Linux
	LDFLAGS = -L$(LIB_DIR)
endif

LIBS		= $(LDFLAGS) -lft -lreadline -lncurses -lm

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "Linking $(NAME)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BIN_DIR)/$(NAME)
	@echo "$(NAME) built successfully!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIB_DIR)

libft:
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo "Cleaning object files..."
	@$(RM) $(BUILD_DIR)

fclean: clean
	@echo "Cleaning all generated files..."
	@$(RM) $(BIN_DIR)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft show