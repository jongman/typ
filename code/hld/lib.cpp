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
#include<functional>
using namespace std;

const int MAXN = 5000;

// Segment tree for point update/range query. Elements of array and results are
// supposed to be the same type. (Can be used for range min, range max, range
// sum, ..)
template<typename T>
struct SimpleSegmentTree {
  int n;
  vector<T> data;
  function<T(T, T)> merge;

  SimpleSegmentTree() {}
  SimpleSegmentTree(int n, function<T(T, T)> merge): n(n), merge(merge) { init(); }
  SimpleSegmentTree(const vector<T>& A, function<T(T,T)> merge): n(A.size()), merge(merge) {
    init();
    init_array(1, 0, n-1, A);
  }

  void init() {
    int sz = 1; while(sz < n) sz *= 2;
    data.resize(sz*2);
  }
  void init_array(int node, int left, int right, const vector<T>& A) {
    if(left == right) data[node] = A[left];
    else {
      init_array(node*2, left, (left + right) / 2, A);
      init_array(node*2+1, (left + right) / 2 + 1, right, A);
      data[node] = merge(data[node*2], data[node*2+1]);
    }
  }

  void set(int pos, T val) { set(pos, val, 1, 0, n-1); }
  void set(int pos, T val, int node, int left, int right) {
    if(left == right) 
      data[node] = val;
    else {
      int mid = (left + right) / 2;
      if(pos <= mid)
        set(pos, val, node*2, left, mid);
      else
        set(pos, val, node*2+1, mid+1, right);
      data[node] = merge(data[node*2], data[node*2+1]);
    }
  }

  bool disjoint(int a, int b, int c, int d) { return b < c || d < a; }
  T query(int lo, int hi) { return query(lo, hi, 1, 0, n-1); }
  T query(int lo, int hi, int node, int left, int right) {
    if(lo <= left && right <= hi) return data[node];
    int mid = (left + right) / 2;
    if(hi <= mid) return query(lo, hi, node*2, left, mid);
    if(mid+1 <= lo) return query(lo, hi, node*2+1, mid+1, right);
    return merge(query(lo, hi, node*2, left, mid),
                 query(lo, hi, node*2+1, mid+1, right));
  }
};

struct SimpleEdge {
  int u, v;

  SimpleEdge(int u=-1, int v=-1): u(u), v(v) {}
  int other(int here) const { return u == here ? v : u; }
};

template<typename EDGE>
struct DecomposedTree {
  typedef vector<EDGE> Edges;

  int V, E, root;
  Edges to_parent;
  vector<Edges> to_children;

  // size of the subtree, and depth of the node
  vector<int> subtree_size, depth;
  // parent[u][i] = follow to_parent link 2**i times from u. where are we?
  vector<vector<int> > exp_ancestor;

  // heavy_paths[i] = list of vertices in a heavy path, INCLUDING the light edge
  // from the highest node of the path to its ancestor (if the highest node is
  // the root of the tree, this is omitted). Those light edges are included so
  // that all edges belong to one heavy path.
  vector<vector<int> > heavy_paths;
  vector<int> heavy_path_index;

  DecomposedTree(int V, int E, int root, const Edges& to_parent, const vector<Edges>& to_children):
      // things we are given
      V(V), E(E), root(root), to_parent(to_parent), to_children(to_children), 
      // things we need to calculate
      subtree_size(V, 1), depth(V, -1), exp_ancestor(V), heavy_paths(), heavy_path_index(V, -1)
  {

    dfs();
    decompose_heavy_light(root);
  }

  void dfs() {
    depth[root] = 0;
    stack<int> st;
    st.push(root);
    vector<int> order;
    // iterative dfs here
    while(!st.empty()) {
      int here = st.top(); st.pop();
      order.push_back(here);

      // calculate exp_ancestor[][]
      if(here != root) {
        exp_ancestor[here].push_back(to_parent[here].other(here));
        for(int log_jump = 0; ; ++log_jump) {
          int arrived = exp_ancestor[here][log_jump];
          if(exp_ancestor[arrived].size() <= log_jump) break;
          int next = exp_ancestor[arrived][log_jump];
          exp_ancestor[here].push_back(next);
        }
      }

      // visit children
      for(const auto& e: to_children[here]) {
        int there = e.other(here);
        st.push(there);
        depth[there] = depth[here] + 1;
      }
    }
    // calculate subtree size (in reverse dfs order)
    for(int i = order.size()-1; i >= 0; --i) {
      int here = order[i];
      for(const auto& e: to_children[here]) {
        int there = e.other(here);
        subtree_size[here] += subtree_size[there];
      }
    }
  }

