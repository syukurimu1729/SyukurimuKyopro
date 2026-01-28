// ---------------- Point ----------------
struct Point {
    ll x, y;
    Point(ll x=0, ll y=0): x(x), y(y){}
    Point(const pair<ll,ll>& p): x(p.first), y(p.second){}
    operator pair<ll,ll>() const { return {x, y};}
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y);}    
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y);}    
    Point operator+(const pair<ll,ll>& o) const { return Point(x + o.first, y + o.second);}    
    friend Point operator+(const pair<ll,ll>& a, const Point& b) { return Point(a.first + b.x, a.second + b.y);}    
    Point& operator+=(const Point& o) { x += o.x; y += o.y; return *this; }
    Point& operator+=(const pair<ll,ll>& o) { x += o.first; y += o.second; return *this; }
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Point& o) const { return !(*this == o); }
    Point& operator++() { ++x; ++y; return *this; }
    Point operator++(int) { Point tmp = *this; ++(*this); return tmp; }
    Point& operator--() { --x; --y; return *this; }
    Point operator--(int) { Point tmp = *this; --(*this); return tmp; }
    Point operator*(const Point& o) const { return Point(x * o.x, y * o.y); }
    Point& operator*=(const Point& o) { x *= o.x; y *= o.y; return *this; }
    bool operator<(const Point& o) const { return x < o.x || (x == o.x && y < o.y); }
    bool operator>(const Point& o) const { return o < *this; }
    friend ostream& operator<<(ostream& os, const Point& p) { return os << "(" << p.x << "," << p.y << ")"; }
    friend istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }
    void swap(){ std::swap(x,y); }
    ll Ydist(const Point& o) const { ll dx = x - o.x; ll dy = y - o.y; return dx*dx + dy*dy; }
    ll Udist(const Point& o) const { ll dx = x - o.x; ll dy = y - o.y; return llabs(dx)+llabs(dy); }
};

const Point fnear[4] = {{-1ll,0ll},{0ll,1ll},{1ll,0ll},{0ll,-1}};

// ---------------- is_streamable helper ----------------
template<typename U>
struct is_streamable {
private:
    template<typename T>
    static auto test(int) -> decltype( declval<ostream&>() << declval<const T&>(), true_type{} );
    template<typename>
    static false_type test(...);
public:
    static constexpr bool value = decltype(test<U>(0))::value;
};

// ---------------- FE macro (forEach shortcut) ----------------
#define FE(PNAME, VNAME, BODY) forEach([&](Point PNAME, auto& VNAME) BODY )

// ---------------- Grid2D ----------------
template<typename T>
struct Grid2D {
    using size_type = size_t;

private:
    vector<T> data_;
    size_type height_ = 0;
    size_type width_  = 0;

public:
    T dummy;

    struct Proxy {
        Grid2D *parent;
        bool inbound;
        size_type idx;

        Proxy(Grid2D *p, long long y, long long x) noexcept
            : parent(p), inbound(p->inBounds(y, x)),
              idx(inbound ? static_cast<size_type>(y) * p->width_ + static_cast<size_type>(x) : 0) {}
        operator T&() noexcept { return inbound ? parent->data_[idx] : parent->dummy; }
        operator const T&() const noexcept { return inbound ? parent->data_[idx] : parent->dummy; }
        Proxy& operator=(const T &v) noexcept { if (inbound) parent->data_[idx] = v; return *this; }
        Proxy& operator+=(const T &v) noexcept { if (inbound) parent->data_[idx] += v; return *this; }
        Proxy& operator-=(const T &v) noexcept { if (inbound) parent->data_[idx] -= v; return *this; }
        T& get() noexcept { assert(inbound); return parent->data_[idx]; }
        const T& get() const noexcept { assert(inbound); return parent->data_[idx]; }
    };

