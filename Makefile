CC = g++
DEBUG = -g
CFLAGS = -g -Wall -Wextra -pthread
SOURCES = main.cpp Clique.cc Graph.cpp VertexColor.cc 
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE = clique

# Target

all : $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) *.o *.a *~
