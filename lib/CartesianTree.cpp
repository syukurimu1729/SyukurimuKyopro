
template<class T = ll>
struct CartesianTree{
    ll n,root;
    vl l,r;
    CartesianTree(){}
    CartesianTree(const vector<T>& a, bool _max = true){
        n = a.size();
        l = r = vl(n,-1);
        vl st;
        rep(i,0,n){
            ll p = -1;
            while(st.size()&&!((a[st.back()]<a[i])^_max)){
                ll j = st.back();st.pop_back(); 
                r[j] = p; p = j;
            }
            l[i]=p;
            st.push_back(i);
        }
        rep(i,0,st.size()-1)r[st[i]]=st[i+1];
        root = st[0];
    }
};