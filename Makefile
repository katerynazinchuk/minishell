NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
CFLAGS += -I$(LIBFT_DIR)/include
CFLAGS += -I$(INCLUDE_DIR)
# CFLAGS += -fsanitize=address,undefined,leak
LFLAGS += -lreadline -lncurses 
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
LIBFT_DIR = libft
LIBFT = libft.a



ENV = src/env/env_errors_frees.c \
		src/env/env_operations.c \
		src/env/env_utils.c

EXECUTOR = src/executor/executor.c \
		src/executor/child_processes.c \
		src/executor/free_execute.c \
		src/executor/exe_utils.c \
		src/executor/redir_dispatch.c \
		src/executor/run_external.c \
		src/executor/path_parser.c 

BUILT_IN = src/builtins/cd_pwd.c \
			src/builtins/echo.c \
			src/builtins/exit.c \
			src/builtins/export.c \
			src/builtins/get_builtin.c \
			src/builtins/unset_env.c \
			src/builtins/utils_builtins.c

LEXER = src/lexer/create_token_list.c \
		src/lexer/free_lexer.c \
		src/lexer/define_token_type.c \
		src/lexer/lexer.c \
		src/lexer/create_segment.c \
		src/lexer/utils_segments.c \
		src/lexer/lexer_debug.c

EXPANDER = src/expander/expand_var.c \
			src/expander/expand_segment.c \
			src/expander/utils_expander.c \
			src/expander/free_exp.c \
			src/expander/handle_special_cases.c 

PARSER = src/parser/parser.c \
		src/parser/create_ast_node.c \
		src/parser/divide_ast_comand.c \
		src/parser/free_parser.c \
		src/parser/parser_debug.c \
		src/parser/redirects.c \
		src/parser/utils_parser.c

HEREDOC = src/heredoc/heredoc.c \
			src/heredoc/utils_heredoc.c

MY_SIGNAL = src/signals/signal.c

UTILS = src/utils/utils_general.c \
		src/utils/init_shell.c \
		src/utils/utils_main.c \
		src/utils/shell_debug.c

ERRORS = src/errors/dispatch_errors.c \
		src/errors/input_syntax_error.c \
		src/errors/syntax_fn.c \
		src/errors/execute_fn.c \
		src/errors/builtin_errors.c


SRC = $(LEXER) $(UTILS) $(ERRORS) $(ENV) $(EXPANDER) $(PARSER) $(HEREDOC) $(MY_SIGNAL) $(EXECUTOR) $(BUILT_IN) src/main.c

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

#valgrind: $(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --suppressions=readline.supp --log-file=valgrind.log ./$(NAME)

LOG_DIR := valgrind_logs

valgrind: $(NAME)
	@mkdir -p $(LOG_DIR)
	@VALGRIND_LOG_FILE=$(LOG_DIR)/valgrind_$(shell date +"%Y%m%d_%H%M%S").log; \
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s --suppressions=readline.supp --log-file=$$VALGRIND_LOG_FILE ./$(NAME)

nolog:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re valgrind nolog
