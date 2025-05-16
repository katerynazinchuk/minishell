NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(LIBFT_DIR)/include
CFLAGS += -I$(INCLUDE_DIR)
LFLAGS += -lreadline -lncurses

SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include

LIBFT_DIR = libft
LIBFT = libft.a

# Define the source files and object files
BUILD_IN = src/builtins/
ENV = src/env/env_errors_frees.c \
		src/env/env_operations.c
EXECUTOR = src/executor/
LEXER = src/lexer/create_node_list.c \
		src/lexer/initialize_structs.c \
		src/lexer/token_types.c \
		src/lexer/lexer.c \
		src/lexer/token_word_utils.c \
		src/lexer/tokenization_utils.c
EXPANDER = src/expander/expand_var.c \
			src/expander/utils.c \
			src/expander/free_exp.c
PARSER = src/parser/parser.c \
# SIGNALS = 
UTILS = src/utils/utils.c \
		src/utils/init_shell.c

ERRORS = src/errors/lexer_error.c \
		src/errors/common_errors.c

SRC = $(LEXER) $(UTILS) $(ERRORS) $(ENV) $(EXPANDER) src/main.c 
#signal.c

OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT)
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) $(LFLAGS)

$(LIBFT_DIR)/$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re