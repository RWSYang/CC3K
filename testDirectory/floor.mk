# To run this makefile type:
# make -f floor.mk
CXX = g++-5
D_LEVEL ?= 0
CXXFLAGS = -g -std=c++14 -Wall -MMD -DDEBUG_LEVEL=${D_LEVEL}
EXEC = floor
OBJECTS = ../floor.o floorTest.o ../tile.o ../activeTile.o ../emptyTile.o ../horizontalWall.o ../verticalWall.o
OBJECTS += ../door.o ../bridge.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -I.. ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}

rebuild: clean ${EXEC}
