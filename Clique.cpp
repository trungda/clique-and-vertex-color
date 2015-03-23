#include "Clique.h"

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
}

Clique::~Clique() {
  deg.clear();
  maxClique.clear();
  cliqueList.clear();
}

void Clique::intersect(unsigned int * lli, unsigned int * R, unsigned int *Rp) {
  for (int i = 0; i <= (n - 1) / BITS; i ++) {
    Rp[i] = (lli[i] & R[i]);
  }
}

int Clique::countOneBit(int start, unsigned int *x) {
  int ret = 0;
  for (int i = start; i <= (n - 1) / BITS; i ++)
    ret = ret + __builtin_popcount(x[i]);
  return ret;
}

bool Clique::isConnected(int i, int j) {
  return (getBit(ll[i][j / BITS], j % BITS) == 1);
}

void Clique::basicExpand(unsigned int *rem, unsigned int curCliqueSize) {
  int numRem = 0;
  numRem = countOneBit(0, rem);
  if (numRem == 0) {
    if (maxCliqueSize < curCliqueSize) {
      maxCliqueSize = curCliqueSize;
      for (int i = 0; i < (n - 1) / BITS; i ++) {
	Qmax[i] = Q[i];
      }
    }
    return;
  }
  if (curCliqueSize + numRem <= maxCliqueSize) {
    return;
  }
  while (numRem > 0) {
    for (int p = 0; p < n; p ++)
      if (getBit(rem[p / BITS], p % BITS)) {
	if (curCliqueSize + numRem > maxCliqueSize) {
	  unsigned int rp[MAX_NUMBER_OF_VERTICES / BITS + 1];
	  setBit(Q[p / BITS], p % BITS);
	  intersect(ll[p], rem, rp);
	  basicExpand(rp, curCliqueSize + 1);
	  clearBit(Q[p / BITS], p % BITS);
	}
	clearBit(rem[p / BITS], p % BITS);
	numRem --;
      }
  }
}

int Clique::vertexColor(unsigned int *Rem, unsigned int *Col, unsigned int &CurListSize) {
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

void Clique::expand(unsigned int *rem, unsigned int curCliqueSize) {
  unsigned int col[MAX_NUMBER_OF_VERTICES];
  unsigned int curListSize;
  int colorNum = vertexColor(rem, col, curListSize);
  if (curListSize == 0) {
    if (maxCliqueSize < curCliqueSize) {
      maxCliqueSize = curCliqueSize;
      for (int i = 0; i <= (n - 1) / BITS; i ++) {
	Qmax[i] = Q[i];
      }
    }
    return;
  }
  if (curCliqueSize + colorNum <= maxCliqueSize) {
    return;
  }
  for (int i = curListSize - 1; i >= 0; i --) {
    int p = col[i];
    if (getBit(rem[p / BITS], p % BITS)) {
      unsigned int rp[MAX_NUMBER_OF_VERTICES / BITS + 1];
      setBit(Q[p / BITS], p % BITS);
      intersect(ll[p], rem, rp);
      expand(rp, curCliqueSize + 1);
      clearBit(Q[p / BITS], p % BITS);
      clearBit(rem[p / BITS], p % BITS);
    }
  }
}

int Clique::maxCliqueFinding() {
  unsigned int rem[MAX_NUMBER_OF_VERTICES / BITS + 1];
  maxCliqueSize = 0;
  for (int i = 0; i <= (n - 1) / BITS; i ++) {
    rem[i] = Q[i] = Qmax[i] = 0;
  }
  for (int i = 0; i < n; i ++) 
    if (!Colored[i]) {
      setBit(rem[i / BITS], i % BITS);
    }
  expand(rem, 0);
  maxClique.clear();
  for (int i = 0; i < n; i ++) {
    if (getBit(Qmax[i / BITS], i % BITS)) {
      maxClique.push_back(i);
    }
  }
  maxCliqueSize = maxClique.size();
  return maxCliqueSize;
}

void Clique::cliquePartition() {
  maxClique.clear();
  cliqueList.clear();
  for (int i = 0; i < n; i ++) {
    Colored[i] = false;
  }
  // clique partition by finding MAXIMUM clique each time
  // while (maxCliqueFinding() > 0) {
  //   vector<int> newClique;
  //   for (int i = 0; i < n; i ++) {
  //     if (getBit(Qmax[i / BITS], i % BITS)) {
  // 	Colored[i] = true;
  // 	newClique.push_back(i);
  //     }
  //   }
  //   cliqueList.push_back(newClique);
  // }

  // Clique partition by finding MAXIMAL clique each time
  int id = 0;
  while (id < n) {
    int u = deg[id].first;
    if (Colored[u]) {
      id ++;
      continue;
    }
    vector<int> newClique;
    newClique.push_back(u);
    for (int i = id + 1; i < n; i ++) {
      int v = deg[i].first;
      if (Colored[v]) continue;
      bool ok = true;
      for (int j = 0; j < newClique.size(); j ++)
	if (!isConnected(newClique[j], v)) {
	  ok = false;
	  break;
	}
      if (ok) {
	newClique.push_back(v);
      }
    }
    for (int i = 0; i < newClique.size(); i ++) {
      Colored[newClique[i]] = true;
    }
    cliqueList.push_back(newClique);
  }
  for (int i = 0; i < n; i ++) {
    Colored[i] = false;
  }
}

vector<int> Clique::getMaximumCliqueList() {
  maxCliqueFinding();
  return maxClique;
}

vector< vector<int> > Clique::getCliquePartitionList() {
  cliquePartition();
  return cliqueList;
}

