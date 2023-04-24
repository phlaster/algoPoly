all: build

build: main.o Class_RBTree.o Methods_RBTree.o
	g++ main.o Class_RBTree.o Methods_RBTree.o -o build.out

# # # # #
main.o: main.cpp
	g++ -c main.cpp

Class_RBTree.o: Class_RBTree.cpp
	g++ -c Class_RBTree.cpp

Methods_RBTree.o: Methods_RBTree.cpp
	g++ -c Methods_RBTree.cpp


##################################################
#------------------ UTILITY ---------------------#
##################################################
clean:
	rm -f *.o *.gch

purge:
	rm -f *.o *.gch *.out; rm -rf build/
