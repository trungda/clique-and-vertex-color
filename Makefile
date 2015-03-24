CC = g++
DEBUG = -g
CFLAGS = -Wall -Wextra -I.

AR = ar

# User directory
# Modify the following path according to where you put the project
USER_DIR = ~/Dropbox/trungda/research/work/clique-and-vertex-color

BIN = bin
BUILD = build
SRC = src
TARGET = target

FINAL = libngclique.a

HEADER = $(SRC)/Graph.h $(SRC)/Clique.h $(SRC)/VertexColor.h
SOURCE = $(SRC)/Graph.cpp $(SRC)/Clique.cpp $(SRC)/VertexColor.cpp
OBJECT = $(BUILD)/Graph.o $(BUILD)/Clique.o $(BUILD)/VertexColor.o

TEST = test

TEST_SOURCE = $(TEST)/test.cpp
TEST_OBJECT = $(BUILD)/test.o

all: $(OBJECT)
	/bin/mkdir -p $(TARGET)
	$(AR) rcs $(TARGET)/$(FINAL) $(OBJECT)

$(BUILD)/Graph.o: $(SRC)/Graph.cpp
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/Clique.o: $(SRC)/Clique.cpp $(SRC)/Graph.h
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/VertexColor.o: $(SRC)/VertexColor.cpp $(SRC)/Graph.h $(SRC)/Clique.h
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

# Build Test

test: $(TEST_OBJECT) $(OBJECT)
	/bin/mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/test $(TEST_OBJECT) $(OBJECT)

$(TEST_OBJECT): $(TEST_SOURCE) $(HEADER)
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	/bin/rm -rf $(TEST)/*~ $(SRC)/*~ 
	/bin/rm -rf $(BUILD)
	/bin/rm -rf $(BIN)
	/bin/rm -rf $(TARGET)
