EXEC = a4q1
SUITE = suiteq1.txt
SUBMIT = Makefile *.cc *.h
CORRECT = a4q1-exec

SHELL = bash
EXEC = biquadris
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DDEBUG
CCFILES = $(shell find . -type f -name '*.cc')
OBJECTS = ${CCFILES:.cc=.o}
DEPENDS = ${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean 

clean:
	rm ${OBJECTS} ${DEPENDS}
