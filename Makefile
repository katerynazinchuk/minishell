NAME = minishell
LIBFT_DIR = libft
LIBFT = libft.a

SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(LIBFT_DIR)/include
CFLAGS += -I$(INCLUDE_DIR)
LFLAGS += -lreadline -lncurses

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

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:%.c=%.o))

all: $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT)
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<.."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Object files created."

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