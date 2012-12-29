#include "Graph.h"

#define BITS 32

/* 
This file contains three classes:
1. Graph: A class holds the information of a graph in form of adjacent list: mList
+ Graph(): Constructor; creates a graph from file for testing purpose
+ Graph(vector<ES>): Constructor; creates a graph from list of ES. There is an edge between two ES instances if 
they are compatible
+ calReversedList(): Creates a reversed graph from the current graph and holds the information of this graph in 
mReversedList. There is an edge between two vertices in the new graph if there is no edge between these two 
vertices in the original graph. This function is used for Vertex Coloring Problem

2. CliqueCover: Split the graph into subsets of vertices. Each set forms a clique.
+ CliqueCover(Graph graph): Constructor; Creates an instance of CliqueCover from a graph
+ vector< vector<int> > getCliqueCoverList(): Returns list of each sets

3. VertexColor: Solve the same problem as above but using a different approach
+ VertexColor(Graph graph): Constructor; Creates an instance of VertexColor from a graph
+ vector< vector<int> > getColorList(): Returns the list of colors. Each list contains vertices with the same 
color. In other words, each list forms a clique.
*/

bool comp(pair<int, int> x, pair<int, int> y) {
  if (x.second > y.second) return true;
  if (x.second < y.second) return false;
  if (x.first < y.first) return true;
  return true;
}

void setBit(unsigned int &x, int i) { 
  x = x | (1 << i);
} 

void clearBit(unsigned int &x, int i) { 
  x = x & (~(1 << i));
} 

unsigned int getBit(unsigned int x, int i) { 
  return ((x & 1 << i) != 0); 
}

//////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph(vector< vector<int> > list) {
  mList.clear();
  mComplementList.clear();
  nVertex = 0;
  if (list.size() == 0) return;
  nVertex = list.size();
  for (int i = 0; i < nVertex; i ++) {
    vector<int> newList;
    for (int j = 0; j < list[i].size(); j ++) {
      newList.push_back(list[i][j]);
    }
    mList.push_back(newList);
  }
  calComplementList();
}

void Graph::calComplementList() {
  mComplementList.clear();
  for (int i = 0; i < nVertex; i ++) {
    vector<int> newList;
    bool adjacent[MAX_NUMBER_OF_VERTICES];
    for (int j = 0; j < nVertex; j ++) {
      adjacent[j] = false;
    }
    for (int j = 0; j < mList[i].size(); j ++) {
      adjacent[mList[i][j]] = true;
    }
    for (int j = 0; j < nVertex; j ++) 
      if (!adjacent[j]) {
	newList.push_back(j);
      }
    mComplementList.push_back(newList);
  }
}

vector< vector<int> > Graph::getAdjList() {
  return mList;
}

vector< vector<int> > Graph::getComplementAdjList() {
  return mComplementList;
}
//////////////////////////////////////////////////////////////////////////////////

void Clique::intersect(unsigned int * lli, unsigned int * R, unsigned int *Rp) {
  for (int i = 0; i <= (n - 1) / BITS; i ++) {
    Rp[i] = (lli[i] & R[i]);
  }
}

int Clique::CountOneBit(int start, unsigned int *x) {
  int ret = 0;
  for (int i = start; i <= (n - 1) / BITS; i ++)
    ret = ret + __builtin_popcount(x[i]);
  return ret;
}

bool Clique::isConnected(int i, int j) {
  return (getBit(ll[i][j / BITS], j % BITS) == 1);
}

void Clique::BASICEXPAND(unsigned int * Rem, unsigned int CurCliqueSize) {
  int NumRem = 0;
  NumRem = CountOneBit(0, Rem);
  if (NumRem == 0) {
    if (MaxCliqueSize < CurCliqueSize) {
      MaxCliqueSize = CurCliqueSize;
      for (int i = 0; i < (n - 1) / BITS; i ++) {
	Qmax[i] = Q[i];
      }
    }
    return;
  }
  if (CurCliqueSize + NumRem <= MaxCliqueSize) {
    return;
  }
  while (NumRem > 0) {
    for (int p = 0; p < n; p ++)
      if (getBit(Rem[p / BITS], p % BITS)) {
	if (CurCliqueSize + NumRem > MaxCliqueSize) {
	  unsigned int Rp[MAX_NUMBER_OF_VERTICES / BITS + 1];
	  setBit(Q[p / BITS], p % BITS);
	  intersect(ll[p], Rem, Rp);
	  BASICEXPAND(Rp, CurCliqueSize + 1);
	  clearBit(Q[p / BITS], p % BITS);
	}
	clearBit(Rem[p / BITS], p % BITS);
	NumRem --;
      }
  }
}

