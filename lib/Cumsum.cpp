
template<typename T = ll>
struct CumSum2D {
    ll H, W;
    vv<T> S;
    CumSum2D(ll h = 0, ll w = 0) : H(h), W(w), S(h+1, vc<T>(w+1, 0)) {}

    CumSum2D(const vv<T>& A) {
        H = (ll)A.size();
        W = H ? (ll)A[0].size() : 0;
        S.assign(H+1, vc<T>(W+1, 0));
        for (ll y = 0; y < H; ++y) for (ll x = 0; x < W; ++x) S[y+1][x+1] = A[y][x];
        build();
    }

    void add(ll y, ll x, T v) {
        if (y < 0 || x < 0 || y >= H || x >= W) return;
        S[y+1][x+1] += v;
    }

    void build() {
        for (ll y = 1; y <= H; ++y) {
            for (ll x = 1; x <= W; ++x) {
                S[y][x] += S[y][x-1] + S[y-1][x] - S[y-1][x-1];
            }
        }
    }
    T prefix_sum(ll y, ll x) const {
        if (y < 0 || x < 0) return 0;
        if (y >= H) y = H-1;
        if (x >= W) x = W-1;
        return S[y+1][x+1];
    }
    T sum(ll y0, ll x0, ll y1, ll x1) const {
        if (y0 > y1 || x0 > x1) return 0;
        // clamp
        y0 = max(0LL, min(y0, H-1));
        x0 = max(0LL, min(x0, W-1));
        y1 = max(0LL, min(y1, H-1));
        x1 = max(0LL, min(x1, W-1));
        return S[y1+1][x1+1] - S[y0][x1+1] - S[y1+1][x0] + S[y0][x0];
    }

    T at(ll y, ll x) const {
        return sum(y, x, y, x);
    }
};

// H x W の grid を読み込んで、ある矩形和を取得する例
/*
ll H = 3, W = 4;
vv<ll> A = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
CumSum2D<ll> cs(A);  A から自動で build() される
ll ans = cs.sum(0,1,1,2);
*/
