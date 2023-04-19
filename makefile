# Compiler and linker settings
CC = g++
CFLAGS = -g -Wall

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = CADB

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

do:
	./$(TARGET) /Testcase/ProblemB_case1.txt

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
