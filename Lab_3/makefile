all: build

build: main.o functions.o TreeNode.o BTree.o
	g++ main.o functions.o TreeNode.o BTree.o -o build.out

# # # # #
main.o: main.cpp
	g++ -c main.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

TreeNode.o: TreeNode.cpp
	g++ -c TreeNode.cpp

BTree.o: BTree.cpp
	g++ -c BTree.cpp


##################################################
#------------------ UTILITY ---------------------#
##################################################
clean:
	rm -f *.o *.gch

purge:
	rm -f *.o *.gch *.out; rm -rf build/