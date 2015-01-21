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

const int MAXN = 50000;

// 입력으로 주어지는 값들
// ======================

int n; // 정점의 수 
int parent[MAXN]; // 각 정점에 대해 부모의 번호를 저장한다. 루트는 -1
vector<int> children[MAXN]; // 각 정점마다 자식 정점의 목록을 저장한다.

// HLD가 계산하는 값들
// ===================

int subtree_size[MAXN]; // 해당 정점을 루트로 하는 서브트리의 크기 (= 정점의 무게)
int depth[MAXN]; // 트리에서 해당 정점의 깊이. 루트의 깊이는 0.

// 각 무거운 경로마다, 경로에 포함된 정점의 목록. 무거운 경로 맨 위에서 그
// 선조로 가는 가벼운 간선을 포함한다.
vector<vector<int> > heavy_paths; 
// 이 정점에서 부모로 가는 간선을 포함된 무거운 경로의 번호. 
// heavy_paths[] 의 인덱스를 가리킨다.
vector<int> heavy_path_index;

// exp_ancestor[i][j] = i에서 부모로 가는 간선을 2^j번 따라갔을 때 나오는 정점의
// 번호. lca() 를 위해 계산해 둔다.
vector<int> exp_ancestor[MAXN];

// 문제를 풀기 위해 계산하는 값들
// ==============================

// 각 무거운 경로에 해당하는 구간 트리. segment_trees[i]는 heavy_paths[i]에
// 대응된다.
vector<SegmentTree> segment_trees;

// HLD의 구현
// ==========

void dfs(int here) {
  subtree_size[here] = 1;

  // exp_ancestor[here]를 계산한다.
  exp_ancestor[here] = vector<int>(1, parent[here]);
  for(int log_jump = 0; ; ++log_jump) {
    // 2^log_jump번 올라가 만난 정점
    int arrived = exp_ancestor[here][log_jump];
    // 2^log_jump번 더 올라갈 수 없다면 종료
    if(exp_ancestor[arrived].size() <= log_jump) break;
    // 여기서 2^log_jump번 더 올라가면 2^(log_jump+1)번 올라간 셈이 된다.
    int next = exp_ancestor[arrived][log_jump];
    exp_ancestor[here].push_back(next);
  }

  for(int child: children[here]) {
    depth[child] = depth[here] + 1;
    dfs(child);
    subtree_size[here] += subtree_size[child];
  }
}

// depth[]와 subtree_size[]는 이미 계산되어 있다고 가정한다.
void heavy_light_decomposition(int root) {
  // 초기화
  heavy_paths.clear();
  heavy_path_index.resize(n, -1);

  // 너비 우선 탐색을 하며 heavy_paths와 heavy_path_index를 계산한다.
  queue<int> q;
  q.push(root);
  while(!q.empty()) {
    int here = q.front(); 
    q.pop();

    for(int child: children[here])
      q.push(child);

    // here에서 자신의 부모로 올라가는 간선을 적절한 heavy_paths에 추가하자.
    // 우선 here가 트리의 루트라 부모로 올라가는 간선이 없는 경우는 무시한다.
    if(here == root) continue;

    int p = parent[here];

    // here에서 p로 올라가는 간선은 어떤 heavy_paths에 들어가야 할까?
    if(subtree_size[here] * 2 >= subtree_size[p] && p != root) {
      // 1. 이 간선이 무겁다면, 부모에서 끝나는 무거운 경로의 맨 끝에 들어간다.
      // (예외: 부모가 루트인 경우에는 부모에서 끝나는 무거운 경로가 아직
      // 없으므로 새 무거운 경로를 만들어야 한다.)
      int parent_path_index = heavy_path_index[p];
      heavy_paths[parent_path_index].push_back(here);
      heavy_path_index[here] = parent_path_index;
    }
    else {
      // 2. 이 간선이 가볍다면, 이 간선으로 시작하는 새 무거운 경로를 만든다.
      heavy_path_index[here] = heavy_paths.size();
      heavy_paths.push_back(vector<int>(2));
      heavy_paths.back()[0] = p;
      heavy_paths.back()[1] = here;
    }
  }
}

void initialize_trees() {
  segment_trees.clear();
  segment_trees.reserve(heavy_paths.size());
  // 각 무거운 경로마다 구간 트리를 만들고 모든 간선에 대해 값을 1로 지정한다.
  for(const auto& path: heavy_paths) {
    // 경로에 포함된 정점의 개수가 m개일 때, 간선의 개수는 m-1개이다.
    int m = path.size();
    segment_trees.push_back(SegmentTree(m - 1));
    for(int i = 0; i < m-1; ++i)
      segment_trees.back().update(i, 1);
  }
}