int Clique::VertexColor(unsigned int *Rem, unsigned int *Col, unsigned int &CurListSize) {
  unsigned int Color[MAX_NUMBER_OF_VERTICES];
  unsigned int CurList[MAX_NUMBER_OF_VERTICES];
  bool Choosed[MAX_NUMBER_OF_VERTICES];
  CurListSize = 0;
  int CurColor = 0;
  for (int i = 0; i < n; i ++)
    if (getBit(Rem[deg[i].first / BITS], deg[i].first % BITS)) {
      CurList[CurListSize ++] = deg[i].first;
    }
  for (int i = 0; i < CurListSize; i ++) {
    Color[i] = 0;
    for (int j = 1; j <= CurColor; j ++) {
      Choosed[j] = false;
    }
    for (int j = i - 1; j >= 0; j --)
      if (isConnected(CurList[i], CurList[j])) {
	Choosed[ Color[j] ] = true;
      }
    for (int j = 1; j <= CurColor; j ++)
      if (!Choosed[j]) {
	Color[i] = j;
	break;
      }
    if (Color[i] == 0) {
      CurColor ++;
      Color[i] = CurColor;
    }
  }
  int k = 0;
  for (int i = 1; i <= CurColor; i ++)
    for (int j = 0; j < CurListSize; j ++)
      if (Color[j] == i) {
	Col[k ++] = CurList[j];
      }
  return CurColor;
}

void Clique::EXPAND(unsigned int * Rem, unsigned int CurCliqueSize) {
  unsigned int Col[MAX_NUMBER_OF_VERTICES];
  unsigned int CurListSize;
  //  int NumRem = CountOneBit(0, Rem);
  int ColorNum = VertexColor(Rem, Col, CurListSize);
  if (CurListSize == 0) {
    if (MaxCliqueSize < CurCliqueSize) {
      MaxCliqueSize = CurCliqueSize;
      cout << MaxCliqueSize << endl;
      for (int i = 0; i < (n - 1) / BITS; i ++) {
	Qmax[i] = Q[i];
      }
    }
    return;
  }
  if (CurCliqueSize + ColorNum <= MaxCliqueSize) {
    return;
  }
  for (int i = CurListSize - 1; i >= 0; i --) {
    int p = Col[i];
    if (getBit(Rem[p / BITS], p % BITS)) {
      unsigned int Rp[MAX_NUMBER_OF_VERTICES / BITS + 1];
      setBit(Q[p / BITS], p % BITS);
      intersect(ll[p], Rem, Rp);
      EXPAND(Rp, CurCliqueSize + 1);
      clearBit(Q[p / BITS], p % BITS);
      clearBit(Rem[p / BITS], p % BITS);
    }
  }
}

int Clique::MaxCliqueFinding() {
  unsigned int Rem[MAX_NUMBER_OF_VERTICES / BITS + 1];
  MaxCliqueSize = 0;
  for (int i = 0; i <= (n - 1) / BITS; i ++) {
    Rem[i] = 0;
  }
  for (int i = 0; i <= (n - 1) / BITS; i ++) {
    Q[i] = Qmax[i] = 0;
  }
  for (int i = 0; i < n; i ++) {
    setBit(Rem[i / BITS], i % BITS);
  }
  EXPAND(Rem, 0);
  return MaxCliqueSize;
}

void Clique::CliqueCover() {
  bool Cover[MAX_NUMBER_OF_VERTICES];
  MaxClique.clear();
  CliqueList.clear();
  for (int i = 0; i < n; i ++) {
    Cover[i] = false;
  }
  while (MaxCliqueFinding() > 0) {
    vector<int> newClique;
    for (int i = 0; i <= n - 1; i ++) {
      if (getBit(Qmax[i / BITS], i % BITS))
	Cover[i] = true;
	newClique.push_back(i);
	for (int j = 0; j <= n - 1; j ++) {
	  clearBit(ll[i][j / BITS], j % BITS);
	  clearBit(ll[j][i / BITS], i % BITS);	    
	}
      }
    CliqueList.push_back(newClique);
    if (MaxClique.size() == 0) {
      for (int i = 0; i < newClique.size(); i ++) {
	MaxClique.push_back(newClique[i]);
      }
    }
  }
}

