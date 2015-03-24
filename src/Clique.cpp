#include "Clique.h"

#include <cassert>

namespace ngclique {

  Clique::Clique() {
  }

  Clique::Clique(Graph &graph) {
    assert(graph.num_vertices() != 0);

    vector< vector<int> > adj_list = graph.adj_list();
    num_vertices_ = adj_list.size();

    for (size_t i = 0; i < num_vertices_; i ++) {
      adj_matrix_.push_back(vector<unsigned int>(num_vertices_ / BITS + 1, 0));
    }

    for (size_t i = 0; i < num_vertices_; i ++) {
      id_deg_.push_back(pair<int, int>(i, adj_list[i].size()));
      colored_.push_back(false);
    }

    for (size_t i = 0; i < num_vertices_ / BITS + 1; i ++) {
      cur_clique_.push_back(0);
      cur_max_clique_.push_back(0);
    }

    sort(id_deg_.begin(), id_deg_.end(), comp);

    for (size_t i = 0; i < num_vertices_; i ++) {
      for (size_t t = 0; t < adj_list[i].size(); t ++) {
	int j = adj_list[i][t];
	set_bit(adj_matrix_[i][j / BITS], j % BITS);
      }
    }

  }

  Clique::~Clique() {
  }

  bool Clique::IsConnected(int i, int j) {
    return (get_bit(adj_matrix_[i][j / BITS], j % BITS) == 1);
  }

  vector<unsigned int> Clique::Intersect(vector<unsigned int> &adj_list_i, vector<unsigned int> &R) {
    vector<unsigned int> rem_potential(adj_list_i.size(), 0);

    for (size_t i = 0; i <= (num_vertices_ - 1) / BITS; i ++) {
      rem_potential[i] = adj_list_i[i] & R[i];
    }

    return rem_potential;
  }

  int Clique::CountOneBit(int start, vector<unsigned int> &x) {
    int ret = 0;
    for (size_t i = start; i <= (num_vertices_ - 1) / BITS; i ++) {
      ret = ret + __builtin_popcount(x[i]);
    }
    return ret;
  }

  void Clique::BasicExpand(vector<unsigned int> &rem, unsigned int cur_clique_size) {
    // number of remaining vertices
    int num_rem = CountOneBit(0, rem);

    if (num_rem == 0) {
      if (max_clique_size_ < cur_clique_size) {
	max_clique_size_ = cur_clique_size;
	for (size_t i = 0; i < (num_vertices_ - 1) / BITS; i ++) {
	  cur_max_clique_[i] = cur_clique_[i];
	}
      }
      return;
    }

    if (cur_clique_size + num_rem <= max_clique_size_) {
      return;
    }

    while (num_rem > 0) {
      for (size_t p = 0; p < num_vertices_; p ++)
	if (get_bit(rem[p / BITS], p % BITS)) {
	  if (cur_clique_size + num_rem > max_clique_size_) {
	    set_bit(cur_clique_[p / BITS], p % BITS);
	    vector<unsigned int> rem_potential = Intersect(adj_matrix_[p], rem);
	    BasicExpand(rem_potential, cur_clique_size + 1);
	    clear_bit(cur_clique_[p / BITS], p % BITS);
	  }
	  clear_bit(rem[p / BITS], p % BITS);
	  num_rem --;
	}
    }
  }

