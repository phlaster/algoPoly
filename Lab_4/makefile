CC=g++
CFLAGS= -g
SOURCE_DIR=.
OBJECT_DIR=obj

# List all source code (.cpp) files here (without .cpp extension)
SOURCES=main CodeMap Huffman_ENcode Huffman_DEcode Printer FreqTable Huffman_IO HuffmanTree Node

# Generate list of corresponding object file names from sources listed above 
OBJECTS=$(addprefix $(OBJECT_DIR)/,$(addsuffix .o,$(SOURCES)))

all: MyProject

MyProject: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@.out

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT_DIR):
	mkdir -p $@


clean:
	rm -f $(OBJECT_DIR)/*

purge:
	rm -rf $(OBJECT_DIR)/; rm MyProject.out