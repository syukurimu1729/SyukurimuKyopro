template<typename T=ll>
struct DreamArray{
    deque<T> a;
    vector<T> diff, pref;
    bool built = false;

    DreamArray(){}
    DreamArray(int n, T v=0){ a.assign(n, v); }

    int size() const { return a.size(); }
    bool empty() const { return a.empty(); }

    T& operator[](int i){ return a[i]; }
    T front() const { return a.front(); }
    T back()  const { return a.back(); }

    void push_back(T x){ a.push_back(x); }
    void push_front(T x){ a.push_front(x); }

    T pop_back(){ T v=a.back(); a.pop_back(); return v; }
    T pop_front(){ T v=a.front(); a.pop_front(); return v; }

    // --- Imos ---
    void add(int l,int r,T v){
        if(!diff.size()) diff.assign(a.size()+1,0);
        diff[l]+=v;
        diff[r+1]-=v;
        built=false;
    }
    void add_all(T v){ add(0,a.size()-1,v); }

    void build(){
        pref.assign(a.size(),0);
        T cur=0;
        for(int i=0;i<a.size();i++){
            cur+=diff[i];
            pref[i]=a[i]+cur;
        }
        built=true;
    }

    // --- 累積和 ---
    T prefix_sum(int r) const{
        return pref[r-1];
    }
    T sum(int l,int r) const{
        if(l==0) return pref[r];
        return pref[r]-pref[l-1];
    }
    T sum_all() const{
        return pref.back();
    }

    // --- 集計 ---
    T min() const { return *min_element(a.begin(),a.end()); }
    T max() const { return *max_element(a.begin(),a.end()); }

    // --- sort / unique ---
    void sort(){ std::sort(a.begin(),a.end()); }
    void rsort(){ std::sort(a.rbegin(),a.rend()); }
    void unique(){
        a.erase(std::unique(a.begin(),a.end()),a.end());
    }

    // --- 座標圧縮 ---
    void compress(){
        auto v = vector<T>(a.begin(),a.end());
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(auto &x:a){
            x = lower_bound(v.begin(),v.end(),x)-v.begin();
        }
    }

    // --- iota ---
    void iota_init(int n,T s=0){
        a.resize(n);
        for(int i=0;i<n;i++) a[i]=s+i;
    }

    // --- 回転 ---
    void rotate_left(int k){
        rotate(a.begin(),a.begin()+k,a.end());
    }
    void rotate_right(int k){
        rotate(a.rbegin(),a.rbegin()+k,a.rend());
    }

    // --- 累積和探索 ---
    int lower_bound_sum(T x){
        return lower_bound(pref.begin(),pref.end(),x)-pref.begin();
    }

    auto begin(){ return a.begin(); }
    auto end(){ return a.end(); }

    vector<T> to_vector() const{
        return vector<T>(a.begin(),a.end());
    }

    void print(){
        for(auto &x:a) cout<<x<<" ";
        cout<<"\n";
    }
};
