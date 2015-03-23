//
// Test program for the two libraries: max clique finding and vertex color.
//

#include "../src/Clique.h"
#include "../src/Graph.h"
#include "../src/VertexColor.h"

int n, m;
vector<int> adjlist[MAX_NUMBER_OF_VERTICES];
vector< vector<int> > list;

void DIMACSTest();
void UnitTest();
void CheckColorCorrection(Graph &, VertexColor &);
void CheckCliqueCorrection(Graph &, Clique &);

int main() {
  UnitTest();
  // DIMACSTest();
  return 0;
}

void CheckColorCorrection(Graph &graph, VertexColor &vertexcolor) {
  cout << "Check GRAPH COLOR algorithm: " << endl;
  int color[MAX_NUMBER_OF_VERTICES];
  for (size_t i = 0; i < graph.getNumVertices(); i ++) {
    color[i] = -1;
  }
  vector< vector<int> > ColorList = vertexcolor.getColorList();
  for (size_t i = 0; i < ColorList.size(); i ++) {
    for (size_t j = 0; j < ColorList[i].size(); j ++) {
      int u = ColorList[i][j];
      if (color[u] == -1) color[u] = i;
      else {
	cout << "ERROR: a vertex is colored twice." << endl;
	return;
      }
    }
    for (size_t j = 0; j < ColorList[i].size(); j ++) {
      int u = ColorList[i][j];
      for (size_t k = j + 1; k < ColorList[i].size(); k ++) {
	int v = ColorList[i][k];
	if (graph.isConnected(u, v)) {
	  cout << "ERROR: " << u << " and " << v << " are adjacent but same color." << endl;
	  return ;
	}
      }
    }
  }
  cout << "CORRECT!!! " << ColorList.size() << " colors are used." << endl;
  for (size_t i = 0; i < ColorList.size(); i ++) {
    for (size_t j = 0; j < ColorList[i].size(); j ++)
      cout << ColorList[i][j] << " ";
    cout << endl;
  }
}

void CheckCliqueCorrection(Graph &graph, Clique &clique) {
  cout << "Check CLIQUE PARTITION algorithm: " << endl;
  int color[MAX_NUMBER_OF_VERTICES];
  for (size_t i = 0; i < graph.getNumVertices(); i ++) {
    color[i] = -1;
  }
  vector< vector<int> > colorList = clique.getCliquePartitionList();
  for (size_t i = 0; i < colorList.size(); i ++) {
    for (size_t j = 0; j < colorList[i].size(); j ++) {
      int u = colorList[i][j];
      if (color[u] == -1) color[u] = i;
      else {
	cout << "ERROR: a vertex is colored twice." << endl;
      }
    }
    for (size_t j = 0; j < colorList[i].size(); j ++) {
      int u = colorList[i][j];
      for (size_t k = j + 1; k < colorList[i].size(); k ++) {
	int v = colorList[i][k];
	if (graph.isConnected(u, v)) {
	  cout << "ERROR: " << u << " and " << v << " are adjacent but same color." << endl;
	  return ;
	}
      }
    }
  }
  cout << "CORRECT!!! " << colorList.size() << " partitions are found." << endl;
  for (size_t i = 0; i < colorList.size(); i ++) {
    for (size_t j = 0; j < colorList[i].size(); j ++)
      cout << colorList[i][j] << " ";
    cout << endl;
  }
}

void UnitTest() {
  cin >> n;
  for (size_t i = 0; i < n; i ++) {
    int deg;
    cin >> deg;
    for (size_t k = 0; k < deg; k ++) {
      int j;
      cin >> j;
      adjlist[i].push_back(j);
    }
  }
  for (size_t i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }
  Graph graph(list);
  Graph complement(graph.getComplementAdjList());
  VertexColor vertexcolor(complement);
  Clique clique(graph);
  CheckCliqueCorrection(complement, clique);
  CheckColorCorrection(complement, vertexcolor);
}

void DIMACSTest() {
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
  for (size_t i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }
  Graph graph(list);
  Clique clique(graph);
}