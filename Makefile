SHELL = bash
EXEC = biquadris
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -DDEBUG
CCFILES = $(shell find ./proj -type f -name '*.cc')
OBJECTS = ${CCFILES:.cc=.o}
DEPENDS = ${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11

-include ${DEPENDS}

.PHONY: clean 

clean:
	rm ${OBJECTS} ${DEPENDS}
