/*
  Clique: Partition the graph into subsets of vertices. Each set forms a clique.
*/

#ifndef CLIQUE_H
#define CLIQUE_H

#include "Graph.h"

#define BITS 32

namespace ngclique {

  class Clique {
  public:
    Clique();
    Clique(Graph &graph);
    ~Clique();

    vector<int> max_clique() { 
      if (max_clique_.size() == 0) FindMaxClique(); 
      return max_clique_;
    };

    vector< vector<int> > clique_partition_list() {
      if (clique_list_.size() == 0) CliquePartition(); 
      return clique_list_;
    };

  private:
    bool IsConnected(int, int);
    vector<unsigned int> Intersect(vector<unsigned int> &adj_list_i, vector<unsigned int> &R);
    int CountOneBit(int start, vector<unsigned int> &x);
  
    int VertexColor(vector<unsigned int> &rem, vector<unsigned int> &col, unsigned int &cur_list_size);
    void Expand(vector<unsigned int> &rem, unsigned int cur_clique_size); 
    void BasicExpand(vector<unsigned int> &rem, unsigned int cur_clique_size);
    int FindMaxClique();
    void CliquePartition();  

  private: 
    size_t num_vertices_;

    // Adjacency matrix
    vector< vector<unsigned int> > adj_matrix_;

    // vector of pairs (vertex id, vertex degree) 
    vector<IdDeg> id_deg_;

    //set of current clique
    vector<unsigned int> cur_clique_;

    //set of current maximum clique 
    vector<unsigned int> cur_max_clique_;
  
    vector<bool> colored_;
  
    unsigned int max_clique_size_;

    vector<int> max_clique_;
    vector< vector<int> > clique_list_;
  };

}

#endif
