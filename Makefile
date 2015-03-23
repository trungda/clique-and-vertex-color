CC = g++
DEBUG = -g
CFLAGS = -Wall -Wextra -I.

BIN = bin
BUILD = build
SRC = src

HEADER = $(SRC)/Graph.h $(SRC)/Clique.h $(SRC)/VertexColor.h
SOURCE = $(SRC)/Graph.cpp $(SRC)/Clique.cpp $(SRC)/VertexColor.cpp
OBJECT = $(BUILD)/Graph.o $(BUILD)/Clique.o $(BUILD)/VertexColor.o

TEST = test

TEST_SOURCE = $(TEST)/main.cpp
TEST_OBJECT = $(BUILD)/main.o

# Target
$(BIN)/test: $(TEST_OBJECT) $(OBJECT)
	/bin/mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJECT) $(OBJECT)

$(TEST_OBJECT): $(TEST_SOURCE) $(HEADER)
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/Graph.o: $(SRC)/Graph.cpp
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/Clique.o: $(SRC)/Clique.cpp $(SRC)/Graph.h
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/VertexColor.o: $(SRC)/VertexColor.cpp $(SRC)/Graph.h $(SRC)/Clique.h
	/bin/mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	/bin/rm -rf $(TEST)/*~ $(SRC)/*~ 
	/bin/rm -rf $(BUILD)
	/bin/rm -rf $(BIN)
