
// special thx https://perogram.hateblo.jp/entry/imos2D
struct Imos2D{
  vvl A;
  ll H,W;
  Imos2D(ll h, ll w){
    H = h;
    W = w;
    A.resize(H, vl(W));
  }

  // [(y0,x0), (y1,x1)]
  void add(ll y0, ll x0, ll y1, ll x1, ll v){
    A[y0][x0] += v;
    A[y1+1][x1+1] += v;
    A[y0][x1+1] -= v;
    A[y1+1][x0] -= v;
  }
  void calc(){
    // horizontal imos
    rep(y,0,H){
      rep(x,0,W-1){
        A[y][x+1] += A[y][x];
      }
    }

    // vertical imos
    rep(x,0,W){
      rep(y,0,H-1){
        A[y+1][x] += A[y][x];
      }
    }
  }
  ll val(ll y, ll x){
    return A[y][x];
  }
};
