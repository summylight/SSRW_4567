RW: RW.o SFMT.o
	g++ -std=c++11  -pthread -o RW SFMT.o RW.o 
	
RW.o: sfmt/SFMT.h 
	g++ -std=c++11  -pthread -c RW.cpp

SFMT.o: sfmt/SFMT.h
	gcc  -c sfmt/SFMT.c

clean:
	-rm *.o
