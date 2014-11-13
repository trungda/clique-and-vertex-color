/*
Clique: Partition the graph into subsets of vertices. Each set forms a clique.
*/

#ifndef CLIQUE_H
#define CLIQUE_H

#include "Graph.h"

class Clique {
 private:
  //VARIABLES DECLARATION---------------------------------------------------------------------------
  int n;
  // Adjacency matrix
  unsigned int ll[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES / BITS + 1];
  vector< IdDeg > deg;

  //set of current clique
  unsigned int Q[MAX_NUMBER_OF_VERTICES / BITS + 1];

  //set of current maximum clique 
  unsigned int Qmax[MAX_NUMBER_OF_VERTICES / BITS + 1];
  
  bool Colored[MAX_NUMBER_OF_VERTICES];
  
  unsigned int c[MAX_NUMBER_OF_VERTICES];

  unsigned int maxCliqueSize;

  vector<int> maxClique;
  vector< vector<int> > cliqueList;
  //END OF VARIALBLES DECLARATION--------------------------------------------------------------------

  //SUPPORTING FUNCTIONS DECLARATION-----------------------------------------------------------------
  bool isConnected(int, int);
  void intersect(unsigned int * lli, unsigned int * R, unsigned int *Rp);
  int countOneBit(int start, unsigned int *x);
  
  int vertexColor(unsigned int *, unsigned int *, unsigned int &);
  void expand(unsigned int *, unsigned int); 
  void basicExpand(unsigned int *, unsigned int);
  int maxCliqueFinding();
  void cliquePartition();

  //END OF SUPPORTING FUNCTIONS DECLARATION-------------------------------------------------------------------

public:
  Clique();
  Clique(Graph);
  ~Clique();
  vector<int> getMaximumCliqueList();
  vector< vector<int> > getCliquePartitionList();
};

#endif
