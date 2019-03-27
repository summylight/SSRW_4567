.PHONY:SSRW5 SSRW5.o
SSRW5: SSRW5.o SFMT.o
	g++ -std=c++11  -pthread -o SSRW5 SFMT.o SSRW5.o 
	
SSRW5.o: sfmt/SFMT.h 
	g++ -std=c++11  -pthread -c SSRW5.cpp

SFMT.o: sfmt/SFMT.h
	gcc  -c sfmt/SFMT.c

clean:
	-rm *.o
