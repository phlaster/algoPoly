CC=clang++
LIBFLAGS=-lGL -lglut
CFLAGS_DBG=-g3 -O0 -Wall -Wextra -Wconversion -Wimplicit --std=c++17
CFLAGS=-O3 --std=c++17
SOURCE_DIR=.
OBJECT_DIR=objects
DBG_NAME=debug
BIN_NAME=build

SOURCES=main CodeMap Huffman_ENcode Huffman_DEcode FreqTable Huffman_IO HuffmanTree Node

DBG_OBJECTS=$(addprefix $(OBJECT_DIR)/,$(addsuffix _DBG.o,$(SOURCES)))
OBJECTS=$(addprefix $(OBJECT_DIR)/,$(addsuffix .o,$(SOURCES)))


all: build
$(BIN_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@.out $(LIBFLAGS)
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJECT_DIR):
	mkdir -p $@


debug:
$(DBG_NAME): $(DBG_OBJECTS)
	$(CC) $(CFLAGS_DBG) $^ -o $@.out $(LIBFLAGS)
$(OBJECT_DIR)/%_DBG.o: $(SOURCE_DIR)/%.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS_DBG) -c $< -o $@


clean:
	rm -f $(OBJECT_DIR)/*.o


purge:
	rm -rf $(OBJECT_DIR)/; rm *.out