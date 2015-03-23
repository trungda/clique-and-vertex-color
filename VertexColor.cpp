#include "VertexColor.h"

bool VertexColor::isConnected(int i, int j) {
  return (getBit(ll[i][j / BITS], j % BITS) == 1);
}

VertexColor::VertexColor() {
  deg.clear();
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
    curColor[i] = -1;
    DSATUR[i] = 0;
    for (int t = 0; t < graph[i].size(); t ++) {
      int j = graph[i][t];
      setBit(ll[i][j / BITS], j % BITS);
    }
  }
  heuristicColoring();
  cout << "Heuristic result: " << bestColorNum << endl;
  Clique clique(OriginalGraph);
  vector<int> InitialList = clique.getMaximumCliqueList();
  for (int i = 0; i < InitialList.size(); i ++) {
    curColor[InitialList[i]] = i;
    for (int j = 0; j < n; j ++)
      if (isConnected(InitialList[i], j)) {
	DSATUR[j] ++;
      }
  }
  curUsedColor = InitialList.size();
}

VertexColor::~VertexColor() {
  deg.clear();
}

void VertexColor::heuristicColoring() {
  int curColor = 0;
  for (int i = 0; i < n; i ++) {
    int u = deg[i].first;
    color[u] = -1;
    bool Used[MAX_NUMBER_OF_VERTICES];
    for (int j = 0; j < curColor; j ++) {
      Used[j] = false;
    }
    for (int j = 0; j < i; j ++) {
      int v = deg[j].first;
      if (isConnected(u, v)) {
	Used[color[v]] = true;
      }
    }
    for (int j = 0; j < curColor; j ++)
      if (!Used[j]) {
	color[u] = j;
	break;
      }
    if (color[u] == -1) {
      curColor ++;
      color[u] = curColor - 1;
      vector<int> newColor;
      newColor.push_back(u);
    }
  }
  bestColorNum = curColor;
}

// uu can be colored by color j
bool VertexColor::isPossible(int uu, int j) {
  for (int i = 0; i < n; i ++)
    if (curColor[i] != -1 && isConnected(i, uu) && curColor[i] == j) {
      return false;
    }
  return true;
}

void VertexColor::update(int uu, int t) {
  for (int i = 0; i < n; i ++)
    if (isConnected(i, uu)) {
      DSATUR[i] += t;
    }
}

void VertexColor::bbColoring(int Remain, int curUsedColor) {
  if (Remain <= 0) {
    if (curUsedColor < bestColorNum) {
      bestColorNum = curUsedColor;
      cout << "New val: " << bestColorNum << endl;
      for (int i = 0; i < n; i ++) {
	color[i] = curColor[i];
      }
    }
    return;
  }
  if (curUsedColor >= bestColorNum) return;
  int MaxDSATUR = -1;
  int uu = -1;
  for (int i = 0; i < n; i ++) {
    int u = deg[i].first;
    if (curColor[u] != -1) continue;
    if (DSATUR[u] > MaxDSATUR) {
      MaxDSATUR = DSATUR[u];
      uu = u;
    }
  }
  for (int j = 0; j < curUsedColor + 1; j ++) 
    if (isPossible(uu, j)) {
      curColor[uu] = j;
      update(uu, 1);
      bbColoring(Remain - 1, max(curUsedColor, j + 1));
      curColor[uu] = -1;
      update(uu, -1);
    }
}

void VertexColor::coloring() {
  // Find maximum clique in the given graph to determine initial colors
  int Remain = n - curUsedColor;
  bbColoring(Remain, curUsedColor);
}

vector< vector<int> > VertexColor::getColorList() {
  coloring();
  vector< vector<int> > colorList;
  for (int i = 0; i < bestColorNum; i ++) {
    vector<int> newColor;
    colorList.push_back(newColor);
  }
  for (int i = 0; i < n; i ++) {
    colorList[color[i]].push_back(i);
  }
  return colorList;
}

