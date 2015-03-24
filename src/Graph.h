/* 
   Graph: A class holds the information of a graph in form of adjacent list: mList
   + Graph(): Constructor; creates a graph from file for testing purpose
   + Graph(vector<ES>): Constructor; creates a graph from list of ES. There is an edge between two ES instances if 
   they are compatible
   + calReversedList(): Creates a reversed graph from the current graph and holds the information of this graph in 
   mReversedList. There is an edge between two vertices in the new graph if there is no edge between these two 
   vertices in the original graph. This function is used for Vertex Coloring Problem
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

namespace ngclique {

#define MAX_NUMBER_OF_VERTICES 1000
#define MAX_NUMBER_OF_COLORS 1000

  typedef pair<int, int> IdDeg;

  class Graph {
  public:
    Graph();

    // Constructor that passes adjacency lists as a parameter
    Graph(vector< vector<int> >);

    ~Graph();

    size_t num_vertices() const {return num_vertices_;};
    vector< vector<int> > adj_list() const {return adj_list_;};
    vector< vector<int> > complement_adj_list() const {return complement_adj_list_;};

    bool IsConnected(int, int) const;

  private:
    void cal_complement_list();

  private:
    size_t num_vertices_;
    vector< vector<int> > adj_list_;
  
    // adjacency lists of the complement graph
    vector< vector<int> > complement_adj_list_;
  };

  bool comp(const IdDeg &, const IdDeg &);

  void set_bit(unsigned int &x, int i);
  void clear_bit(unsigned int &x, int i);
  unsigned int get_bit(unsigned int x, int i);

}

#endif
