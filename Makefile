# Compiler and flags
CC = g++
CFLAGS = -Wall -g

# Source files
SRCS = MarkovChain.cpp main.cpp

# Output executable
TARGET = $(BUILD_DIR)/MarkovChain.out

# Build directory
BUILD_DIR = build

# Default target: build the executable
all: $(BUILD_DIR) $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean target: remove the build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean