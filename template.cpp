#if !__INCLUDE_LEVEL__
#include __FILE__

//----------------メインコード部分----------------


int main(){
    
}


//----------------メインコード部分----------------

#else
// 以下汎用テンプレ

//ちょっとした呪文みたいなもの。ちょっと便利になる
#include <bits/stdc++.h>
using namespace std; 
#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder; 
#endif
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG //デバッグモードを有効にする
#endif
struct Init { Init() { ios::sync_with_stdio(0); cin.tie(0); } }init;

// QCFium法のpragmaたち
// 定数倍での高速化を図ることができる
// 一方で、どのpragmaも有効化すれば早くなるということはなく、逆にSIMDやunroll-loopsが余計な処理となって悪化する可能性もある
# pragma GCC target("avx")
# pragma GCC optimize("O3")
# pragma GCC optimize("unroll-loops")
//# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

// # pragma GCC target("avx")
// - 自動ベクトル化のサポート(所謂SIMD)
// - 基本的にループなどはベクトル化され高速になる
// # pragma GCC optimize("O3")
// - 最適化オプションをO3にすることで最適化効果を得る
// # pragma GCC optimize("unroll-loops")
// - ループを部分的に展開して内部で複数回まとめて行う...
// - 例えば100回のループを20回ループで1回につき5回まとめて行うようにする
// - 結果ループ変数の処理などにかかる時間の短縮等につながる可能性
//# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// - 浮動小数点が絡むときのSIMD有効化


//変数関連の定義。よく使う変数や、変数型
using ull = unsigned long long;
using ll = long long;
using ld = long double;
using lll = __int128;
const int INF = 1e9;
const ll LINF = 1e18;
const ld pi = acos(-1.0);
const ld rad = pi/180;
const ld dar = 1/rad;
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string digits = "0123456789";
const ll MOD = 1e9 + 7; //よく使うmod値。大きい素数
const ll FIB[] = {1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025};

template <typename T> using vc = vector<T>; //ベクタのエイリアス
template <typename T> using vv = vector<vc<T>>; //2次元ベクタのエイリアス
using vl = vc<ll>; //long long型のベクタ
using vvl = vc<vl>; //long long型の2次元ベクタ 
using vs = vc<string>; //文字列型のベクタ
using vvs = vc<vs>; //文字列型の2次元ベクタ
using vi = vc<int>; //整数型のベクタ
using vvi = vc<vi>; //整数型の2次元ベクタ
using vb = vc<bool>; //真偽値型のベクタ
using vvb = vc<vb>; //真偽値型の2次元ベクタ

using pairl = pair<ll, ll>; //long long型のペア
using paird = pair<double, double>; //double型のペア

using tuplel = tuple<ll,ll,ll>; //ll型のtuple

template<class>
inline constexpr bool always_false = false;

#ifdef __has_include
#if __has_include(<atcoder/modint.hpp>)
using mint = atcoder::modint1000000007; //よく使うmint
using qmint = atcoder::modint998244353; //よく使うmint(特に有理数で多いのでqmint)
#endif
#endif

//マクロの定義。よく使うループや条件分岐などを簡潔に書くためのもの

#define overload5(a,b,c,d,e,name,...) name
#define overload4(a,b,c,d,name,...) name
#define overload3(a,b,c,name,...) name
#define rep(i, x, limit) for (ll i = (ll)x; i < (ll)limit; i++) //普通のrepeat
#define rrep(i, x, limit) for (ll i = (ll)x; i > (ll)limit; i--) //逆順のrepeat
#define REP(i, x, limit) for (ll i = (ll)x; i <= (ll)limit; i++) //普通のrepeat (inclusive)
#define RREP(i, x, limit) for (ll i = (ll)x; i >= (ll)limit; i--) //逆順のrepeat (inclusive)
#define all(x) (x).begin(), (x).end() //コンテナの全要素を取得
#define rall(x) (x).rbegin(), (x).rend() //コンテナの全要素を逆順に取得
#define sp ' ' //スペース
#define el '\n' //改行文字
#define dco ':' //コロン
#define dca ',' //カンマ
#define line "------------------\n"
#define Yes cout << "Yes" << el // Yesと出力
#define No cout << "No" << el // Noと出力
#define yes cout << "yes" << el // yesと出力
#define no cout << "no" << el // noと出力
#define YES cout << "YES" << el // 大文字のYesと出力
#define NO cout << "NO" << el // 大文字のNoと出力
#define YesNo Yes; else No; //条件によってYesまたはNoと出力
#define dame cout << "-1" << el // -1と出力
#define lim(x) if((x)>=LINF)(x)=-1
#define elc cout << el // 改行とキャッシュフラッシュ
#define spc cout << sp // スペースとキャッシュフラッシュ
#define fc cout << flush //即時フラッシュ
#define pb push_back // ベクタに要素を追加
#define eb emplace_back
#define mp make_pair // ペアを作成
#define mt make_tuple //タプルを作成
#define Ecout(x) cout << x << el //xと出力
#define Vcout(x) cout << (x).val() << el //xのval出力
#define Scout(x) cout << x << sp //xの後スペースをつけて出力
#define Dcout(x) cout << setprecision(20) << x << el //小数点20桁保証で出力
#define Fcout(x) cout << x << el << flush //フラッシュ付き出力
#define answer(x) { cout << (x) << el; return; } //xを出力してreturn
#define sq(x) (x*x)
#define bit(x,i) (((x)>>(i))&1) //xのi桁目が1かどうか
#define each1(i,a) for(auto&&i:a)
#define each2(x,y,a) for(auto&&[x,y]:a)
#define each3(x,y,z,a) for(auto&&[x,y,z]:a)
#define each4(w,x,y,z,a) for(auto&&[w,x,y,z]:a)
#define each(...) overload5(__VA_ARGS__,each4,each3,each2,each1)(__VA_ARGS__)
#define elif else if
#define vli(a) {rep(vliai,0,(ll)((a).size()))(a[vliai])=vliai;}
#define tsolve {lc(t);while(t--)solve();}
#define cd(a) (c-'a')
#define dc(d) (d+'a')
#define popcnt(x) (__popcount((unsigned long long)(x)))
#define bitrep(i,n) for(ll i=0;i<(1LL<<(n));i++)

inline bool even(ll x){ return x % 2 == 0; }
inline bool odd(ll x){ return x % 2 != 0; }

template<typename... Args>
void _read(Args&... args) {
    ((cin >> args), ...);
}
template<typename... Args>
void _dec(Args&... args) {
    ((--args), ...);
}

#define lc(...) long long __VA_ARGS__; _read(__VA_ARGS__)

#define ilc(...) long long __VA_ARGS__; _read(__VA_ARGS__); _dec(__VA_ARGS__)

#define sc(...) string __VA_ARGS__; _read(__VA_ARGS__)
#define chc(...) char __VA_ARGS__; _read(__VA_ARGS__)


#define _VC_NARG(...) _VC_NARG_(__VA_ARGS__,8,7,6,5,4,3,2,1)
#define _VC_NARG_(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N
#define _VC_DISPATCH1(x) _VC_##x
#define _VC_DISPATCH(x) _VC_DISPATCH1(x)

#define _VC_1(n,a) vl a((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i]);
#define _VC_2(n,a,b) vl a((size_t)(n)), b((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i]);
#define _VC_3(n,a,b,c) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i]);
#define _VC_4(n,a,b,c,d) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)), d((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i],d[i]);
#define _VC_5(n,a,b,c,d,e) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)), d((size_t)(n)), e((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i],d[i],e[i]);
#define _VC_6(n,a,b,c,d,e,f) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)), d((size_t)(n)), e((size_t)(n)), f((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i],d[i],e[i],f[i]);
#define _VC_7(n,a,b,c,d,e,f,g) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)), d((size_t)(n)), e((size_t)(n)), f((size_t)(n)), g((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i],d[i],e[i],f[i],g[i]);
#define _VC_8(n,a,b,c,d,e,f,g,h) vl a((size_t)(n)), b((size_t)(n)), c((size_t)(n)), d((size_t)(n)), e((size_t)(n)), f((size_t)(n)), g((size_t)(n)), h((size_t)(n)); for(size_t i=0;i<(size_t)(n);++i) _read(a[i],b[i],c[i],d[i],e[i],f[i],g[i],h[i]);

#define vin(n, ...) _VC_DISPATCH(_VC_NARG(__VA_ARGS__))(n, __VA_ARGS__)


// よく使う priority_queue の型エイリアス
template<typename T>
using maxpq = priority_queue<T>;

template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

using maxlpq = maxpq<ll>;
using minlpq = minpq<ll>;

// デバッグ出力関連

void _debug_out() {}

template<class T>
void _debug_out(const T& head) {
    cout << head;
}

template<class T, class U, class... Ts>
void _debug_out(const T& head, const U& next, const Ts&... tail) {
    cout << head;

    bool skip_space = false;

    if constexpr (is_same_v<T, char>) {
        if (head == sp
            || head == '('
            || head == ','
            || head == ':'
            || head == ')'
            || head == el)
        {
            skip_space = true;
        }
    }

    if constexpr (is_same_v<U, char>) {
        if (next == sp 
            || next == '('
            || next == ',' 
            || next == ':' 
            || next == ')'
            || next == el) 
        {
            skip_space = true;
        }
    }

    if (!skip_space) {
        cout << ' ';
    }

    _debug_out(next, tail...);
}

static thread_local int __dbg_depth = 0;
struct DebugScope {
    DebugScope() { if(__dbg_depth++ == 0) cout << "\033[31m"; }
    ~DebugScope() { if(--__dbg_depth == 0) cout << "\033[0m" << flush; }
};

#ifdef LOCAL
  #define fdebug(...)                     \
    do {                                 \
      DebugScope __dbg_guard;            \
      _debug_out(__VA_ARGS__);           \
      cout << flush;           \
    } while(0)
  #define debug(...)                      \
    do {                                 \
      DebugScope __dbg_guard;            \
      _debug_out(__VA_ARGS__);           \
      cout << flush;           \
    } while(0)
#else
  #define fdebug(...) do{}while(0)
  #define debug(...) do{}while(0)
#endif

//templateの定義。よく使う、マクロは表現するのが大変な関数を定義する

/*  関数名          ntodec(const char c)
    説明            char で 文字{0,1,2,...,9,A,B,...,Z} を受け取り、
　　　　　　　　　　　 int で {0,1,2,...9,10,11,...,35}に直して返す。
　　　　　　　　　　　 それ以外の文字が来た場合は-1を返す。
    参考            https://qiita.com/Shiro-san/items/9376c8898a0882482a6a
*/
int ntodec(const char c){
    switch(c){
        case '0': return 0;case '1': return 1;case '2': return 2;case '3': return 3;case '4': return 4;case '5': return 5;case '6': return 6;case '7': return 7;case '8': return 8;case '9': return 9;case 'A': return 10;case 'B': return 11;case 'C': return 12;case 'D': return 13;case 'E': return 14;case 'F': return 15;case 'G': return 16;case 'H': return 17;case 'I': return 18;case 'J': return 19;case 'K': return 20;case 'L': return 21;case 'M': return 22;case 'N': return 23;case 'O': return 24;case 'P': return 25;case 'Q': return 26;case 'R': return 27;case 'S': return 28;case 'T': return 29;case 'U': return 30;case 'V': return 31;case 'W': return 32;case 'X': return 33;case 'Y': return 34;case 'Z': return 35;default : return -1;
    }
}

/*  関数名          decton(const int n)
    説明            int で 数値 0〜35 を受け取り、文字{0,1,2,...,9,A,B,...,Z}に直して char で返す。
　　　　　　　　　　　 それ以外の数字が来た場合は \0 を返す。
    参考            https://qiita.com/Shiro-san/items/9376c8898a0882482a6a
*/
char decton(const int n){
    switch(n){
        case 0: return '0';case 1: return '1';case 2: return '2';case 3: return '3';case 4: return '4';case 5: return '5';case 6: return '6';case 7: return '7';case 8: return '8';case 9: return '9';case 10: return 'A';case 11: return 'B';case 12: return 'C';case 13: return 'D';case 14: return 'E';case 15: return 'F';case 16: return 'G';case 17: return 'H';case 18: return 'I';case 19: return 'J';case 20: return 'K';case 21: return 'L';case 22: return 'M';case 23: return 'N';case 24: return 'O';case 25: return 'P';case 26: return 'Q';case 27: return 'R';case 28: return 'S';case 29: return 'T';case 30: return 'U';case 31: return 'V';case 32: return 'W';case 33: return 'X';case 34: return 'W';case 35: return 'Z';default : return '\0';
    }
}

/*  関数名          pow_ll(long long x, long long n)
    説明            x^n を計算する。long long 対応
    参考            https://qiita.com/Shiro-san/items/9376c8898a0882482a6a
*/
inline long long pow_ll(long long x, long long n){
    long long ret = x;
    if(n==0) return 1;
    for(long long i=1; i<n; i++){
        ret *= x;
    }
    return ret;
}

/*  関数名          base_ntom(string str, int n, int m)
    説明            n 進数で表現された数値を文字列 str で受け取り、m 進数に直して文字列で出力する。
    使用ライブラリ  string
    使用自作関数    ntodec, decton, pow_ll
    制約事項        36進数までの対応。負の値には対応していない。
    参考            https://qiita.com/Shiro-san/items/9376c8898a0882482a6a
*/
string base_ntom(string str, int n, int m){
    unsigned long tmp = 0;
    string ret;

    for(int i=0; i<(ll)str.length(); i++){
        tmp += (unsigned long) ntodec(str[str.length()-1-i]) * pow(n, i);
    }

    if(tmp==0) return "0";
    while(tmp!=0){
        ret = decton(tmp%m) + ret;
        tmp/=m;
    }
    return ret;
}

// 基数のデフォルトは10
long long reverse_number(long long n, long long base = 10) {
  long long reversed_n = 0;
  while (n > 0) {
    reversed_n = reversed_n * base + (n % base);
    n /= base;
  }
  return reversed_n;
}

//配列の中央値(n=偶数であれば左側)を返す
template<class T>
T median(const vector<T>& a) {
    int n = a.size();
    return a[(n - 1) / 2];
}

//xがl<=x<rに収まっているか
template<class T>
bool in(T x, T l, T r){
    return l <= x && x < r;
}

//[l1,r1)と[l2,r2)が交差しているかの判定
template<class T>
bool intersect(T l1, T r1, T l2, T r2){
    return max(l1,l2) < min(r1,r2);
}

// 回文数判定
bool is_palindromic(long long n, long long base = 10) {
  return n==reverse_number(n, base);
}

bool isPalindrome_reverse(const string& str) {
    string reversed_str = str;
    reverse(reversed_str.begin(), reversed_str.end());
    return str == reversed_str;
}

//与えられた整数の深さ(要するに二進法で何桁か)を調べる
int depth(ll n) {
    int d = 0;
    while (true) {
        n >>= 1;
        if (!n) break;
        ++d;
    }
    return d+1;
}

//与えられた整数Kの約数を列挙する
vl divisor(ll k){
    vl ret;
    for(ll i=1;i*i<=k;i++){
        if(k%i!=0ll)continue;
        ret.pb(i);
        if(i!=k/i)ret.pb(k/i);
    }
    sort(all(ret));
    return ret;
}

//与えられた数が素数かの判定を行う
bool isPrime(ll n){
    if(n <= 1) return false;
    for(ll i=2; i*i<=n; i++){
        if(n%i==0) return false;
    }
    return true;
}

//与えられた数が整数の平方数かの判定を行う、また平方根を返す
ll itsSqrt(ll n) {
    vl ds = divisor(n);
    for(auto d:ds){
        if(d*d==n)return d;
    }
    return -1;
}

//a,bのLCMを返す
ll lcm(ll a, ll b){
    return a / gcd(a,b) * b;
}

