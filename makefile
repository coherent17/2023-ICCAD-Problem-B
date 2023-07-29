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

# Evaluator
EVALUATOR = Evaluator/ProblemB_evaluator_20230418

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

getCase:
	rm -rf Testcase
	mkdir -p Testcase
	wget -P Testcase http://iccad-contest.org/Document/Problems/Testcase/ProblemB_case1_0522.txt
	wget -P Testcase http://iccad-contest.org/Document/Problems/Testcase/ProblemB_case2.txt
	wget -P Testcase http://iccad-contest.org/Document/Problems/Testcase/ProblemB_case3_20230720.txt
	wget -P Testcase http://iccad-contest.org/Document/Problems/Testcase/ProblemB_case4_20230720.txt

.PHONY: getCase

do1:
	./$(TARGET) Testcase/ProblemB_case1.txt Testcase/ProblemB_case1_result.txt

do2:
	./$(TARGET) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt

do3:
	./$(TARGET) Testcase/ProblemB_case3.txt Testcase/ProblemB_case3_result.txt

do4:
	./$(TARGET) Testcase/ProblemB_case4.txt Testcase/ProblemB_case4_result.txt

test1:
	./$(EVALUATOR) Testcase/ProblemB_case1.txt Testcase/ProblemB_case1_result.txt 

test2:
	./$(EVALUATOR) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt 

test3:
	./$(EVALUATOR) Testcase/ProblemB_case3.txt Testcase/ProblemB_case3_result.txt 

test4:
	./$(EVALUATOR) Testcase/ProblemB_case4.txt Testcase/ProblemB_case4_result.txt 

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) Testcase/ProblemB_case2.txt Testcase/ProblemB_case2_result.txt > ckeck.log

clean:
	rm -rf $(OBJDIR) $(TARGET) *.hgr *.part.2 *.txt *.out *.in log* placement/ *.pl *.plt placementT/ Testcase/*result*

.PHONY: all clean