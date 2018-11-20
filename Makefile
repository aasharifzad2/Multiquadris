EXEC = a4q1
SUITE = suiteq1.txt
SUBMIT = Makefile *.cc *.h
CORRECT = a4q1-exec

SHELL = bash
EXEC = biquadris
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
CCFILES = $(shell for file in ${SUBMIT}; do if [[ $$file == *.cc ]]; then echo $${file}; fi done)
OBJECTS = ${CCFILES:.cc=.o}
DEPENDS = ${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean test-tests test-imp prodout submit-tests submit-imp touch-all

clean:
	rm ${OBJECTS} ${DEPENDS}