    Grid2D() noexcept : data_(), height_(0), width_(0), dummy(T()) {}
    Grid2D(long long h, long long w, T init = T(), T dummy_val = T()) : data_(), height_(0), width_(0), dummy(dummy_val) { resize(h, w, init); }
    void resize(long long h, long long w, T init = T()) {
        if (h < 0 || w < 0) { height_ = width_ = 0; data_.clear(); return; }
        height_ = static_cast<size_type>(h);
        width_  = static_cast<size_type>(w);
        data_.assign(height_ * width_, init);
    }
    long long height() const noexcept { return static_cast<long long>(height_); }
    long long width()  const noexcept { return static_cast<long long>(width_); }
    bool inBounds(long long y, long long x) const noexcept {
        if (y < 0 || x < 0) return false;
        return (static_cast<size_type>(y) < height_) && (static_cast<size_type>(x) < width_);
    }
    bool inBounds(Point p) const noexcept { return inBounds(p.y, p.x); }
    long long pth(Point p) const noexcept { if (!inBounds(p)) return -1; return static_cast<long long>(p.y) * static_cast<long long>(width_) + static_cast<long long>(p.x); }
    Point htp(long long h) const noexcept {
        if (h < 0) return Point{-1, -1};
        const unsigned long long uh = static_cast<unsigned long long>(h);
        const unsigned long long total = static_cast<unsigned long long>(height_) * static_cast<unsigned long long>(width_);
        if (uh >= total) return Point{-1, -1};
        long long y = static_cast<long long>(uh / static_cast<unsigned long long>(width_));
        long long x = static_cast<long long>(uh % static_cast<unsigned long long>(width_));
        return Point{x, y};
    }
    Proxy operator[](Point p) noexcept { return Proxy(this, p.y, p.x); }
    Proxy operator[](const pair<ll,ll>& pp) noexcept { return Proxy(this, pp.second, pp.first); }
    const T& operator[](const Point& p) const noexcept { if (inBounds(p)) return data_[static_cast<size_type>(p.y) * width_ + static_cast<size_type>(p.x)]; return dummy; }
    const T& operator[](const pair<ll,ll>& pp) const noexcept { long long x = pp.first, y = pp.second; if (inBounds(y, x)) return data_[static_cast<size_type>(y) * width_ + static_cast<size_type>(x)]; return dummy; }

    vector<Point> neighbors(Point p) const {
        vector<Point> res; res.reserve(4);
        const long long px = p.x, py = p.y;
        if (inBounds(py + 1, px)) res.emplace_back(px, py + 1);
        if (inBounds(py - 1, px)) res.emplace_back(px, py - 1);
        if (inBounds(py, px + 1)) res.emplace_back(px + 1, py);
        if (inBounds(py, px - 1)) res.emplace_back(px - 1, py);
        return res;
    }

    template <typename F, typename Ret = invoke_result_t<F, Point, T&>>
    void forEach(F f) {
        for (size_type y = 0; y < height_; ++y) {
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                Point p{static_cast<long long>(x), static_cast<long long>(y)};
                if constexpr (is_void_v<Ret>) {
                    f(p, data_[base + x]);
                } else if constexpr (is_integral_v<Ret>) {
                    Ret r = f(p, data_[base + x]);
                    if (r != 0) return;
                }
            }
        }
    }

    template <typename F, typename Ret = invoke_result_t<F, Point, const T&>>
    void forEachConst(F f) const {
        for (size_type y = 0; y < height_; ++y) {
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                Point p{static_cast<long long>(x), static_cast<long long>(y)};
                if constexpr (is_void_v<Ret>) {
                    f(p, data_[base + x]);
                } else if constexpr (is_integral_v<Ret>) {
                    Ret r = f(p, data_[base + x]);
                    if (r != 0) return;
                }
            }
        }
    }

    template <typename Pred>
    long long countIf(Pred p) const noexcept { long long cnt = 0; for (const auto &v : data_) if (p(v)) ++cnt; return cnt; }

    template <typename Pred>
    vector<Point> positionIf(Pred p) const { vector<Point> out; out.reserve(16); for (size_type y = 0; y < height_; ++y) { size_type base = y * width_; for (size_type x = 0; x < width_; ++x) { if (p(data_[base + x])) out.emplace_back(static_cast<long long>(x), static_cast<long long>(y)); } } return out; }

    void rotate90() {
        if (height_ == 0 || width_ == 0) return;
        size_type nh = width_, nw = height_;
        vector<T> newdata; newdata.resize(nh * nw);
        for (size_type y = 0; y < height_; ++y) {
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                newdata[x * nw + (nh - 1 - y)] = data_[base + x];
            }
        }
        data_.swap(newdata);
        height_ = nh;
        width_  = nw;
    }

    void print() const {
        for (size_type y = 0; y < height_; ++y) {
            ostringstream oss;
            bool first = true;
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                if (!first) oss << ' ';
                first = false;
                printValue(oss, data_[base + x]);
            }
            oss << '\n';
            // debug 代わりに標準出力へ
            cout << oss.str();
        }
    }

    // expose raw data access for advanced usage (const/non-const)
    const vector<T>& raw() const noexcept { return data_; }
    vector<T>& raw() noexcept { return data_; }

private:
    template<typename U = T>
    static typename enable_if<is_streamable<U>::value, void>::type
    printValue(ostream& os, const U& v) { os << v; }

    template<typename U = T>
    static typename enable_if<!is_streamable<U>::value, void>::type
    printValue(ostream& os, const U&) { os << "<" << typeid(U).name() << ">"; }
};

