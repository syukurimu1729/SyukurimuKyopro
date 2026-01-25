
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
    Point& operator++() {
        ++x;
        ++y;
        return *this;
    }

    Point operator++(int) {
        Point tmp = *this;
        ++(*this);
        return tmp;
    }

    Point& operator--() {
        --x;
        --y;
        return *this;
    }
    Point operator--(int) {
        Point tmp = *this;
        --(*this);
        return tmp;
    }
    Point operator*(const Point& o) const { return Point(x * o.x, y * o.y); }
    Point& operator*=(const Point& o) { x *= o.x; y *= o.y; return *this; }
    bool operator<(const Point& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator>(const Point& o) const {
        return o < *this;
    }
    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
    friend istream& operator>>(istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    void swap(){
        std::swap(x,y);
    }
    ll Ydist(const Point& o) const {
        ll dx = x - o.x;
        ll dy = y - o.y;
        return dx*dx + dy*dy;
    }
    ll Udist(const Point& o) const {
        ll dx = x - o.x;
        ll dy = y - o.y;
        return abs(dx)+abs(dy);
    }
};

const Point fnear[4] = {{-1ll,0ll},{0ll,1ll},{1ll,0ll},{0ll,-1}};

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

// --- マクロ: 簡潔な forEach 呼び出し ---
// 使い方:
//   FE(a,p,v { cin >> v; });        // a.forEach([&](Point p, auto& v){ cin >> v; });
//
// 注意:
// - ラムダ内で `return;` を書けば（void ラムダ）そのイテレーションで終わり（続行）
// - `return 0;` を書けば（整数戻り値のラムダ）そのイテレーションは続行（0 = continue相当）
// - `return 1;` を書けば（整数戻り値のラムダ）forEach 全体を抜けます（1 = break相当）
// - C++ のラムダの戻り型推論ルールに従うため、例えばある分岐で値付き return を書く場合は
//   全ての制御経路で値を返すようにする必要あり
#define FE(PNAME, VNAME, BODY) forEach([&](Point PNAME, auto& VNAME) BODY )

template<typename T>
struct Grid2D {
    using size_type = size_t;

private:
    vector<T> data_;
    size_type height_ = 0;
    size_type width_  = 0;

public:
    T dummy;

    // --- Proxy: Grid の要素への "中間オブジェクト" ---
    struct Proxy {
        Grid2D *parent;
        bool inbound;
        size_type idx;

        Proxy(Grid2D *p, long long y, long long x) noexcept
            : parent(p), inbound(p->inBounds(y, x)),
              idx(inbound ? static_cast<size_type>(y) * p->width_ + static_cast<size_type>(x) : 0) {}
        operator T&() noexcept {
            return inbound ? parent->data_[idx] : parent->dummy;
        }
        operator const T&() const noexcept {
            return inbound ? parent->data_[idx] : parent->dummy;
        }
        Proxy& operator=(const T &v) noexcept {
            if (inbound) parent->data_[idx] = v;
            return *this;
        }
        Proxy& operator+=(const T &v) noexcept {
            if (inbound) parent->data_[idx] += v;
            return *this;
        }
        Proxy& operator-=(const T &v) noexcept {
            if (inbound) parent->data_[idx] -= v;
            return *this;
        }
        T& get() noexcept { assert(inbound); return parent->data_[idx]; }
        const T& get() const noexcept { assert(inbound); return parent->data_[idx]; }
    };

    Grid2D() noexcept : data_(), height_(0), width_(0), dummy(T()) {}
    Grid2D(long long h, long long w, T init = T(), T dummy_val = T())
        : data_(), height_(0), width_(0), dummy(dummy_val) {
        resize(h, w, init);
    }
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
    long long pth(Point p) const noexcept {
        if (!inBounds(p)) return -1;
        return static_cast<long long>(p.y) * static_cast<long long>(width_) + static_cast<long long>(p.x);
    }
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
    const T& operator[](const Point& p) const noexcept {
        if (inBounds(p)) return data_[static_cast<size_type>(p.y) * width_ + static_cast<size_type>(p.x)];
        return dummy;
    }
    const T& operator[](const pair<ll,ll>& pp) const noexcept {
        long long x = pp.first, y = pp.second;
        if (inBounds(y, x)) return data_[static_cast<size_type>(y) * width_ + static_cast<size_type>(x)];
        return dummy;
    }

    vector<Point> neighbors(Point p) const {
        vector<Point> res;
        res.reserve(4);
        const long long px = p.x, py = p.y;
        if (inBounds(py + 1, px)) res.emplace_back(px, py + 1);
        if (inBounds(py - 1, px)) res.emplace_back(px, py - 1);
        if (inBounds(py, px + 1)) res.emplace_back(px + 1, py);
        if (inBounds(py, px - 1)) res.emplace_back(px - 1, py);
        return res;
    }

    // --- forEach: 単一テンプレート + if constexpr 方式 ---
    // - Point を値渡しする（ユーザーの希望に合わせる）
    // - ラムダが void を返す場合は普通に実行
    // - ラムダが整数を返す場合は戻り値を検査（0: 続行, 非0: 早期終了）
    template <typename F, typename Ret = invoke_result_t<F, Point, T&>>
    void forEach(F f) {
        for (size_type y = 0; y < height_; ++y) {
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                Point p{static_cast<long long>(x), static_cast<long long>(y)};
                if constexpr (is_void_v<Ret>) {
                    f(p, data_[base + x]);
                    // return; は呼び出し元ラムダ内でそのイテレーションを終えるだけ
                } else if constexpr (is_integral_v<Ret>) {
                    // 整数を返すラムダ（例: return 0; -> 続行, return 1; -> 早期終了）
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
    long long countIf(Pred p) const noexcept {
        long long cnt = 0;
        for (const auto &v : data_) if (p(v)) ++cnt;
        return cnt;
    }

    template <typename Pred>
    vector<Point> positionIf(Pred p) const {
        vector<Point> out;
        out.reserve(16);
        for (size_type y = 0; y < height_; ++y) {
            size_type base = y * width_;
            for (size_type x = 0; x < width_; ++x) {
                if (p(data_[base + x])) out.emplace_back(static_cast<long long>(x), static_cast<long long>(y));
            }
        }
        return out;
    }

    // rotate90: 90度回転（clockwise）
    void rotate90() {
        if (height_ == 0 || width_ == 0) return;
        size_type nh = width_, nw = height_;
        vector<T> newdata;
        newdata.resize(nh * nw);
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
            debug(oss.str());
        }
    }

private:
    template<typename U = T>
    static typename enable_if<is_streamable<U>::value, void>::type
    printValue(ostream& os, const U& v) {
        os << v;
    }

    template<typename U = T>
    static typename enable_if<!is_streamable<U>::value, void>::type
    printValue(ostream& os, const U&) {
        os << "<" << typeid(U).name() << ">";
    }
};

template<typename T>
ostream& operator<<(ostream& os, const Grid2D<T>& g) {
    g.print();
    return os;
}
