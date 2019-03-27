.PHONY: SSRW6 SSRW6.o
SSRW6: SSRW6.o SFMT.o
		g++ -std=c++11  -pthread -o SSRW6 SFMT.o SSRW6.o -ligraph
SSRW6.o: sfmt/SFMT.h
		g++ -std=c++11  -pthread -c SSRW6.cpp
SFMT.o: sfmt/SFMT.h
		gcc -c sfmt/SFMT.c
clean:
		-rm  *.o
