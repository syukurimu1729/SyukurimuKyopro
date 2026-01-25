
// ---------- 素因数分解 ----------
static inline ull mul_mod(ull a, ull b, ull mod) {
    return (ull)((__uint128_t)a * b % mod);
}

static inline ull pow_mod(ull a, ull d, ull mod) {
    ull r = 1;
    while (d) {
        if (d & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return r;
}

static bool is_prime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}) {
        if (n % p == 0) return n == p;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    const ull bases[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    for (ull a : bases) {
        if (a % n == 0) continue;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false; // 分解可能 -> 合成数
    }
    return true;
}

static mt19937_64 __pf_rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

static ull pollards_rho(ull n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    ull c = uniform_int_distribution<ull>(1, n-1)(__pf_rng);
    ull y = uniform_int_distribution<ull>(2, n-1)(__pf_rng);
    ull m = min<ull>(128, n-1);
    ull g = 1, r = 1, q = 1;
    ull x = 0, ys = 0;
    auto f = [&](ull v){ return (mul_mod(v, v, n) + c) % n; };
    while (g == 1) {
        x = y;
        for (ull i = 0; i < r; ++i) y = f(y);
        ull k = 0;
        while (k < r && g == 1) {
            ys = y;
            ull lim = min(m, r - k);
            for (ull i = 0; i < lim; ++i) {
                y = f(y);
                ull diff = x > y ? x - y : y - x;
                q = mul_mod(q, diff, n);
                if (q == 0) break;
            }
            g = gcd(q, n);
            k += lim;
        }
        r <<= 1;
    }
    if (g == n) {
        do {
            ys = f(ys);
            ull diff = x > ys ? x - ys : ys - x;
            g = gcd(diff, n);
        } while (g == 1);
    }
    return g;
}

static void factor_rec(ull n, vc<ull>& facs) {
    if (n == 1) return;
    if (is_prime(n)) {
        facs.pb(n);
        return;
    }
    ull d = n;
    while (d == n) d = pollards_rho(n);
    factor_rec(d, facs);
    factor_rec(n / d, facs);
}

// public: 与えられた unsigned long long を素因数分解して (prime, count) のリストを返す
vc<pair<ull,int>> factorize(ull n) {
    vc<pair<ull,int>> res;
    if (n <= 1) return res;
    vc<ull> facs;
    factor_rec(n, facs);
    sort(all(facs));
    for (size_t i = 0; i < facs.size();) {
        size_t j = i;
        while (j < facs.size() && facs[j] == facs[i]) ++j;
        res.emplace_back(facs[i], int(j - i));
        i = j;
    }
    return res;
}
// ---------- ここまで ----------