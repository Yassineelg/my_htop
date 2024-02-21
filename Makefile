# Compiler and linker configuration
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lncurses

# Directories for source and object files
SRC_DIR = src
OBJ_DIR = obj

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
EXEC = my_htop

# Docker configuration
DOCKER_IMAGE_NAME = my_htop_image
DOCKER_CONTAINER_NAME = my_htop_container

# Phony targets
.PHONY: all clean fclean run re valgrind dev-up docker-build docker-run docker-stop docker-remove

# Default target to build the executable
all: $(EXEC)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Target to build the executable
$(EXEC): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "\033[1;32mCompilation Completed Successfully!\033[0m"

# Target to run the executable
run: $(EXEC)
	@./$(EXEC)

# Target to clean up objects
clean:
	@echo "\033[1;36mCleaning up objects...\033[0m"
	@rm -f $(OBJ_DIR)/*.o
	@echo "\033[1;36mClean up completed!\033[0m"

# Target to clean up objects and the executable
fclean: clean
	@echo "\033[1;36mCleaning up executable...\033[0m"
	@rm -f $(EXEC)
	@echo "\033[1;36mFull clean up completed!\033[0m"

# Target to clean and rebuild the project
re: fclean all

# Target to analyze the program with Valgrind
valgrind: $(EXEC)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

dev-up: docker-build docker-run

# Target to build the Docker image
docker-build:
	@docker build -t $(DOCKER_IMAGE_NAME) .

# Target to run the Docker container
docker-run:
	@docker run --name $(DOCKER_CONTAINER_NAME) -it --rm $(DOCKER_IMAGE_NAME)

# Target to stop the Docker container
docker-stop:
	@docker stop $(DOCKER_CONTAINER_NAME)

# Target to remove the Docker image and container forcefully
docker-remove:
	@docker rmi -f $(DOCKER_IMAGE_NAME)
	@docker rm -f $(DOCKER_CONTAINER_NAME)