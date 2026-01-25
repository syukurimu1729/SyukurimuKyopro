
template <typename T = ll>
struct Interval {
    T l;
    T r;

    Interval(): l(1), r(0) {}
    Interval(T left, T right): l(left), r(right) {}

    T length() const { return (r > l) ? (r - l) : static_cast<T>(0); }

    bool empty() const { return r <= l; }

    Interval hull(const Interval &o) const { return Interval(min(l, o.l), max(r, o.r)); }
    Interval operator+(const Interval &o) const { return hull(o); }

    Interval intersect(const Interval &o) const {
        T nl = max(l, o.l);
        T nr = min(r, o.r);
        if (nr <= nl) return Interval();
        return Interval(nl, nr);
    }

    bool intersects(const Interval &o) const { return max(l, o.l) < min(r, o.r);}
    bool containsInterval(const Interval &o) const { return !o.empty() && l <= o.l && o.r <= r;}
    bool contains(const T &x) const { return l <= x && x < r;}
    vc<Interval> difference(const Interval &o) const {
        vc<Interval> res;
        if (empty()) return res;
        if (o.empty()) { res.pb(*this); return res; }
        if (!intersects(o)) { res.pb(*this); return res; }
        if (l < o.l) {
            res.pb(Interval(l, min(r, o.l)));
        }
        if (o.r < r) {
            res.pb(Interval(max(l, o.r), r));
        }
        return res;
    }

    Interval shift(T d) const { return Interval(l + d, r + d);}
    Interval clamp(const Interval &bounds) const { return intersect(bounds);}
    bool operator<(const Interval &o) const { return l < o.l || (l == o.l && r < o.r);}
    bool operator==(const Interval &o) const { return l == o.l && r == o.r;}
    bool operator!=(const Interval &o) const { return !(*this == o);}
    pair<T,T> to_pair() const { return {l, r}; }
    string str() const {
        if (empty()) return string("empty");
        ostringstream oss;
        oss << "[" << l << "," << r << ")";
        return oss.str();
    }
};

template<typename T>
ostream& operator<<(ostream &os, const Interval<T> &iv) {
    if (iv.empty()) os << "empty";
    else os << "[" << iv.l << "," << iv.r << ")";
    return os;
}