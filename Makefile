all:
	g++ -std=c++17 -Wall -Wextra genealogy.cpp -o genealogy

clean:
	rm genealogy