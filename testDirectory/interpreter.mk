CXX = g++-5
D_LEVEL ?= 0
CXXFLAGS = -g -std=c++14 -Wall -MMD -DDEBUG_LEVEL=${D_LEVEL}
EXEC = interpreter
OBJECTS = ../board.o ../interpreter.o interpreterTest.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}

rebuild: clean ${EXEC}
