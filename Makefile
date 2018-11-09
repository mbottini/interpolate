CXX=g++
CC=gcc
CXXFLAGS=--std=c++11 -Wall 
LIBRARIES=-lm -lX11


all: a.out

a.out: main.o interpolate.o
	${CXX} ${CXXFLAGS} main.o interpolate.o -o a.out ${LIBRARIES}

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp ${LIBRARIES}

interpolate.o: interpolate.cpp
	${CXX} ${CXXFLAGS} -c interpolate.cpp

clean:
	rm -f *.o
	rm -f a.out
	rm -f *.xwd
