//
// Test program for the two libraries: max clique finding and vertex color.
//

#include "../src/Clique.h"
#include "../src/Graph.h"
#include "../src/VertexColor.h"

void DIMACSTest();
void UnitTest();
void CheckColorCorrection(ngclique::Graph &, ngclique::VertexColor &);
void CheckCliqueCorrection(ngclique::Graph &, ngclique::Clique &);

int main() {
  UnitTest();
  // DIMACSTest();
  return 0;
}

void CheckColorCorrection(ngclique::Graph &graph, ngclique::VertexColor &vertexcolor) {
  cout << "Check GRAPH COLOR algorithm: " << endl;
  vector<int> color(graph.num_vertices(), -1);
  
  vector< vector<int> > color_list = vertexcolor.GetColorList();
  
  for (size_t i = 0; i < color_list.size(); i ++) {
    for (size_t j = 0; j < color_list[i].size(); j ++) {
      int u = color_list[i][j];
      if (color[u] == -1) color[u] = i;
      else {
	cout << "ERROR: a vertex is colored twice." << endl;
	return;
      }
    }

    for (size_t j = 0; j < color_list[i].size(); j ++) {
      int u = color_list[i][j];
      for (size_t k = j + 1; k < color_list[i].size(); k ++) {
	int v = color_list[i][k];
	if (graph.IsConnected(u, v)) {
	  cout << "ERROR: " << u << " and " << v << " are adjacent but same color." << endl;
	  return ;
	}
      }
    }
  }

  cout << "CORRECT!!! " << color_list.size() << " colors are used." << endl;

  for (size_t i = 0; i < color_list.size(); i ++) {
    for (size_t j = 0; j < color_list[i].size(); j ++)
      cout << color_list[i][j] << " ";
    cout << endl;
  }
}

void CheckCliqueCorrection(ngclique::Graph &graph, ngclique::Clique &clique) {
  cout << "Check MAX. CLIQUE algorithm: " << endl;
  vector<int> max_clique = clique.max_clique();
  for (size_t i = 0; i < max_clique.size(); i ++) {
    for (size_t j = i + 1; j < max_clique.size(); j ++) {
      if (!graph.IsConnected(max_clique[i], max_clique[j])) {
	cout << "ERROR: " << max_clique[i] << " and " << max_clique[j] << 
	  " are not adjacent but belong to the same clique." << endl;
      }
    }
  }
  cout << "CORRECT!!! " << max_clique.size() << endl;

  cout << "Check CLIQUE PARTITION algorithm: " << endl;
  vector<int> belong_to_clique(graph.num_vertices(), -1);

  vector< vector<int> > clique_list = clique.clique_partition_list();

  for (size_t i = 0; i < clique_list.size(); i ++) {
    for (size_t j = 0; j < clique_list[i].size(); j ++) {
      int u = clique_list[i][j];
      if (belong_to_clique[u] == -1) {
	belong_to_clique[u] = i;
      }
      else {
	cout << "ERROR: vertex " << u << " belongs to two cliques." << endl;
      }
    }

    for (size_t j = 0; j < clique_list[i].size(); j ++) {
      int u = clique_list[i][j];
      for (size_t k = j + 1; k < clique_list[i].size(); k ++) {
	int v = clique_list[i][k];
	if (!graph.IsConnected(u, v)) {
	  cout << "ERROR: " << u << " and " << v << " are not adjacent but belong to the same clique." << endl;
	  return;
	}
      }
    }
  }

  cout << "CORRECT!!! " << clique_list.size() << " partitions are found." << endl;
}

/*
7
2 1 2
4 0 4 5 6
2 0 3
2 2 6
3 1 5 6
3 1 4 6
4 1 3 4 5
*/

void UnitTest() {
  size_t n;
  vector<int> adjlist[MAX_NUMBER_OF_VERTICES];
  vector< vector<int> > list;

  cin >> n;
  for (size_t i = 0; i < n; i ++) {
    adjlist[i].clear();
    unsigned int deg;
    cin >> deg;
    for (size_t k = 0; k < deg; k ++) {
      int j;
      cin >> j;
      adjlist[i].push_back(j);
    }
  }
  list.clear();
  for (size_t i = 0; i < n; i ++) {
    list.push_back(adjlist[i]);
  }

  ngclique::Graph graph(list);
  ngclique::Graph complement(graph.complement_adj_list());

  ngclique::VertexColor vertexcolor(complement);
  ngclique::Clique clique(graph);

  CheckCliqueCorrection(graph, clique);

  cout << "As for the complement graph:" << endl;
  CheckColorCorrection(complement, vertexcolor);
}

void DIMACSTest() {
  size_t n, m;
  vector<int> adjlist[MAX_NUMBER_OF_VERTICES];
  vector< vector<int> > list;

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

  // TODO: finish DIMACS test
  ngclique::Graph graph(list);
  ngclique::Clique clique(graph);
}
