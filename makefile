CXX = g++
CFLAGS = -g
main: main.cpp allocator.h vector.h
	$(CXX) $^ -o $@


