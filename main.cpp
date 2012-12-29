#include "Graph.h"

int n, m;
vector<int> adjlist[MAX_NUMBER_OF_VERTICES];
vector< vector<int> > list;

void DIMACS();
void UnitTest();

int main() {
  UnitTest();
  //  DIMACS();
  return 0;
}

void UnitTest() {
  cin >> n >> m;
  for (int e = 0; e < m; e ++) {
    int i, j;
    cin >> i >> j;
    adjlist[i].push_back(j);
    adjlist[j].push_back(i);
  }
  for (int i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }
  Graph graph(list);
  //  Clique clique(graph);
  VertexColor vertexcolor(graph);
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
