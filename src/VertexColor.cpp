#include "VertexColor.h"

namespace ngclique {

  VertexColor::VertexColor() {
    id_deg_.clear();
  }

  VertexColor::VertexColor(Graph &graph) {
    vector< vector<int> > adj_list = graph.adj_list();
    if (adj_list.size() == 0) {
      cout << "Error: empty adjacent list." << endl;
      return;
    }

    num_vertices_ = adj_list.size();
    for (size_t i = 0; i < num_vertices_; i ++) {
      adj_matrix_.push_back(vector<unsigned int>(num_vertices_ / BITS + 1, 0));
    }

    for (size_t i = 0; i < num_vertices_; i ++) {
      id_deg_.push_back(pair<int, int>(i, adj_list[i].size()));
      for (unsigned int j = 0; j <= (num_vertices_ - 1) / BITS; j ++) {
	adj_matrix_[i][j] = 0;
      }
    }

    sort(id_deg_.begin(), id_deg_.end(), comp);

    for (size_t i = 0; i < num_vertices_; i ++) {
      color_.push_back(-1);
      cur_color_.push_back(-1);
      dsatur_.push_back(0);

      for (size_t t = 0; t < adj_list[i].size(); t ++) {
	int j = adj_list[i][t];
	set_bit(adj_matrix_[i][j / BITS], j % BITS);
      }
    }

    HeuristicColoring();

    cout << "Heuristic result: " << best_color_num_ << endl;

    Clique clique(graph);

    vector<int> initial_list = clique.max_clique();
 
    for (size_t i = 0; i < initial_list.size(); i ++) {
      cur_color_[initial_list[i]] = i;
      for (size_t j = 0; j < num_vertices_; j ++)
	if (IsConnected(initial_list[i], j)) {
	  dsatur_[j] ++;
	}
    }
    cur_used_color_ = initial_list.size();

  }

  VertexColor::~VertexColor() {
    id_deg_.clear();
  }

  bool VertexColor::IsConnected(int i, int j) {
    return (get_bit(adj_matrix_[i][j / BITS], j % BITS) == 1);
  }

  // uu can be colored by color j
  bool VertexColor::IsPossible(int uu, int j) {
    for (size_t i = 0; i < num_vertices_; i ++)
      if (cur_color_[i] != -1 && IsConnected(i, uu) && cur_color_[i] == j) {
	return false;
      }
    return true;
  }

  void VertexColor::Update(int uu, int t) {
    for (size_t i = 0; i < num_vertices_; i ++)
      if (IsConnected(i, uu)) {
	dsatur_[i] += t;
      }
  }

  void VertexColor::HeuristicColoring() {
    int cur_color_num = 0;
    for (size_t i = 0; i < num_vertices_; i ++) {
      int u = id_deg_[i].first;
      color_[u] = -1;
      bool Used[MAX_NUMBER_OF_VERTICES];
      for (int j = 0; j < cur_color_num; j ++) {
	Used[j] = false;
      }
      for (size_t j = 0; j < i; j ++) {
	int v = id_deg_[j].first;
	if (IsConnected(u, v)) {
	  Used[color_[v]] = true;
	}
      }
      for (int j = 0; j < cur_color_num; j ++)
	if (!Used[j]) {
	  color_[u] = j;
	  break;
	}
      if (color_[u] == -1) {
	cur_color_num ++;
	color_[u] = cur_color_num - 1;
	vector<int> newColor;
	newColor.push_back(u);
      }
    }
    best_color_num_ = cur_color_num;
  }

  void VertexColor::BbColoring(int remain, int cur_used_color_) {
    if (remain <= 0) {
      if (cur_used_color_ < best_color_num_) {
	best_color_num_ = cur_used_color_;
	cout << "New val: " << best_color_num_ << endl;
	for (size_t i = 0; i < num_vertices_; i ++) {
	  color_[i] = cur_color_[i];
	}
      }
      return;
    }

    if (cur_used_color_ >= best_color_num_) return;

    int max_dsatur = -1;
    int uu = -1;
    for (size_t i = 0; i < num_vertices_; i ++) {
      int u = id_deg_[i].first;
      if (cur_color_[u] != -1) continue;
      if (dsatur_[u] > max_dsatur) {
	max_dsatur = dsatur_[u];
	uu = u;
      }
    }
    for (int j = 0; j < cur_used_color_ + 1; j ++) 
      if (IsPossible(uu, j)) {
	cur_color_[uu] = j;
	Update(uu, 1);
	BbColoring(remain - 1, max(cur_used_color_, j + 1));

	cur_color_[uu] = -1;

	Update(uu, -1);
      }
  }

  void VertexColor::Coloring() {
    // Find maximum clique in the given graph to determine initial colors
    int remain = num_vertices_ - cur_used_color_;
    BbColoring(remain, cur_used_color_);
  }

  vector< vector<int> > VertexColor::GetColorList() {
    Coloring();

    vector< vector<int> > color_list;
    for (int i = 0; i < best_color_num_; i ++) {
      vector<int> new_color;
      color_list.push_back(new_color);
    }

    for (size_t i = 0; i < num_vertices_; i ++) {
      color_list[color_[i]].push_back(i);
    }

    return color_list;
  }

}
