/*
  VertexColor: Solve the same problem as CliqueCover but using a different approach
*/
#ifndef VERTEX_COLOR_H
#define VERTEX_COLOR_H

#include "Clique.h"
#include "Graph.h"

namespace ngclique {

  class VertexColor {
  public:  
    VertexColor();
    VertexColor(Graph &graph);
    ~VertexColor();
    vector< vector<int> > GetColorList();

  private:
    bool IsConnected(int, int);
  
    bool IsPossible(int, int);
    void Update(int, int);

    void HeuristicColoring();
    void BbColoring(int, int); // branch and bound coloring
    void Coloring();  

  private:
    size_t num_vertices_;

    int cur_used_color_;
    int best_color_num_; // best number of used colors up to now

    vector< vector<unsigned int> > adj_matrix_;
    vector< IdDeg > id_deg_;

    vector<int> color_;

    vector<int> cur_color_;
  
    vector<int> dsatur_; // degree of saturation list

  };

}

#endif
