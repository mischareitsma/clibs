# Target executable and library names
TARGET        = rsacrypto
TARGET_LIB    = librsacrypto.so
TARGET_XC_LIB = libgtmrsacrypto.so

# Directories
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
OBJ_DIR = obj

GTM_SRC_DIR = gtmsrc
GTM_OBJ_DIR = gtmobj

# Compiler info and inputs
CC = gcc

INC_PATH = -I./src -I/usr/include/openssl -I/usr/local/opt/openssl@1.1/include
LIB_PATH = -L./lib -L/usr/local/opt/openssl@1.1/lib

CFLAGS = -Wall -Werror
LFLAGS = -lcrypto

# Add GT.M related libraries if gtm_dist is defined.
ifdef gtm_dist
GTM_ENABLE = 1
GTM_INC_PATH = $(INC_PATH) -I$$gtm_dist
GTM_LIB_PATH = $(LIB_PATH) -L$$gtm_dist
GTM_LFLAGS = $(LFLAGS) -lgtmshr
endif

# Sources, headers and objects
SOURCES  := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := $(wildcard $(SRC_DIR)/*.h)
OBJECTS  := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

GTM_SOURCES  := $(wildcard $(GTM_SRC_DIR)/*.c)
GTM_INCLUDES := $(wildcard $(GTM_SRC_DIR)/*.h)
GTM_OBJECTS  := $(patsubst $(GTM_SRC_DIR)/%.c, $(GTM_OBJ_DIR)/%.o, $(GTM_SOURCES))

# Default will be creating an executable using the orignal C sources
$(BIN_DIR)/$(TARGET): $(SOURCES) $(INCLUDES) $(BIN_DIR) $(LIB_DIR)
	$(CC) $(LIB_PATH) $(INC_PATH) $(SOURCES) -o $@ $(LFLAGS)

# Creation of the object files for the pure C components
$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(INC_PATH) $(CFLAGS) -c -fPIC $< $(LIB_PATH) $(LFLAGS) -o $@

# Creation of the object files for the GT.M C components
$(GTM_OBJECTS): $(GTM_OBJ_DIR)/%.o : $(GTM_SRC_DIR)/%.c $(GTM_OBJ_DIR)
	$(CC) $(GTM_INC_PATH) $(CFLAGS) -c -fPIC $< $(GTM_LIB_PATH) $(GTM_LFLAGS) -o $@

# Create the so for the pure C rsacrypo lib
clib: $(OBJ_DIR)/rsacrypto.o $(LIB_DIR)
	$(CC) $(CFLAGS) -shared $< -o $(LIB_DIR)/$(TARGET_LIB) $(LIB_PATH) $(LFLAGS)

# Create the so for the GT.M external call lib
gtmlib: $(OBJ_DIR)/rsacrypto.o $(GTM_OBJ_DIR)/gtmrsacrypto.o $(LIB_DIR)
	$(CC) $(CFLAGS) -shared $(filter-out $(LIB_DIR), $^) -o $(LIB_DIR)/$(TARGET_XC_LIB) $(GTM_LIB_PATH) $(GTM_LFLAGS)

# Rules or directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(GTM_OBJ_DIR):
	mkdir -p $(GTM_OBJ_DIR)

# Make the binary, librsacrypto and libgtmrsacrypto
all: $(BIN_DIR)/$(TARGET) clib gtmlib

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR) $(GTM_OBJ_DIR)
