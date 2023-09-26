# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = srcs
INC_DIR = includes
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Executable name
NAME = philo

# Colors for output
Y = "\033[33m"
G = "\033[32m"
X = "\033[0m"

# Targets
all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(Y)Linking [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo Removing [$(NAME)]...
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
