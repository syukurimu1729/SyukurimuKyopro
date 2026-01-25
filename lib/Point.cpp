
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