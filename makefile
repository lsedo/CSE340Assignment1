all: test1

test1: test1.o program1.o Grammar.o
	g++ -o test1 test1.o program1.o Grammar.o

test1.o: test1.cpp
	g++ -c test1.cpp

program1.o: program1.cpp
	g++ -c program1.cpp

Grammar.o: Grammar.cpp
	g++ -c Grammar.cpp

clean:
	rm -f test1 *.o

run: test1
	./test1