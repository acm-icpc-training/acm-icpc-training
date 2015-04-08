#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1.0E-9;
const double PI = atan(1) * 4;

struct Circle {
  double x, y, r;
};

struct Double2D {
  double x, y;
  Double2D operator-(const Double2D& p) const {
    return Double2D({x - p.x, y - p.y});
  }
  double Norm2() const {
    return x * x + y * y;
  }
};

struct Edge {
  int from, to;
  bool used;
  Edge(int in_from, int in_to) : from(in_from), to(in_to), used(false) {}
};

double CrossProduct(const Double2D& a, const Double2D& b) {
  return a.x * b.y - a.y * b.x;
}

double DotProduct(const Double2D& a, const Double2D& b) {
  return a.x * b.x + a.y * b.y;
}

// NOTE: This does not handle on-edge cases.
bool Contains(const vector<Double2D>& polygon, const Double2D& p) {
    const int n = polygon.size();
    bool res = false;
    for (int i = 0; i < n; ++i) {
        Double2D v1 = polygon[i] - p, v2 = polygon[(i + 1) % n] - p;
        if(v1.y > v2.y) swap(v1, v2);
        if(v1.y < EPS && EPS < v2.y && CrossProduct(v1, v2) > EPS) res = !res;
    }
    return res;
}

// The range is [0, 2 * PI).
double Arg(const Double2D& p1, const Double2D& p2, const Double2D& o) {
  const auto& v01 = p1 - o, v02 = p2 - o;
  double arg = atan2(CrossProduct(v01, v02), DotProduct(v01, v02));
  if (arg < 0) arg += 2 * PI;
  return arg;
}

double Square(double x) {
  return x * x;
}

class Main {
 private:
  int n, m;
  vector<Circle> circles;
  vector<Double2D> ps, qs;
  vector<int> skipped;
  vector<vector<Edge>> graph;
  vector<vector<Double2D>> faces;

  Double2D Center(int i) {
    return Double2D({circles[i].x, circles[i].y});
  }

  double Radius(int i) {
    return circles[i].r;
  }

  void MarkEdge(int from, int to) {
    for (auto& edge : graph[from]) {
      if (edge.to == to) edge.used = true;
    }
  }

  vector<int> GetEnclosingCircles(const Double2D& p) {
    vector<int> ret;
    for (int i = 0; i < n; ++i) {
      const auto& d = p - Center(i);
      double r = circles[i].r;
      if (d.Norm2() < r * r) ret.push_back(i);
    }
    return ret;
  }

  void ConstructGraph() {
    graph.assign(n, vector<Edge>());
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        if (skipped[i] || skipped[j]) continue;
        double d2 = (Center(i) - Center(j)).Norm2();
        double r2 = Square(Radius(i) + Radius(j));
        if (d2 < r2) graph[i].push_back(Edge(i, j));
      }
    }
  }

  void RemoveIsolatedPathsDFS(int v) {
    int count = 0;
    for (const auto& edge : graph[v]) {
      if (!edge.used) ++count;
    }
    if (count != 1) return;

    for (auto& edge : graph[v]) {
      if (!edge.used) {
        int u = edge.to;
        edge.used = true;
        MarkEdge(u, v);

        RemoveIsolatedPathsDFS(u);
      }
    }
  }

  void RemoveIsolatedPaths() {
    for (int i = 0; i < n; ++i) {
      RemoveIsolatedPathsDFS(i);
    }
  }

  void FindFace(const Edge& start_edge) {
    int start_vertex = start_edge.from;
    int v1 = start_edge.from; auto p1 = Center(v1);
    int v2 = start_edge.to; auto p2 = Center(v2);
    MarkEdge(v1, v2);
    vector<int> vertexes({v1, v2});

    while (true) {
      double max_arg = 0;
      int max_arg_v3 = -1;
      for (const auto& edge : graph[v2]) {
        if (edge.used) continue;
        if (edge.to == v1) continue;
        int v3 = edge.to;
        Double2D p3 = Center(v3);
        if (Arg(p1, p3, p2) > max_arg) {
          max_arg = Arg(p1, p3, p2);
          max_arg_v3 = v3;
        }
      }

      if (max_arg_v3 == -1) {
        cout << "This should not happen!" << endl;
        exit(1);
      }

      v1 = v2; p1 = Center(v1);
      v2 = max_arg_v3; p2 = Center(v2);
      MarkEdge(v1, v2);
      if (v2 == start_vertex) break;
      vertexes.push_back(v2);
    }

    vector<Double2D> face;
    for (int v : vertexes) {
      face.push_back(Center(v));
    }
    faces.push_back(face);
  }

  void ConstructFaces() {
    // We skip centers of circles which share a center with another circle and
    // smaller than it. The purpose is to remove vertexes with the same
    // coordinates in a planar graph.
    skipped.assign(n, false);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        if (circles[i].x == circles[j].x && circles[i].y == circles[j].y &&
            circles[i].r < circles[j].r) {
          skipped[i] = true;
        }
      }
    }

    ConstructGraph();
    RemoveIsolatedPaths();

    for (int i = 0; i < n; ++i) {
      for (auto& edge : graph[i]) {
        if (!edge.used) FindFace(edge);
      }
    }
  }

  vector<int> GetEnclosingFaces(const Double2D& p) {
    vector<int> ret;
    for (int i = 0; i < faces.size(); ++i) {
      if (Contains(faces[i], p)) ret.push_back(i);
    }
    return ret;
  }

  bool SolveQuery(const Double2D& p, const Double2D& q) {
    vector<int> p_circles = GetEnclosingCircles(p);
    vector<int> q_circles = GetEnclosingCircles(q);
    if (!p_circles.empty() || !q_circles.empty()) {
      return p_circles == q_circles;
    }
    vector<int> p_faces = GetEnclosingFaces(p);
    vector<int> q_faces = GetEnclosingFaces(q);
    return p_faces == q_faces;
  }

 public:
  bool ProcessCase() {
    cin >> n >> m;
    if (n == 0 && m == 0) return false;
    for (int i = 0; i < n; ++i) {
      double x, y, r;
      cin >> x >> y >> r;
      circles.push_back(Circle({x, y, r}));
    }
    for (int i = 0; i < m; ++i) {
      double px, py, qx, qy;
      cin >> px >> py >> qx >> qy;
      ps.push_back(Double2D({px, py}));
      qs.push_back(Double2D({qx, qy}));
    }

    ConstructFaces();

    for (int i = 0; i < m; ++i) {
      if (i > 0) cout << " ";
      cout << (SolveQuery(ps[i], qs[i]) ? "YES" : "NO");
    }
    cout << endl;
    return true;
  }
};

int main() {
  while (Main().ProcessCase()) {}
  return 0;
}