//二次元配列により構成されたある頂点uから到達可能な頂点、によって定義されるGにuとvを結ぶ無向辺を追加
template <typename G, typename N>
void both_edge(G& graph, N u, N v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

//整数のpowを高速に計算するu
ll int_pow(ll a,ll t){
    ll res = 1;
    rep(i,0,t)res*=a;
    return res;
}

//a^bのmod mを高速に計算する
template<typename T = ll>
T modpow(T a,T b,T m){
    ll p = 1,q = a;
    rep(i,0,64){
        if((b & (1ll<<i))!=0){
            p*=q;p%=m;
        }
        q*=q;q%=m;
    }
    return static_cast<T>(p);
}


//a/bのmod mを逆元を用いて計算する
template<typename T = ll>
T Div(T a,T b,T m){
    return (a*modpow(b,m-2,m))%m;
}

//ncrの計算に必要な階乗の前計算
//なんかまあ...かぶるのを危惧して変な名前にしています
ll ncrinitfact[1<<19],ncrinitfactinv[1<<19];
bool ncrinited;
ll ncrinitmod = 998244353ll;

//ncrの前計算
void ncrinit(ll m = ncrinitmod) {
    ncrinited = true;
    ncrinitmod = m;
	ncrinitfact[0] = 1LL;
	for (int i = 1; i <= 500000; i++) ncrinitfact[i] = (1LL * i * ncrinitfact[i - 1]) % m;
	for (int i = 0; i <= 500000; i++) ncrinitfactinv[i] = Div(1ll, ncrinitfact[i], m);
}

//ncrを返す(また、initを用いてから計算する必要がある)
template<typename T = ll>
T ncr(T n,T r){
    if(!ncrinited)ncrinit(ncrinitmod);
    if(n<r || r<0)return 0;
    return (ncrinitfact[n]*ncrinitfactinv[r]%ncrinitmod)*ncrinitfactinv[n-r]%ncrinitmod;
}

//nexを計算して返す
//nex[i][c] 文字列Sのi文字目以降で、文字cが出現する最小の添え字(存在しないときは文字長N)
template<typename T = ll>
vector<vector<ll> > Calcnex(const string &S) {
    ll n = (ll)S.size();
    vector<vector<ll> > res(n+1, vector<ll>(26, n));
    for (ll i = n-1; i >= 0; --i) {
        for (ll j = 0; j < 26; ++j) res[i][j] = res[i+1][j];
        res[i][S[i]-'a'] = i;
    }
    return res;
}

//与えられたcharを数字に戻す
template<typename T = int>
T ctod(char c) {
    return static_cast<T>(c - '0');
}

// 与えられたstringをlからrでcutする(0index)
// Tはbasic_stringの派生型string, wstring など）
template <typename T>
T cut(const T& s, ll l, ll r) {
    return s.substr(l, r-l+1);
}

//各文字が何回出るかを得る
array<int,26> freq26(const string& s){
    array<int,26> f{};
    for(char c:s) f[cd(c)]++;
    return f;
}

//与えられた整数が2進数で何桁で表現可能か返す
template <typename T>
ll bit_length(T x) {
    if (x == 0) return 0;
    int length = 0;
    using UnsignedT = typename make_unsigned<T>::type;
    UnsignedT val = static_cast<UnsignedT>(x);
    while (val) {
        ++length;
        val >>= 1;
    }
    return length;
}

//累積和
template<class T>
vector<T> prefix_sum(const vector<T>& v){
    vector<T> s(v.size()+1);
    rep(i,0,v.size()) s[i+1] = s[i] + v[i];
    return s;
}

//累積min
template<class T>
vector<T> prefix_min(const vector<T>& v){
    vector<T> p(v.size());
    p[0]=v[0];
    rep(i,1,v.size()) p[i]=min(p[i-1],v[i]);
    return p;
}

//累積max
template<class T>
vector<T> prefix_max(const vector<T>& v){
    vector<T> p(v.size());
    p[0]=v[0];
    rep(i,1,v.size()) p[i]=max(p[i-1],v[i]);
    return p;
}

//aとbの最大値をaに代入する。aがbより小さい場合はtrueを返す
template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
//aとbの最小値をaに代入する。aがbより大きい場合はtrueを返す
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}

//aをbがtrueなら更新する。更新したならtrueを返す
inline bool chtrue(bool &a, bool b) {
    bool compare = (a!=b && b);
    if(compare) a = b;
    return compare;
}
//aをbがfalseなら更新する。更新したらtrueを返す
inline bool chfalse(bool &a, bool b) {
    bool compare = (a!=b && !b);
    if(compare) a = b;
    return compare;
}

// 文字列がすべて大文字であるかを判定する
template <typename StringT>
bool Uppercase(const StringT& str) {
    return all_of(str.begin(), str.end(), [](unsigned char c) {
        return isupper(c);
    });
}

