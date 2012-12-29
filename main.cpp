#include "Graph.h"

int n, m;
vector<int> adjlist[MAX_NUMBER_OF_VERTICES];
vector< vector<int> > list;

void DIMACS();
void UnitTest();
void CheckColorCorrection(Graph &, VertexColor &);

int main() {
  UnitTest();
  //  DIMACS();
  return 0;
}

void CheckColorCorrection(Graph &graph, VertexColor & vertexcolor) {
  int color[MAX_NUMBER_OF_VERTICES];
  for (int i = 0; i < graph.getNumVertices(); i ++) {
    color[i] = -1;
  }
  vector< vector<int> > ColorList = vertexcolor.getColorList();  
  for (int i = 0; i < ColorList.size(); i ++) {
    for (int j = 0; j < ColorList[i].size(); j ++) {
      int u = ColorList[i][j];
      if (color[u] == -1) color[u] = i;
      else {
	cout << "ERROR: a vertex is colored twice." << endl;
	return;
      }
    }
    for (int j = 0; j < ColorList[i].size(); j ++) {
      int u = ColorList[i][j];
      for (int k = j + 1; k < ColorList[i].size(); k ++) {
	int v = ColorList[i][k];
	if (graph.isConnected(u, v)) {
	  cout << "ERROR: " << u << " and " << v << "are adjacent but same color." << endl;
	  return ;
	}
      }
    }
  }
  cout << "CORRECT!!! " << ColorList.size() << " colors are used." << endl;
  for (int i = 0; i < ColorList.size(); i ++) {
    for (int j = 0; j < ColorList[i].size(); j ++)
      cout << ColorList[i][j] << " ";
    cout << endl;
  }
}

void UnitTest() {
  cin >> n;
  for (int i = 0; i < n; i ++) {
    int deg;
    cin >> deg;
    for (int k = 0; k < deg; k ++) {
      int j;
      cin >> j;
      adjlist[i].push_back(j);
    }
  }
  for (int i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }
  Graph graph(list);
  VertexColor vertexcolor(graph);
  //Clique clique(graph);
  CheckColorCorrection(graph, vertexcolor);
}

void DIMACS() {
  char command;
  while (cin >> command) {
    string s;
    if (command == 'c') {
      getline(cin, s);
      continue;
    }
    else if (command == 'p') {
      cin >> s >> n >> m;
    }
    else if (command == 'e') {
      int i, j;
      cin >> i >> j;
      i --;
      j --;
      adjlist[i].push_back(j);
      adjlist[j].push_back(i);
    }
  }
  for (int i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }
  Graph graph(list);
  Clique clique(graph);
  vector<int> maxclique = clique.getMaximumClique();
}
