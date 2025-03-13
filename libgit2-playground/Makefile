PROGNAME := lg2pg
MAJOR := 0
MINOR := 1
PATCH := 0
VERSION := $(MAJOR).$(MINOR).$(PATCH)

CC := gcc
CFLAGS := -c -Wall $(shell pkg-config --cflags libgit2)
LFLAGS := $(shell pkg-config --libs libgit2)

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJECTS := $(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.c,%.o,$(SOURCES))))

.PHONY: all version debug

all: $(BIN_DIR)/$(PROGNAME)

debug:
	@echo "SOURCER: $(SOURCES)"
	@echo "HEADERS: $(HEADERS)"
	@echo "OBJECTS: $(OBJECTS)"

$(BIN_DIR)/$(PROGNAME): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

version:
	@echo $(VERSION)-$$(git rev-parse --short HEAD)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)