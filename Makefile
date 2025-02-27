#Copyright Peiu Andreea 314CA - Tema 1
# Compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Define source files (all .c files in the directory)
SRCS = $(wildcard *.c)

# Build target
build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o sfl

# Run target
run: build
	./sfl

# Pack target
pack:
	zip -FSr 314CA_PeiuAndreea_Tema1.zip README Makefile *.c *.h

# Clean target
clean:
	rm -f $(OBJS) sfl

.PHONY: build run pack clean
