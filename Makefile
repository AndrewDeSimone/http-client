# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Output executable
TARGET = http-client

# Source files
SRC = src/main.c

# Default target: build the client
all: $(TARGET)

# How to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up the executable
clean:
	del $(TARGET).exe
