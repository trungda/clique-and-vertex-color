#include "Graph.h"

namespace ngclique {

  Graph::Graph() {
  }

  Graph::Graph(vector< vector<int> > adj_list) {
    adj_list_.clear();

    num_vertices_ = adj_list.size();

    for (size_t i = 0; i < num_vertices_; i ++) {
      sort(adj_list[i].begin(), adj_list[i].end());
      adj_list_.push_back(adj_list[i]);
    }

    cal_complement_list();
  }

  Graph::~Graph() {
    adj_list_.clear();
    complement_adj_list_.clear();
  }

  void Graph::cal_complement_list() {
    complement_adj_list_.clear();
    for (size_t i = 0; i < num_vertices_; i ++) {
      vector<int> new_adj_list;
      vector<bool> adjacent(num_vertices_, false);
      adjacent[i] = true;
      for (size_t j = 0; j < adj_list_[i].size(); j ++) {
	adjacent[adj_list_[i][j]] = true;
      }

      for (size_t j = 0; j < num_vertices_; j ++) {
	if (!adjacent[j]) {
	  new_adj_list.push_back(j);
	}
      }

      complement_adj_list_.push_back(new_adj_list);
    }
  }

  bool Graph::IsConnected(int i, int j) const {
    if (adj_list_[i].size() == 0) {
      return false;
    }

    int lo = 0;
    int hi = adj_list_[i].size() - 1;
    while (lo <= hi) {
      int mid = (lo + hi) / 2;
      if (adj_list_[i][mid] == j) return true;
      if (adj_list_[i][mid] > j) hi = mid - 1;
      else lo = mid + 1;
    }

    return false;
  }

  // helper functions

  bool comp(const IdDeg &x, const IdDeg &y) {
    if (x.second > y.second) return true;
    if (x.second < y.second) return false;
    if (x.first < y.first) return true;
    return false;
  }

  void set_bit(unsigned int &x, int i) { 
    x = x | (1 << i);
  } 

  void clear_bit(unsigned int &x, int i) { 
    x = x & (~(1 << i));
  } 

  unsigned int get_bit(unsigned int x, int i) { 
    return ((x & 1 << i) != 0); 
  }

}
