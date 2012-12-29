#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define MAX_NUMBER_OF_VERTICES 5000
#define MAX_NUMBER_OF_COLORS 5000
#define BITS 32

void setBit(unsigned int &x, int i);
void clearBit(unsigned int &x, int i);
unsigned int getBit(unsigned int x, int i);

class Graph {
 private:
  int nVertex;
  vector< vector<int> > mList;
  vector< vector<int> > mComplementList;

 public:
  Graph();
  Graph(vector< vector<int> >);
  int getNumVertices();
  bool isConnected(int, int);
  void calComplementList();
  vector< vector<int> > getAdjList();
  vector< vector<int> > getComplementAdjList();
  Graph getComplementGraph();  
};

class Clique {
 private:
  //VARIABLES DECLARATION---------------------------------------------------------------------------
  int n;
  // Adjacency matrix
  unsigned int ll[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES / BITS + 1];
  vector< pair<int, int> > deg;

  //set of current clique
  unsigned int Q[MAX_NUMBER_OF_VERTICES / BITS + 1];

  //set of current maximum clique 
  unsigned int Qmax[MAX_NUMBER_OF_VERTICES / BITS + 1];
  
  bool Colored[MAX_NUMBER_OF_VERTICES];
  
  unsigned int c[MAX_NUMBER_OF_VERTICES];

  unsigned int MaxCliqueSize;

  unsigned int CurSet[MAX_NUMBER_OF_VERTICES / BITS + 1];

  vector<int> MaxClique;
  vector< vector<int> > CliqueList;
  //END OF VARIALBLES DECLARATION--------------------------------------------------------------------

  //SUPPORTING FUNCTIONS DECLARATION-----------------------------------------------------------------
  bool isConnected(int, int);
  void intersect(unsigned int * lli, unsigned int * R, unsigned int *Rp);
  int CountOneBit(int start, unsigned int *x);
  
  int VertexColor(unsigned int *, unsigned int *, unsigned int &);
  void EXPAND(unsigned int *, unsigned int); 
  void BASICEXPAND(unsigned int *, unsigned int);
  int MaxCliqueFinding();
  void CliquePartition();

  //END OF SUPPORTING FUNCTIONS DECLARATION-------------------------------------------------------------------

public:
  Clique();
  Clique(Graph);
  int getMaximumCliqueSize();
  vector<int> getMaximumCliqueList();
  int getCliquePartitionNum();
  vector< vector<int> > getCliquePartitionList();
  void displayResult();
};

class VertexColor {
 private:
  int n;
  unsigned int ll[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES / BITS + 1];
  vector< pair<int, int> > deg;
  vector< vector<int> > ColorList;
  
  bool IsConnected(int, int);
  
  void HeuristicColoring();
  void Coloring();
  bool isConnected(int, int);
  
 public:
  VertexColor();
  VertexColor(Graph);
  vector< vector<int> > getColorList();
  void displayResult();
};
#endif
