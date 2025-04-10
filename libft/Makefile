NAME = libft.a
SRC_DIR = src
BUILD_DIR = build
LIBFT_BUILD_DIR = $(BUILD_DIR)/libft
FT_PRINTF_DIR = $(BUILD_DIR)/ft_printf
INCLUDE_DIR = include

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_SRC =	$(SRC_DIR)/libft/ft_isalpha.c \
		$(SRC_DIR)/libft/ft_isdigit.c \
		$(SRC_DIR)/libft/ft_isalnum.c \
		$(SRC_DIR)/libft/ft_isascii.c \
		$(SRC_DIR)/libft/ft_isprint.c \
		$(SRC_DIR)/libft/ft_strlen.c \
		$(SRC_DIR)/libft/ft_memset.c \
		$(SRC_DIR)/libft/ft_bzero.c \
		$(SRC_DIR)/libft/ft_memcpy.c \
		$(SRC_DIR)/libft/ft_memmove.c \
		$(SRC_DIR)/libft/ft_strlcpy.c \
		$(SRC_DIR)/libft/ft_strlcat.c \
		$(SRC_DIR)/libft/ft_toupper.c \
		$(SRC_DIR)/libft/ft_tolower.c \
		$(SRC_DIR)/libft/ft_strchr.c \
		$(SRC_DIR)/libft/ft_strrchr.c \
		$(SRC_DIR)/libft/ft_strncmp.c \
		$(SRC_DIR)/libft/ft_memchr.c \
		$(SRC_DIR)/libft/ft_memcmp.c \
		$(SRC_DIR)/libft/ft_strnstr.c \
		$(SRC_DIR)/libft/ft_atoi.c \
		$(SRC_DIR)/libft/ft_calloc.c \
		$(SRC_DIR)/libft/ft_strdup.c \
		$(SRC_DIR)/libft/ft_substr.c \
		$(SRC_DIR)/libft/ft_strjoin.c \
		$(SRC_DIR)/libft/ft_strtrim.c \
		$(SRC_DIR)/libft/ft_split.c \
		$(SRC_DIR)/libft/ft_itoa.c \
		$(SRC_DIR)/libft/ft_strmapi.c \
		$(SRC_DIR)/libft/ft_striteri.c \
		$(SRC_DIR)/libft/ft_putchar_fd.c \
		$(SRC_DIR)/libft/ft_putstr_fd.c \
		$(SRC_DIR)/libft/ft_putendl_fd.c \
		$(SRC_DIR)/libft/ft_putnbr_fd.c 

FT_PRINTF_SRC = $(SRC_DIR)/ft_printf/ft_printf.c \
		$(SRC_DIR)/ft_printf/ft_print_c.c \
		$(SRC_DIR)/ft_printf/ft_print_str.c \
		$(SRC_DIR)/ft_printf/ft_print_id.c \
		$(SRC_DIR)/ft_printf/ft_print_u.c \
		$(SRC_DIR)/ft_printf/ft_print_x.c \
		$(SRC_DIR)/ft_printf/ft_print_p.c

LIBFT_OBJ = $(LIBFT_SRC:$(SRC_DIR)/libft/%.c=$(LIBFT_BUILD_DIR)/%.o)
FT_PRINTF_OBJ = $(FT_PRINTF_SRC:$(SRC_DIR)/ft_printf/%.c=$(FT_PRINTF_DIR)/%.o)
OBJ = $(LIBFT_OBJ) $(FT_PRINTF_OBJ)

CFLAGS += -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME): $(OBJ) obj_done
	@echo "Creating library $(NAME).. "
	@ar -rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created successfully."

$(LIBFT_BUILD_DIR)/%.o: $(SRC_DIR)/libft/%.c | $(LIBFT_BUILD_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF_DIR)/%.o: $(SRC_DIR)/ft_printf/%.c | $(FT_PRINTF_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_BUILD_DIR):
	@mkdir -p $(LIBFT_BUILD_DIR)

$(FT_PRINTF_DIR):
	@mkdir -p $(FT_PRINTF_DIR)

obj_done:
	@echo "All object files compiled successfully."

clean:
	@echo "Cleaning object files in $(BUILD_DIR).."
	@rm -rf $(BUILD_DIR)
	@echo "Object files in $(BUILD_DIR) cleaned successfully."

fclean: clean
	@echo "Removing library $(NAME).."
	@rm -f $(NAME)
	@echo "Library $(NAME) removed successfully."

re: fclean all

.PHONY: all clean fclean re obj_done