# Compiler and linker settings
CC = gcc
CFLAGS = -Isrc -Isrc/instructions/load -Isrc/instructions/logic -Isrc/instructions/shift -Isrc/instructions/stack -Isrc/instructions/transfer -Isrc/instructions/arith -Isrc/instructions/inc -Isrc/instructions/ctrl -Wall
LDFLAGS =

# Project settings
EXEC = program
SRC_DIRS := src $(shell find src/instructions -type d)
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)

# Default goal
.DEFAULT_GOAL := run

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling source files
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Running the program
run: $(EXEC)
	./$(EXEC)

# Cleaning up
clean:
	@echo $(OBJS)
	rm -f $(OBJS) $(EXEC) $(EXEC).exe