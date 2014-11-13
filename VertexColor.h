/*
VertexColor: Solve the same problem as CliqueCover but using a different approach
*/

#ifndef VERTEX_COLOR_H
#define VErTEX_COLOR_H

#include "Clique.h"
#include "Graph.h"

class VertexColor {
 private:
  int n;

  int curUsedColor;
  int bestColorNum; // best number of used colors up to now

  unsigned int ll[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES / BITS + 1];
  vector< IdDeg > deg;

  int color[MAX_NUMBER_OF_VERTICES];
  int curColor[MAX_NUMBER_OF_VERTICES];
  
  int DSATUR[MAX_NUMBER_OF_VERTICES]; // degree of saturation list

  bool isConnected(int, int);
  
  void heuristicColoring();

  bool isPossible(int, int);
  void update(int, int);
  void bbColoring(int, int); // branch and bound coloring
  void coloring();
  
 public:  
  VertexColor();
  VertexColor(Graph);
  ~VertexColor();
  vector< vector<int> > getColorList();
};

#endif
