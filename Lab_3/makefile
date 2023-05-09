all: build

build: main.o 
	g++ main.o -o build.out

# # # # #
main.o: main.cpp
	g++ -c main.cpp


##################################################
#------------------ UTILITY ---------------------#
##################################################
clean:
	rm -f *.o *.gch

purge:
	rm -f *.o *.gch *.out; rm -rf build/