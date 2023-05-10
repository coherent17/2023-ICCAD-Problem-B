# Compiler and linker settings
CC = g++
CFLAGS = -g -Wall

#Valgrind detect memory leak
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = CADB

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) main.cpp $^ -o $@ -lpthread

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

do1:
	./$(TARGET) Testcase/ProblemB_case1.txt Testcase/ProblemB_case1_result.txt

do2:
	./$(TARGET) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt

clean:
	rm -rf $(OBJDIR) $(TARGET) *.hgr *.part.2 *.txt *.out *.in

.PHONY: all clean
