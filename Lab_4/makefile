CC=g++
CFLAGS=
SOURCE_DIR=.
OBJECT_DIR=objects

SOURCES=main CodeMap Huffman_ENcode Huffman_DEcode FreqTable Huffman_IO HuffmanTree Node

OBJECTS=$(addprefix $(OBJECT_DIR)/,$(addsuffix .o,$(SOURCES)))

all: build

build: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@.out

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJECT_DIR)/*

purge:
	rm -rf $(OBJECT_DIR)/; rm build.out output.bin