// a~zのsetを返す
template <typename CharType = char>
set<CharType> ABCSet() {
    set<CharType> alphabetSet;
    for (CharType c = 'a'; c <= 'z'; ++c) {
        alphabetSet.insert(c);
    }
    return alphabetSet;
}

//配列にunique処理
template<class T>
void uniq(vector<T>& v){
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

//整数の桁数を返す
ll DigitCount(ll n) {
    if (n == 0) return 1; // 0の桁数は1
    ll count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

//配列の時計回り90度回転
template<typename T>
void rotate90(vv<T>& a) {
    ll n = a.size();
    if (n == 0 || a[0].size() != n) return;
    rep(i, 0, n) rep(j, i + 1, n) swap(a[i][j], a[j][i]);
    rep(i, 0, n) reverse(all(a[i]));
}

//二つの数を絶対値で大小比較(|a|<|b|)
template<typename T>
bool absComp(const T& a, const T& b) {
    return abs(a) < abs(b);
}

// absCompを利用してsort
template<typename T>
void abssort(vector<T>& v, bool descending = false) {
    if (descending) {
        sort(v.begin(), v.end(), [](const T& a, const T& b) {
            return abs(a) > abs(b);
        });
    } else {
        sort(v.begin(), v.end(), [](const T& a, const T& b) {
            return abs(a) < abs(b);
        });
    }
}


//BFS関連

// 4近傍、(一般的に)上右下左
const int dy[4] = {1,0,-1,0};
const int dx[4] = {0,1,0,-1};


// 8方向 左上, 上, 右上, 右, 右下, 下, 左下, 左
const int DY[8] = {-1,-1,-1,0,1,1,1,0};
const int DX[8] = {-1,0,1,1,1,0,-1,-1};

//入出力関連の定義(debugでも使えるようにstd内で定義)
namespace std {
    // pair の入力
    template <class T, class U>
    istream& operator>>(istream& is, pair<T, U>& p) {
        return is >> p.first >> p.second;
    }

    template <class T, class U>
    ostream& operator<<(ostream& os, const pair<T, U>& p) {
        return os << "(" << p.first << "," << p.second << ")";
    }


    // tuple の出力: (a, b, c)
    template <class Tuple, size_t... I>
    void print_tuple_impl(const Tuple& t, index_sequence<I...>) {
        cout << "(";
        ((cout << (I == 0 ? "" : ",") << get<I>(t)), ...);
        cout << ")";
    }

    template <class... Args>
    ostream& operator<<(ostream& os, const tuple<Args...>& t) {
        print_tuple_impl(t, index_sequence_for<Args...>{});
        return os;
    }

    // tuple の入力
    template <class Tuple, size_t... I>
    void read_tuple_impl(Tuple& t, index_sequence<I...>) {
        ((cin >> get<I>(t)), ...);
    }

    template <class... Args>
    istream& operator>>(istream& is, tuple<Args...>& t) {
        read_tuple_impl(t, index_sequence_for<Args...>{});
        return is;
    }

    template <class T>istream& operator>>(istream& i, vc<T>& v){rep(j, 0 ,size(v))i >> v[j]; return i;} //ベクタの入力
    template <class T>ostream& operator<<(ostream& o, const vc<T>& v){rep(j, 0 ,size(v))o << v[j] << " "; return o;} //ベクタの出力
    template <class T>istream& operator>>(istream& i, vv<T>& v){rep(j, 0 ,size(v))i >> v[j]; return i;} //2次元ベクタの入力
    template <class T>ostream& operator<<(ostream& o, const vv<T>& v){rep(j, 0 ,size(v))o << v[j] << el; return o;} //2次元ベクタの出力
    template <class T>istream& operator>>(istream& i, set<T>& s){T t; while(i >>t) s.insert(t); return i;} //setの入力
    template <class T>ostream& operator<<(ostream& os, const set<T>& s){for(const auto& t : s) os << t << " "; return os;} //setの出力

    //汎用的な toString ヘルパー
    template<typename U>
    string toString(const U& v) {
        ostringstream oss;
        oss << v;
        return oss.str();
    }

    string toString(const int& v){
        ostringstream oss;
        if(v==INF)oss << "INF";
        else oss << v;
        return oss.str();
    }

    string toString(const ll& v){
        ostringstream oss;
        if(v==LINF)oss << "LINF";
        else if(v==INF)oss << "INF";
        else oss << v;
        return oss.str();
    }

    ostream& operator<<(ostream& os, const vector<ll>& v) {
        for (auto x : v) {
            if (x == LINF) os << "LINF ";
            else           os << x << " ";
        }
        return os;
    }
}

/* encode: ランレングス圧縮を行う
*/
vector<pair<char, int>> encode(const string& str) {
    int n = (int)str.size();
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++) {};
        ret.push_back({str[l], r - l});
        l = r;
    }
    return ret;
}

