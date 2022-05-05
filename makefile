CXX = g++
CFLAGS = -g
main: main.cpp allocator.h
	$(CXX) $^ -o $@


