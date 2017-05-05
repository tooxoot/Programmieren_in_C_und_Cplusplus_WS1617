all:
	g++ -std=c++11 -o algo algo.cpp

test:
	./algo countodd 1 2 3 4 5 6 7 8 9 # == 5
	./algo hasnegative 1 2 3 4 5 6 7 8 9 # == NO
	./algo hasnegative 1 -2 3 4 5 6 7 8 9 # == YES
	./algo inc 1 2 3 4 5 6 7 8 9
	./algo sum 1 2 3 4 5 6 7 8 9
	./algo deleteodd 1 2 3 4 5 6 7 8 9

clean:
	rm  algo
