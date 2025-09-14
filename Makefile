# BIBLE CLI

CC = gcc
CFLAGS = -Wall -g
TARGET = bible-cli

COMMON_DIR = bible_cli

BINARIES_DIR = $(COMMON_DIR)/Binaries
OBJECTS_DIR = $(COMMON_DIR)/Objects
SOURCES_DIR = $(COMMON_DIR)/Sources
HEADERS_DIR = $(COMMON_DIR)/Headers

sources = $(wildcard $(SOURCES_DIR)/*.c)
objects = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(sources))
include_flags = -I$(HEADERS_DIR)

all: $(TARGET)

$(TARGET): $(objects)
	@mkdir -p $(BINARIES_DIR)
	$(CC) $(CFLAGS) $(objects) -o $(BINARIES_DIR)/$@

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) $(include_flags) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS_DIR) $(BINARIES_DIR)