  int Clique::VertexColor(vector<unsigned int> &rem, 
			  vector<unsigned int> &col, unsigned int &cur_list_size) {
    vector<unsigned int> color(num_vertices_, 0);
    vector<unsigned int> cur_list(num_vertices_, 0);
    vector<bool> choosed(num_vertices_ + 1, false);
  
    cur_list_size = 0;
    unsigned int cur_color = 0;
    for (size_t i = 0; i < num_vertices_; i ++) {
      if (get_bit(rem[id_deg_[i].first / BITS], id_deg_[i].first % BITS)) {
	cur_list[cur_list_size ++] = id_deg_[i].first;
      }
    }

    for (size_t i = 0; i < cur_list_size; i ++) {
      color[i] = 0;
      for (unsigned int j = 1; j <= cur_color; j ++) {
	choosed[j] = false;
      }
      for (int j = i - 1; j >= 0; j --)
	if (IsConnected(cur_list[i], cur_list[j])) {
	  choosed[ color[j] ] = true;
	}
      for (unsigned int j = 1; j <= cur_color; j ++)
	if (!choosed[j]) {
	  color[i] = j;
	  break;
	}
      if (color[i] == 0) {
	cur_color ++;
	color[i] = cur_color;
      }
    }

    int k = 0;
    for (unsigned int i = 1; i <= cur_color; i ++)
      for (unsigned int j = 0; j < cur_list_size; j ++)
	if (color[j] == i) {
	  col[k ++] = cur_list[j];
	}

    return cur_color;
  }

  void Clique::Expand(vector<unsigned int> &rem, unsigned int cur_clique_size) {
    vector<unsigned int> col(num_vertices_, 0);
    unsigned int cur_list_size;

    int color_num = VertexColor(rem, col, cur_list_size);

    if (cur_list_size == 0) {
      if (max_clique_size_ < cur_clique_size) {
	max_clique_size_ = cur_clique_size;
	for (size_t i = 0; i <= (num_vertices_ - 1) / BITS; i ++) {
	  cur_max_clique_[i] = cur_clique_[i];
	}
      }
      return;
    }

    if (cur_clique_size + color_num <= max_clique_size_) {
      return;
    }

    for (int i = cur_list_size - 1; i >= 0; i --) {
      int p = col[i];
      if (get_bit(rem[p / BITS], p % BITS)) {
	set_bit(cur_clique_[p / BITS], p % BITS);
	vector<unsigned int> rem_potential = Intersect(adj_matrix_[p], rem);

	Expand(rem_potential, cur_clique_size + 1);

	clear_bit(cur_clique_[p / BITS], p % BITS);
	clear_bit(rem[p / BITS], p % BITS);
      }
    }
  }

  int Clique::FindMaxClique() {
    max_clique_.clear(); 
    max_clique_size_ = 0;

    vector<unsigned int> rem(num_vertices_ / BITS + 1, 0);

    for (size_t i = 0; i <= (num_vertices_ - 1) / BITS; i ++) {
      rem[i] = cur_clique_[i] = cur_max_clique_[i] = 0;
    }

    for (size_t i = 0; i < num_vertices_; i ++) {
      if (!colored_[i]) {
	set_bit(rem[i / BITS], i % BITS);
      }
    }
  
    Expand(rem, 0);
 
    for (size_t i = 0; i < num_vertices_; i ++) {
      if (get_bit(cur_max_clique_[i / BITS], i % BITS)) {
	max_clique_.push_back(i);
      }
    }
    max_clique_size_ = max_clique_.size();

    return max_clique_size_;
  }

  void Clique::CliquePartition() {
    clique_list_.clear();
    for (size_t i = 0; i < num_vertices_; i ++) {
      colored_[i] = false;
    }

    // Clique partition by finding MAXIMAL clique each time
    size_t id = 0;
    while (id < num_vertices_) {
      int u = id_deg_[id].first;
      if (colored_[u]) {
	id ++;
	continue;
      }

      vector<int> new_clique;
      new_clique.push_back(u);

      for (size_t i = id + 1; i < num_vertices_; i ++) {
	int v = id_deg_[i].first;
	if (colored_[v]) continue;
	bool ok = true;
	for (size_t j = 0; j < new_clique.size(); j ++)
	  if (!IsConnected(new_clique[j], v)) {
	    ok = false;
	    break;
	  }
	if (ok) {
	  new_clique.push_back(v);
	}
      }

      for (size_t i = 0; i < new_clique.size(); i ++) {
	colored_[new_clique[i]] = true;
      }
      clique_list_.push_back(new_clique);
    }

    for (size_t i = 0; i < num_vertices_; i ++) {
      colored_[i] = false;
    }
  }

}
