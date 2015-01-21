#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAXN = 50000;

int n; // 정점의 개수
int parent[MAXN]; // 부모 정점의 번호. 루트라면 -1
int weight[MAXN]; // 부모 정점으로 가는 간선의 가중치

// u와 v의 최소 공통 조상(least common ancestor)을 반환한다.
int lca(int u, int v) {
  vector<int> seen(n);
  while(u != -1) { seen[u] = 1; u = parent[u]; }
  while(!seen[v]) { v = parent[v]; }
  return v;
}

// 간선 (u,v)의 가중치를 cost로 갱신한다.
void update(int u, int v, int cost) {
  if(parent[u] == v) swap(u, v);
  assert(parent[v] == u);
  weight[v] = cost;
}

// u와 v를 잇는 간선 중 최대 가중치를 반환한다.
int query(int u, int v) {
  int max_weight = -1;
  int t = lca(u, v);
  while(u != t) { max_weight = max(max_weight, weight[u]); u = parent[u]; }
  while(v != t) { max_weight = max(max_weight, weight[v]); v = parent[v]; }
  return max_weight;
}

struct SegmentTree {
  struct SegmentTreeNode {
    int first, last; // 이 노드가 덮는 구간은 [first, last]이다.
    int max_value; // 이 구간의 최대값
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int first, int last): first(first), last(last), max_value(-1) {
      if(first != last) {
        int mid = (first + last) / 2;
        left = new SegmentTreeNode(first, mid);
        right = new SegmentTreeNode(mid+1, last);
      }
    }

    void update(int pos, int value) {
      // 터미널 노드인 경우 값을 바로 업데이트
      if(first == last)
        max_value = value;
      // 아닌 경우 적절한 가지에 값을 전파하고 구간 최대값을 업데이트 
      else {
        if(pos <= (first + last) / 2)
          left->update(pos, value);
        else
          right->update(pos, value);
        max_value = max(left->max_value, right->max_value);
      }
    }

    int query(int lo, int hi) {
      // [lo,hi]와 [first,last]의 교집합이 없는 경우
      if(hi < first || last < lo) return -1;
      // [lo,hi]가 [first,last]를 포함하는 경우
      if(lo <= first && last <= hi) return max_value;
      // 이외의 경우 각각 나눠 최대값 찾고, 최대치를 반환
      return max(left->query(lo, hi), right->query(lo, hi));
    }
  };

  SegmentTreeNode* root;
  SegmentTree(int n): root(new SegmentTreeNode(0, n-1)) { }

  // pos위치의 값을 value로 바꾼다.
  void update(int pos, int value) { root->update(pos, value); }
  // [lo, hi] 범위의 값 중 최대값을 구한다.
  int query(int lo, int hi) { return root->query(lo, hi); }
};

int main() {
  cin.sync_with_stdio(false);
  int cases;
  cin >> cases;
  while(cases--) {
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> parent[i];
    for(int i = 0; i < n; ++i) weight[i] = 1;
    int queries;
    cin >> queries;
    int ret = 0;
    while(queries--) {
      string op;
      cin >> op;
      if(op == "update") {
        int u, v, cost;
        cin >> u >> v >> cost;
        update(u, v, cost);
      }
      else {
        int u, v;
        cin >> u >> v;
        ret ^= query(u, v);
      }
    }
    cout << ret << endl;
  }
}

