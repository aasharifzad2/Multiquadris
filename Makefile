SHELL = bash
EXEC = biquadris
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DDEBUG -DRICH
CCFILES = $(shell find ./proj -type f -name '*.cc')
OBJECTS = ${CCFILES:.cc=.o}
DEPENDS = ${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean 

clean:
	rm ${OBJECTS} ${DEPENDS}
