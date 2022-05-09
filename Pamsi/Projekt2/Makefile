#
# Opcje dla kompilacji naszego programu
#

CPPFLAGS= -c -g -Iinc -Wall -pedantic -std=c++17

__start__: projekt2
		./projekt2

projekt2: obj/main.o
		g++ -Wall -pedantic -o projekt2 obj/main.o

obj/main.o: src/main.cpp inc/adjacency_matrix.hh inc/bf_algorithm.hh inc/adjacency_list.hh inc/libraries.hh \
			inc/efficiency_test.hh
		g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

clean:
		rm -f obj/*.o projekt2