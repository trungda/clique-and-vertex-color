#include "Graph.h"

Graph::Graph(vector< vector<int> > list) {
  mList.clear();
  mComplementList.clear();
  nVertex = 0;
  if (list.size() == 0) return;
  nVertex = list.size();
  for (int i = 0; i < nVertex; i ++) {
    vector<int> newList;
    for (int j = 0; j < list[i].size(); j ++) {
      newList.push_back(list[i][j]);
    }
    sort(newList.begin(), newList.end());
    mList.push_back(newList);
  }
  calComplementList();
}

Graph::~Graph() {
  for (int i = 0; i < mList.size(); i ++)
    mList[i].clear();
  mList.clear();
  for (int i = 0; i < mComplementList.size(); i ++)
    mComplementList[i].clear();
  mComplementList.clear();
}

void Graph::calComplementList() {
  mComplementList.clear();
  for (int i = 0; i < nVertex; i ++) {
    vector<int> newList;
    bool adjacent[MAX_NUMBER_OF_VERTICES];
    for (int j = 0; j < nVertex; j ++) {
      adjacent[j] = false;
    }
    adjacent[i] = true;
    for (int j = 0; j < mList[i].size(); j ++) {
      adjacent[mList[i][j]] = true;
    }
    for (int j = 0; j < nVertex; j ++) 
      if (!adjacent[j]) {
	newList.push_back(j);
      }
    sort(newList.begin(), newList.end());
    mComplementList.push_back(newList);
  }
}

vector< vector<int> > Graph::getAdjList() {
  return mList;
}

vector< vector<int> > Graph::getComplementAdjList() {
  return mComplementList;
}

bool Graph::isConnected(int i, int j) {
  if (mList[i].size() == 0) return false;
  int lo = 0;
  int hi = mList[i].size() - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (mList[i][mid] == j) return true;
    if (mList[i][mid] > j) hi = mid - 1;
    else lo = mid + 1;
  }
  return false;
}

int Graph::getNumVertices() {
  return nVertex;
}

// helper functions

bool comp(const IdDeg &x, const IdDeg &y) {
  if (x.second > y.second) return true;
  if (x.second < y.second) return false;
  if (x.first < y.first) return true;
  return false;
}

void setBit(unsigned int &x, int i) { 
  x = x | (1 << i);
} 

void clearBit(unsigned int &x, int i) { 
  x = x & (~(1 << i));
} 

unsigned int getBit(unsigned int x, int i) { 
  return ((x & 1 << i) != 0); 
}

