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
SRC = main.c \
	signal.c

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:%.c=%.o))

all: $(NAME)

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