int lca(int u, int v) {
  // 편의를 위해, u와 v의 깊이가 같거나 v가 더 아래 있다고 가정한다.
  if(depth[u] > depth[v]) swap(u, v);

  // 우선 u와 v의 깊이가 다르면 같아질 때까지 v를 올린다.
  int diff = depth[v] - depth[u];
  for(int i = 0; (1<<i) <= diff; ++i) 
    if(diff & (1<<i)) 
      v = exp_ancestor[v][i];

  // 만약 이 때 u == v라면 u가 v의 선조.
  if(u == v) return u;

  // u와 v가 같아지지 않는 한도 내에서 최대한 위로 올라간다.
  for(int i = exp_ancestor[u].size()-1; i >= 0; --i) 
    if(i < exp_ancestor[u].size() && exp_ancestor[u][i] != exp_ancestor[v][i]) {
      u = exp_ancestor[u][i];
      v = exp_ancestor[v][i];
    }

  // 위 루프가 종료하면 u와 v는 LCA 바로 아래 위치하게 된다.
  return exp_ancestor[u][0];
}

void read_input() {
  for(int i = 0; i < MAXN; ++i) children[i].clear();

  cin >> n;
  for(int here = 0; here < n; ++here) {
    int par;
    cin >> par;
    parent[here] = par;
    if(par != -1) children[par].push_back(here);
  }
}

// v에서 그 부모로 올라가는 간선은 이 무거운 경로에서 몇 번째의 간선일까?
// 이 경로의 맨 위에 있는 정점의 깊이와 부모의 깊이를 비교하면 쉽게 알 수 있다.
int find_edge_in_path(int path_index, int v) {
  int top_of_path = heavy_paths[path_index][0];
  return depth[parent[v]] - depth[top_of_path];
}

void update(int u, int v, int cost) {
  // 항상 u가 v의 부모이도록 하자.
  if(parent[u] == v) swap(u, v);
  assert(parent[v] == u);

  // (u,v) 가 속한 경로의 번호는?
  int path_index = heavy_path_index[v];
  // (u,v)는 이 경로에서 몇 번째 간선일까? 
  int index_in_path = find_edge_in_path(path_index, v);
  // 이 경로에 대응되는 구간 트리의 해당 원소를 갱신한다.
  segment_trees[path_index].update(index_in_path, cost);
}

// u에서 v로 내려가는 경로 중 최대값을 반환한다.
int query_topdown(int u, int v) {
  // u와 v가 같다면 경로에는 아무 간선도 포함되어 있지 않다.
  if(u == v) return 0;

  // 만약 u와 v가 같은 무거운 경로에 속한다면 구간 트리로 해결 가능
  if(heavy_path_index[u] == heavy_path_index[v]) {
    int path_index = heavy_path_index[u];
    // u에서 그 부모로 올라가는 간선은 [u,v] 구간에 포함되지 않고,
    // 그 다음 간선부터 포함되므로 first_edge에 1을 더해 준다.
    int first_edge = find_edge_in_path(path_index, u) + 1;
    int last_edge = find_edge_in_path(path_index, v);
    return segment_trees[path_index].query(first_edge, last_edge);
  }

  // v에서 부모로 올라가는 간선이 포함된 무거운 경로의 맨 위 정점까지 올라간다.
  int path_index = heavy_path_index[v];
  int top_of_path = heavy_paths[path_index][0];

  // v == top_of_path 인 경우는 없다. 왜일까?
  assert(top_of_path != v);

  int last_edge = find_edge_in_path(path_index, v);
  return max(query_topdown(u, top_of_path),
             segment_trees[path_index].query(0, last_edge));
}

// u와 v를 잇는 경로 중 최대값을 반환한다.
int query(int u, int v) {
  int t = lca(u, v);
  return max(query_topdown(t, u), query_topdown(t, v));
}

int main() {
  cin.sync_with_stdio(false);

  int cases;
  cin >> cases;
  while(cases--) {
    read_input();

    // HLD를 계산한다.
    dfs(0);
    heavy_light_decomposition(0);
    
    // 각 무거운 경로에 대해 구간 트리를 만들어 둔다.
    initialize_trees();

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