  int lca(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    int diff = depth[v] - depth[u];
    for(int i = 0; (1<<i) <= diff; ++i) 
      if(diff & (1<<i)) 
        v = exp_ancestor[v][i];

    if(u == v) return u;

    for(int i = exp_ancestor[u].size()-1; i >= 0; --i) 
      if(i < exp_ancestor[u].size() && exp_ancestor[u][i] != exp_ancestor[v][i]) {
        u = exp_ancestor[u][i];
        v = exp_ancestor[v][i];
      }
    return exp_ancestor[u][0];
  }

  // HEAVY LIGHT DECOMPOSITION LIVES HERE
  // ====================================

  int find_heavy_child(int here) {
    for(const auto& e: to_children[here]) {
      int there = e.other(here);
      if(subtree_size[here] <= subtree_size[there] * 2)
        return there;
    }
    return -1;
  }

  void decompose_heavy_light(int here) {
    // start a new path
    int path_index = heavy_paths.size();
    heavy_paths.push_back(vector<int>());

    // add the light edge from the highest node to its parent.
    // (see the rationale above at the definition of heavy_paths)
    if(here != root) 
      heavy_paths[path_index].push_back(to_parent[here].other(here));

    while(true) {
      // add this vertex to the current path
      heavy_paths[path_index].push_back(here);
      heavy_path_index[here] = path_index;

      int heavy_child = find_heavy_child(here);

      // find rest of the children and decompose their subtrees
      for(const auto& e: to_children[here]) 
        if(e.other(here) != heavy_child) 
          decompose_heavy_light(e.other(here));

      // follow the heavy path if there is one
      if(heavy_child == -1) break;
      here = heavy_child;
    }
  }

  int get_heavy_path_root(int here) {
    return heavy_paths[heavy_path_index[here]][0];
  }

  int get_index_in_heavy_path(int here) {
    int root = get_heavy_path_root(here);
    return depth[here] - depth[root];
  }

  template<typename CALLBACK>
  void foreach_path(int ancestor, int descendant, CALLBACK callback, bool foreach_edges=true) {
    if(depth[ancestor] > depth[descendant]) swap(ancestor, descendant);

    while(heavy_path_index[ancestor] != heavy_path_index[descendant]) {
      int path = heavy_path_index[descendant];
      callback(path, 0, get_index_in_heavy_path(descendant));
      descendant = get_heavy_path_root(descendant);
    }

    if(!foreach_edges || ancestor != descendant) {
      int path = heavy_path_index[descendant];
      callback(path, get_index_in_heavy_path(ancestor), get_index_in_heavy_path(descendant));
    }
  }

  template<typename CALLBACK>
  void foreach_path_general(int u, int v, CALLBACK callback, bool foreach_edges=true) {
    int ancestor = lca(u, v);
    foreach_path(ancestor, u, callback, foreach_edges);
    foreach_path(ancestor, v, callback, foreach_edges);
  }
};

DecomposedTree<SimpleEdge> *tree;
vector<SimpleSegmentTree<int>> segment_trees;

DecomposedTree<SimpleEdge>* read_input() {
  int v;
  cin >> v;

  vector<SimpleEdge> to_parent(v);
  vector<vector<SimpleEdge>> to_children(v);
  int dummy;
  cin >> dummy;
  for(int child = 1; child < v; ++child) {
    int par;
    cin >> par;
    to_parent[child] = SimpleEdge(child, par);
    to_children[par].push_back(SimpleEdge(child, par));
  }

  return new DecomposedTree<SimpleEdge>(v, v-1, 0, to_parent, to_children);
}

void update(int u, int v, int cost) {
  tree->foreach_path(u, v, [=](int path_index, int a, int b) {
    assert(a + 1 == b);
    segment_trees[path_index].set(a, cost); 
  });
}

int query(int u, int v) {
  int ret = -1;
  tree->foreach_path_general(u, v, [&](int path_index, int a, int b) {
    ret = max(ret, 
              segment_trees[path_index].query(a, b-1));
  });
  return ret;
}

int main() {
  int cases;
  cin >> cases;
  while(cases--) {
    tree = read_input();
    segment_trees.clear();
    segment_trees.reserve(tree->heavy_paths.size());
    for(const auto& path: tree->heavy_paths) {
      vector<int> ones(path.size()-1, 1);
      segment_trees.push_back(SimpleSegmentTree<int>(ones, [](int a, int b) { return max(a, b); }));
    }

    int queries;
    cin >> queries;
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
        cout << query(u, v) << endl;
      }
    }

    delete tree;
  }
}
