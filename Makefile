CXXFLAGS=-std=c++11

main: main.o hash_table.o hash_item.o gps.o
	g++ -o main main.o hash_table.o hash_item.o gps.o

# main.o: main.cpp _hash_item.h hash_table.cpp
# 	g++ $(CXXFLAGS) -c main.cpp

test: test.o subway_route.o
	g++ -o test test.o subway_route.o

test.o: test.cpp subway_route.h doctest.h
	g++ -std=c++14 -c test.cpp

subway_route.o: subway_route.cpp subway_route.h
	g++ $(CXXFLAGS) -c subway_route.cpp

hash_item.o: hash_item.cpp _hash_item.h
	g++ $(CXXFLAGS) -c hash_item.cpp

hash_table.o: hash_table.cpp hash_table.h
	g++ $(CXXFLAGS) -c hash_table.cpp

gps.o: gps.cpp gps.h
	g++ $(CXXFLAGS) -c gps.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g -fsanitize=address,undefined

debug: main

clean:
	rm -f main test hash_item.o hash_table.o gps.o test.o subway_route.o

run:
	./main