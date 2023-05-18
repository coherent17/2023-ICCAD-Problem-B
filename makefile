# Compiler and linker settings
CC = g++
CFLAGS = -g -Wall -O3

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
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

do1:
	./$(TARGET) Testcase/ProblemB_case1.txt Testcase/ProblemB_case1_result.txt

do2:
	./$(TARGET) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt

do3:
	./$(TARGET) Testcase/ProblemB_case3.txt Testcase/ProblemB_case3_result.txt

do4:
	./$(TARGET) Testcase/ProblemB_case4.txt Testcase/ProblemB_case4_result.txt

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) Testcase/ProblemB_case3.txt Testcase/ProblemB_case3_result.txt

clean:
	rm -rf $(OBJDIR) $(TARGET) *.hgr *.part.2 *.txt *.out *.in log*

.PHONY: all clean