// ---------------- Grid2DGravity: Grid2D を内包し重力機能を付加する ----------------
// 目的: 元の Grid2D を破壊せず（または内部で操作して）"下方向に詰める"操作と
// 横/縦の連続並び検出を提供する軽量ラッパー。

template<typename T>
struct Grid2DGravity {
    Grid2D<T> g;
    T emptyValue;

    Grid2DGravity() : g(), emptyValue(T()) {}
    Grid2DGravity(long long h, long long w, T init = T(), T empty_val = T()) : g(h,w,init, empty_val), emptyValue(empty_val) {}

    void resize(long long h, long long w, T init = T()) { g.resize(h,w,init); }
    long long height() const noexcept { return g.height(); }
    long long width()  const noexcept { return g.width(); }

    // forward Proxy access (読み書き)
    typename Grid2D<T>::Proxy operator[](Point p) noexcept { return g[p]; }
    const T& operator[](Point p) const noexcept { return g[p]; }

    // --- applyGravity: 各列ごとに下に詰める（破壊的） ---
    // isEmptyPred を渡すと emptyValue は無視される
    template<typename EmptyPred = std::function<bool(const T&)>>
    void applyGravity(T empty_val, EmptyPred isEmptyPred = nullptr) noexcept {
        auto isEmpty = [&](const T& v)->bool{ if (isEmptyPred) return isEmptyPred(v); return v == empty_val; };
        if (g.height() <= 0 || g.width() <= 0) return;
        using size_type = typename Grid2D<T>::size_type;
        size_type H = static_cast<size_type>(g.height());
        size_type W = static_cast<size_type>(g.width());
        vector<T>& data = g.raw();

        for (size_type x = 0; x < W; ++x) {
            // write pointer (下から詰める)
            long long write = static_cast<long long>(H) - 1;
            for (long long ry = static_cast<long long>(H) - 1; ry >= 0; --ry) {
                size_type ridx = static_cast<size_type>(ry) * W + x;
                if (!isEmpty(data[ridx])) {
                    size_type widx = static_cast<size_type>(write) * W + x;
                    if (static_cast<long long>(ridx) != static_cast<long long>(widx)) data[widx] = std::move(data[ridx]);
                    --write;
                }
            }
            // fill remaining with empty_val
            for (long long fy = write; fy >= 0; --fy) data[static_cast<size_type>(fy) * W + x] = empty_val;
        }
    }

    // applyGravity() の引数を省略可能にする便利版
    void applyGravity() noexcept { applyGravity(emptyValue, nullptr); }

    // --- findLines: 横/縦の連続した同値列を検出して座標列を返す ---
    // n: 必要個数
    // horiz/vert: 横検出／縦検出
    // 戻り値: 見つかった各列（vector<Point>）の配列
    vector<vector<Point>> findLines(int n, bool horiz = true, bool vert = true) const noexcept {
        auto isEmpty = [&](const T& v){ return v == emptyValue; };
        auto eq = [&](const T& a, const T& b){ return a == b; };
        vector<vector<Point>> out;
        if (n <= 1) {
            if (horiz || vert) {
                out.reserve(static_cast<typename Grid2D<T>::size_type>(g.height() * g.width()));
                for (auto y = 0LL; y < g.height(); ++y) {
                    for (auto x = 0LL; x < g.width(); ++x) {
                        const T &v = g[{x,y}];
                        if (!isEmpty(v)) out.push_back(vector<Point>{ Point{static_cast<long long>(x), static_cast<long long>(y)} });
                    }
                }
            }
            return out;
        }

        using size_type = typename Grid2D<T>::size_type;
        size_type H = static_cast<size_type>(g.height());
        size_type W = static_cast<size_type>(g.width());

        // 横
        if (horiz) {
            for (size_type y = 0; y < H; ++y) {
                size_type base = y * W;
                size_type x = 0;
                while (x < W) {
                    const T &startVal = g.raw()[base + x];
                    if (isEmpty(startVal)) { ++x; continue; }
                    size_type sx = x;
                    size_type ex = x + 1;
                    while (ex < W && !isEmpty(g.raw()[base + ex]) && eq(g.raw()[base + ex], startVal)) ++ex;
                    size_type len = ex - sx;
                    if (static_cast<long long>(len) >= n) {
                        vector<Point> run; run.reserve(len);
                        for (size_type tx = sx; tx < ex; ++tx) run.emplace_back(static_cast<long long>(tx), static_cast<long long>(y));
                        out.emplace_back(std::move(run));
                    }
                    x = ex;
                }
            }
        }

        // 縦
        if (vert) {
            for (size_type x = 0; x < W; ++x) {
                size_type y = 0;
                while (y < H) {
                    const T &startVal = g.raw()[y * W + x];
                    if (isEmpty(startVal)) { ++y; continue; }
                    size_type sy = y;
                    size_type ey = y + 1;
                    while (ey < H && !isEmpty(g.raw()[ey * W + x]) && eq(g.raw()[ey * W + x], startVal)) ++ey;
                    size_type len = ey - sy;
                    if (static_cast<long long>(len) >= n) {
                        vector<Point> run; run.reserve(len);
                        for (size_type ty = sy; ty < ey; ++ty) run.emplace_back(static_cast<long long>(x), static_cast<long long>(ty));
                        out.emplace_back(std::move(run));
                    }
                    y = ey;
                }
            }
        }

        return out;
    }

