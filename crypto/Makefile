# project name (generate executable with this name)
TARGET   = crypto

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -I. -I/usr/local/opt/openssl@1.1/include -lcrypto

LINKER   = gcc
# linking flags here
LFLAGS   = -L/usr/local/opt/openssl@1.1/lib

# change these to proper directories where each file should be
SRCDIR   = src
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
rm       = rm -f

$(BINDIR)/$(TARGET): $(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BINDIR)/$(TARGET) $(SOURCES)

clean:
	rm -f $(BINDIR)/$(TARGET)