Clique::Clique() {
}

Clique::Clique(Graph OriginalGraph) {
  vector< vector<int> > graph = OriginalGraph.getAdjList();
  if (graph.size() == 0) {
    cout << "Error: empty adjacent list." << endl;
  }
  n = graph.size();
  for (int i = 0; i < n; i ++) {
    deg.push_back(pair<int, int>(i, graph[i].size()));
    for (int j = 0; j <= (n - 1) / BITS; j ++) {
      ll[i][j] = 0;
    }
  }
  sort(deg.begin(), deg.end(), comp);
  for (int i = 0; i < n; i ++) {
    for (int t = 0; t < graph[i].size(); t ++) {
      int j = graph[i][t];
      setBit(ll[i][j / BITS], j % BITS);
    }
  }
  cout << "Maximum clique size: " << MaxCliqueSize << endl;
  CliqueCover();
};

vector<int> Clique::getMaximumClique() {
  return MaxClique;
}

vector< vector<int> > Clique::getCliqueCoverList() {
  return CliqueList;
}

void Clique::displayResult() {
  cout << "The number of cliques which cover all vertices: " << CliqueList.size() << endl;
  for (int i = 0; i < CliqueList.size(); i ++) {
    for (int j = 0; j < CliqueList[i].size(); j ++) {
      cout << CliqueList[i][j] << " ";
    }
    cout << endl;
  }
}

///////////////////////////////////////////////////////////////////////////////////

bool VertexColor::isConnected(int i, int j) {
  return (getBit(ll[i][j / BITS], j % BITS) == 1);
}

VertexColor::VertexColor() {
  deg.clear();
  ColorList.clear();
}

VertexColor::VertexColor(Graph OriginalGraph) {
  vector< vector<int> > graph = OriginalGraph.getAdjList();
  if (graph.size() == 0) {
    cout << "Error: empty adjacent list." << endl;
  }
  n = graph.size();
  for (int i = 0; i < n; i ++) {
    deg.push_back(pair<int, int>(i, graph[i].size()));
    for (int j = 0; j <= (n - 1) / BITS; j ++) {
      ll[i][j] = 0;
    }
  }
  sort(deg.begin(), deg.end(), comp);
  for (int i = 0; i < n; i ++) {
    for (int t = 0; t < graph[i].size(); t ++) {
      int j = graph[i][t];
      setBit(ll[i][j / BITS], j % BITS);
    }
  }
  HeuristicColoring();
  getColorList();
}

void VertexColor::Coloring() {
}

void VertexColor::HeuristicColoring() {
  int Color[MAX_NUMBER_OF_VERTICES];
  int CurColor = 0;
  for (int i = 0; i < n; i ++) {
    int u = deg[i].first;    
    Color[u] = -1;
    bool Used[MAX_NUMBER_OF_VERTICES];
    for (int j = 0; j < CurColor; j ++) {
      Used[j] = false;
    }
    for (int j = 0; j < i; j ++) {
      int v = deg[j].first;
      if (isConnected(u, v)) {
	Used[Color[v]] = true;
      }
    }
    for (int j = 0; j < CurColor; j ++)
      if (!Used[j]) {
	Color[u] = j;
	ColorList[j].push_back(u);
	break;
      }
    if (Color[u] == -1) {
      CurColor ++;
      Color[u] = CurColor - 1;
      vector<int> newColor;
      newColor.push_back(u);
      ColorList.push_back(newColor);
    }
  }
}

vector< vector<int> > VertexColor::getColorList() {
  cout << ColorList.size() << endl;
  for (int i = 0; i < ColorList.size(); i ++) {
    cout << i << ": ";
    for (int j = 0; j < ColorList[i].size(); j ++)
      cout << ColorList[i][j] << " ";
    cout << endl;
  }
  return ColorList;
}

void VertexColor::displayResult() {
}

//////////////////////////////////////////////////////////////////////////////////
