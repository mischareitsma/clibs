# Version info

VERSION = 0.0.1

# Target executables etc.

TARGET = ioutils
TARGET_LIB_NAME = lib$(TARGET).so
TARGET_LIB = $(TARGET_LIB_NAME).$(VERSION)

TARGET_TEST = test_$(TARGET)

# Directories:

SRC_DIR  = src
TEST_DIR = test
LIB_DIR  = lib
BIN_DIR  = bin
OBJ_DIR  = obj

INCUDE_INSTALL_DIR  = /usr/local/include
LIBRARY_INSTALL_DIR = /usr/local/lib

# Binaries
CC = gcc

# Compiler and Linker options
INCLUDE_DIRS = -I$(SRC_DIR) -I$(TEST_DIR)
LIBRARY_DIRS = 
CFLAGS = -Wall -Werror
LFLAGS = -fPIC -shared

SOURCES       := $(wildcard $(SRC_DIR)/*.c)
INCLUDES      := $(wildcard $(SRC_DIR)/*.h)
TEST_SOURCES  := $(wildcard $(TEST_DIR)/*.c)

all: $(LIB_DIR)/$(TARGET_LIB)

so: $(LIB_DIR)/$(TARGET_LIB)

$(LIB_DIR)/$(TARGET_LIB): $(SOURCES) $(INCLUDES) $(LIB_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SOURCES) $(LFLAGS) -o $@

install: $(LIB_DIR)/$(TARGET_LIB) $(INCLUDES)
	cp $(INCLUDES) $(INCUDE_INSTALL_DIR)
	cp $(LIB_DIR)/$(TARGET_LIB) $(LIBRARY_INSTALL_DIR)
	ln -sf $(LIBRARY_INSTALL_DIR)/$(TARGET_LIB) $(LIBRARY_INSTALL_DIR)/$(TARGET_LIB_NAME)

$(BIN_DIR)/$(TARGET_TEST): $(SOURCES) $(TEST_SOURCES) $(INCLUDES) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SOURCES) $(TEST_SOURCES) -o $(BIN_DIR)/$(TARGET_TEST)

$(TEST_SOURCES): $(INCLUDES) $(SOURCES)

test: $(BIN_DIR)/$(TARGET_TEST)
	$(BIN_DIR)/$(TARGET_TEST)

# Recipies for directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)