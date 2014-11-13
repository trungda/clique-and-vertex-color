/* 
Graph: A class holds the information of a graph in form of adjacent list: mList
+ Graph(): Constructor; creates a graph from file for testing purpose
+ Graph(vector<ES>): Constructor; creates a graph from list of ES. There is an edge between two ES instances if 
they are compatible
+ calReversedList(): Creates a reversed graph from the current graph and holds the information of this graph in 
mReversedList. There is an edge between two vertices in the new graph if there is no edge between these two 
vertices in the original graph. This function is used for Vertex Coloring Problem
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define MAX_NUMBER_OF_VERTICES 20000
#define MAX_NUMBER_OF_COLORS 20000
#define BITS 32

typedef pair<int, int> IdDeg;

class Graph {
 private:
  int nVertex;
  vector< vector<int> > mList;
  vector< vector<int> > mComplementList;

 public:
  Graph();
  Graph(vector< vector<int> >);
  ~Graph();
  int getNumVertices();
  bool isConnected(int, int);
  void calComplementList();
  vector< vector<int> > getAdjList();
  vector< vector<int> > getComplementAdjList();
};

bool comp(const IdDeg &, const IdDeg &);

void setBit(unsigned int &x, int i);
void clearBit(unsigned int &x, int i);
unsigned int getBit(unsigned int x, int i);

#endif
