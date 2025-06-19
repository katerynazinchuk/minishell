NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
CFLAGS += -I$(LIBFT_DIR)/include
CFLAGS += -I$(INCLUDE_DIR)
# CFLAGS += -fsanitize=address,undefined
LFLAGS += -lreadline -lncurses 
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
LIBFT_DIR = libft
LIBFT = libft.a

BUILD_IN = src/builtins/
ENV = src/env/env_errors_frees.c \
		src/env/env_operations.c \
		src/env/env_utils.c

EXECUTOR = src/executor/executor.c \
		src/executor/exe_utils.c \
		src/executor/redir_dispatch.c \
		src/executor/run_builtin_1.c \
		src/executor/run_builtin_2.c \
		src/executor/run_external.c \
		src/executor/path_parser.c
LEXER = src/lexer/create_node_list.c \
		src/lexer/initialize_structs.c \
		src/lexer/token_types.c \
		src/lexer/lexer.c \
		src/lexer/segment.c \
		src/lexer/segment_utils.c \
		src/lexer/lexer_debug.c 
EXPANDER = src/expander/expand_var.c \
			src/expander/utils.c \
			src/expander/free_exp.c
PARSER = src/parser/parser.c \
			src/parser/redirects.c \
			src/parser/parser_debug.c \
			src/parser/free_parser.c
HEREDOC = src/heredoc/heredoc.c \
			src/heredoc/utils.c \
			src/heredoc/heredoc_cleanup.c
MY_SIGNAL = src/signals/signal.c
UTILS = src/utils/utils.c \
		src/utils/init_shell.c \
		src/utils/utils_main.c \
		src/utils/shell_debug.c

ERRORS = src/errors/lexer_error.c \
		src/errors/dispatch_errors.c \
		src/errors/common_errors.c \
		src/errors/pipe_error.c \
		src/errors/syntax_fn.c \
		src/errors/execute_fn.c


SRC = $(LEXER) $(UTILS) $(ERRORS) $(ENV) $(EXPANDER) $(PARSER) $(HEREDOC) $(MY_SIGNAL) $(EXECUTOR) src/rewrite_main.c 
#signal.c

OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/$(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) $(LFLAGS)

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

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re valgrind
