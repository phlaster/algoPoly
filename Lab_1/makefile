all: build

build: main.o largest_submatrix.o printers.o random_arrays_gen.o
	g++ main.o largest_submatrix.o printers.o random_arrays_gen.o -o build.out

# # # # #
main.o: main.cpp
	g++ -c main.cpp

largest_submatrix.o: largest_submatrix.cpp
	g++ -c largest_submatrix.cpp

random_arrays_gen.o: random_arrays_gen.cpp
	g++ -c random_arrays_gen.cpp

printers.o: printers.cpp
	g++ -c printers.cpp


##################################################
#------------------- TESTS ----------------------#
##################################################
tests: tests.o largest_submatrix.o printers.o random_arrays_gen.o
	g++ tests.o largest_submatrix.o printers.o random_arrays_gen.o -o tests.out

tests.o: tests.cpp
	g++ -c tests.cpp
##################################################
#------------------ UTILITY ---------------------#
##################################################
clean:
	rm -f *.o *.gch

purge:
	rm -f *.o *.gch *.out
