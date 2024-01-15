
# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Libraries
LIBS = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL

# Directories
OBJDIR = lib
SRCDIR = src
MATHDIR = $(OBJDIR)/math
UTILDIR = $(OBJDIR)/util
MAZEDIR = $(OBJDIR)/maze
LIGHTDIR = $(OBJDIR)/light

# Object files
OBJS = $(UTILDIR)/initShader.o $(UTILDIR)/inputs.o $(UTILDIR)/reader.o  $(MATHDIR)/mat4.o  $(MATHDIR)/vec4.o $(UTILDIR)/view.o  $(MAZEDIR)/maze.o  $(LIGHTDIR)/light.o $(UTILDIR)/util.o

# Executable
TARGET = build/app

# Source files
SRCS = $(SRCDIR)/main.c 

# Rules
all: $(TARGET)

$(TARGET): $(OBJS) $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(OBJS) $(CFLAGS) $(LIBS)

$(MAZEDIR)/%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIGHT)/%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(MATHDIR)/%.o: $(MATHDIR)/%.c $(MATHDIR)/%.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
