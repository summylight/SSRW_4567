.PHONY: SSRW7 SSRW7.o
SSRW7: SSRW7.o SFMT.o
		g++ -std=c++11  -pthread -o SSRW7 SFMT.o SSRW7.o -ligraph
SSRW7.o: sfmt/SFMT.h
		g++ -std=c++11  -pthread -c SSRW7.cpp
SFMT.o: sfmt/SFMT.h
		gcc -c sfmt/SFMT.c
clean:
		-rm -f *.o