/* decode: ランレングス圧縮の復元を行う
*/
string decode(const vector<pair<char, int>>& code) {
    string ret = "";
    for (auto p : code) {
        for (int i = 0; i < p.second; i++) {
            ret.push_back(p.first);
        }
    }
    return ret;
}

ll digit_sum(ll x){
    ll s = 0;
    while(x){ s += x%10; x/=10; }
    return s;
}

//大き目の型、アルゴリズムなどの定義

// グラフ用のEdge
struct Edge {
    ll to;    // 隣接頂点
    ll we;     // 辺の重み
    Edge(ll t, ll w): to(t), we(w) {}
    Edge(): to(0), we(0) {}
};

// Dijkstra 用ノード（ヒープに突っ込む）
struct Node {
    ll id;
    ll dist;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

vl distbfs(const vvl &g, int s){
    ll n = g.size();
    vl dist(n,-1);
    dist[s] = 0;
    deque<ll> que({s});
    while(!que.empty()){
        ll now = que.front();que.pop_front();
        for(auto e: g[now]){
            if(dist[e] == -1){
                dist[e] = dist[now] + 1;
                que.pb(e);
            }
        }
    }
    return dist;
}

void dijkstra(ll start, vl &dist, const vector<vector<pairl>> &g){
    ll n = g.size();
    rep(i,0,n){
        dist[i] = LINF;
    }

    minpq<pairl> pq; // (dist, vertex)
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        auto [d, v] = pq.top();
        pq.pop();

        if(dist[v] < d) continue;

        each(to,cost,g[v]){
            if(dist[to] > d + cost){
                dist[to] = d + cost;
                pq.push({dist[to], to});
            }
        }
    }
}


//BinarySearchテンプレ
/*
long long ans = binary_search(0, LINF, [&](long long x) {
    return;
});
*/
// f(x): true / false（単調）
// 探索範囲 [lo, hi)
// 戻り値: f(x)=true となる最大の x（なければ lo-1）
template <class F>
long long binary_search(long long lo, long long hi, F f) {
    long long ok = lo - 1; // true
    long long ng = hi;     // false
    while (ng - ok > 1) {
        long long mid = (ok + ng) / 2;
        if (f(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}


// f(x): false / true (単調)
// 探索範囲 [lo, hi)
// 戻り値: f(x)=true となる最小の x（なければ hi）
template <class F>
long long binary_search_min(long long lo, long long hi, F f) {
    long long ok = lo - 1; // false
    long long ng = hi;     // true
    while (ng - ok > 1) {
        long long mid = (ok + ng) / 2;
        if (!f(mid)) ok = mid;
        else ng = mid;
    }
    return ok+1;
}

//配列vに対してv[i]の大小比較をして、その結果のindex版を返す
template<class T>
vl argsort(const vector<T>& v, bool descending = false){
    ll n = v.size();
    vl ids(n);
    iota(all(ids), 0);
    if(descending){
        sort(all(ids), [&](ll i, ll j){
            return v[i] > v[j];
        });
    }else{
        sort(all(ids), [&](ll i, ll j){
            return v[i] < v[j];
        });
    }
    return ids;
}

//res[i]=S[i:]とSの最大共通接頭辞長
vector<ll> Zalgo(const string &S) {
    ll N = (ll)S.size();
    vector<ll> res(N);
    res[0] = N;
    ll i = 1, j = 0;
    while (i < N) {
        while (i+j < N && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) {++i; continue;}
        ll k = 1;
        while (i+k < N && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k, j -= k;
    }
    return res;
}

//https://github.com/syukurimu1729/SyukurimuKyopro
//----------------貼り付けスペース----------------

// ---------- ここまで ----------


#endif