    // 任意の等価判定 / 空判定を渡す汎用版
    template<typename EqPred, typename EmptyPred>
    vector<vector<Point>> findLinesPred(int n, EqPred eq, EmptyPred isEmpty, bool horiz = true, bool vert = true) const noexcept {
        vector<vector<Point>> out;
        if (n <= 1) {
            if (horiz || vert) {
                out.reserve(static_cast<typename Grid2D<T>::size_type>(g.height() * g.width()));
                for (auto y = 0LL; y < g.height(); ++y) {
                    for (auto x = 0LL; x < g.width(); ++x) {
                        const T &v = g[{x,y}];
                        if (!isEmpty(v)) out.push_back(vector<Point>{ Point{static_cast<long long>(x), static_cast<long long>(y)} });
                    }
                }
            }
            return out;
        }

        using size_type = typename Grid2D<T>::size_type;
        size_type H = static_cast<size_type>(g.height());
        size_type W = static_cast<size_type>(g.width());

        if (horiz) {
            for (size_type y = 0; y < H; ++y) {
                size_type base = y * W;
                size_type x = 0;
                while (x < W) {
                    const T &startVal = g.raw()[base + x];
                    if (isEmpty(startVal)) { ++x; continue; }
                    size_type sx = x, ex = x + 1;
                    while (ex < W && !isEmpty(g.raw()[base + ex]) && eq(g.raw()[base + ex], startVal)) ++ex;
                    size_type len = ex - sx;
                    if (static_cast<long long>(len) >= n) {
                        vector<Point> run; run.reserve(len);
                        for (size_type tx = sx; tx < ex; ++tx) run.emplace_back(static_cast<long long>(tx), static_cast<long long>(y));
                        out.emplace_back(std::move(run));
                    }
                    x = ex;
                }
            }
        }

        if (vert) {
            for (size_type x = 0; x < W; ++x) {
                size_type y = 0;
                while (y < H) {
                    const T &startVal = g.raw()[y * W + x];
                    if (isEmpty(startVal)) { ++y; continue; }
                    size_type sy = y, ey = y + 1;
                    while (ey < H && !isEmpty(g.raw()[ey * W + x]) && eq(g.raw()[ey * W + x], startVal)) ++ey;
                    size_type len = ey - sy;
                    if (static_cast<long long>(len) >= n) {
                        vector<Point> run; run.reserve(len);
                        for (size_type ty = sy; ty < ey; ++ty) run.emplace_back(static_cast<long long>(x), static_cast<long long>(ty));
                        out.emplace_back(std::move(run));
                    }
                    y = ey;
                }
            }
        }

        return out;
    }

    // デバッグ / 出力
    void print() const { g.print(); }
};

// ---------------- ostream for Grid2D ----------------------------------
template<typename T>
ostream& operator<<(ostream& os, const Grid2D<T>& g) { g.print(); return os; }

// ---------------- Example usage --------------------------------------
#ifdef EXAMPLE_GRID2D_GRAVITY
int main(){
    Grid2DGravity<int> gg(4, 6, 0, 0); // 4x6, init=0, empty=0
    // set some blocks
    gg[{1,0}] = 5; gg[{1,1}] = 5; gg[{1,2}] = 5; // a vertical stack
    gg[{3,0}] = 7; gg[{4,0}] = 7; gg[{5,0}] = 7; // horizontal at top row
    cout << "before:\n"; gg.print();
    gg.applyGravity();
    cout << "after gravity:\n"; gg.print();
    auto runs = gg.findLines(3, true, true);
    cerr << "found runs: " << runs.size() << "\n";
    for (auto &r : runs){
        for (auto &p : r) cerr << p << " ";
        cerr << "\n";
    }
}
#endif
