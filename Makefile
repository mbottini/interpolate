CXX=g++
CC=gcc
CXXFLAGS=--std=c++11 -Wall -Werror

all: main.o interpolate.o
	${CXX} ${CXXFLAGS} main.o interpolate.o -o a.out

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

interpolate.o: interpolate.cpp
	${CXX} ${CXXFLAGS} -c interpolate.cpp
