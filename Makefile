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
ENV = src/env/
EXECUTOR = src/executor/
LEXER = src/lexer/create_node_list.c \
		src/lexer/initialize_structs.c \
		src/lexer/token_types.c \
		src/lexer/lexer.c \
		src/lexer/token_word_utils.c \
		src/lexer/tokenization_utils.c
PARSER = src/parser/parser.c \
		src/parser/ 
SIGNALS = 
UTILS = src/utils/utils.c
ERRORS = src/errors/lexer_error.c

SRC = $(LEXER) $(UTILS) $(ERRORS) main.c signal.c

OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

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