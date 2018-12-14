COMPILER=g++
FLAGS=-Wall -pedantic

all:
	$(COMPILER) $(FLAGS) main.cpp -o main && $(COMPILER) $(FLAGS) tests.cpp -o tests

main:
	$(COMPILER) $(FLAGS) main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) tests.cpp -o tests

clean:
	rm main tests