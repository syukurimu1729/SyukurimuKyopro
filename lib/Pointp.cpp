
//aとbの外積を計算する
ll crs(Point a, Point b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

// 凸包を計算する関数を定義
// 入力: vc<Point> g — 任意の順序の点集合
// 出力: 凸包を反時計回りに並べた頂点列（最後の点は開始点を含まない）
vc<Point> convex(vc<Point> g) {
    sort(all(g));
    int n = g.size();
    if (n <= 1) return g;

    sort(all(g));

    vc<Point> lower, upper;
    lower.pb(g[0]); lower.pb(g[1]);
    upper.pb(g[0]); upper.pb(g[1]);

    for (int i = 2; i < n; ++i) {
        while (lower.size() >= 2 &&
               crs(lower[lower.size()-1] - lower[lower.size()-2],
                   g[i] - lower[lower.size()-1]) <= 0) {
            lower.pop_back();
        }
        lower.pb(g[i]);

        while (upper.size() >= 2 &&
               crs(upper[upper.size()-1] - upper[upper.size()-2],
                   g[i] - upper[upper.size()-1]) >= 0) {
            upper.pop_back();
        }
        upper.pb(g[i]);
    }

    vc<Point> hull;
    for (auto &p : lower) hull.pb(p);
    for (int i = (int)upper.size() - 2; i >= 1; --i) hull.pb(upper[i]);
    return hull;
}
