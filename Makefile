CC = g++
CFLAGS = -std=c++11 -O2

my_tool: main.cpp
    $(CC) $(CFLAGS) -o $@ $^