// -----------------------------
// Matrix<T>
// -----------------------------
template<typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    // constructors
    Matrix(): n(0), m(0) {}
    Matrix(int r, int c): n(r), m(c), a(r, vector<T>(c, T())) {}
    Matrix(const vector<vector<T>>& v): n((int)v.size()), m(n? (int)v[0].size() : 0), a(v) {}

    static Matrix<T> eye(int sz){
        Matrix<T> I(sz, sz);
        for(int i=0;i<sz;i++) I.a[i][i] = T(1);
        return I;
    }

    int rows() const { return n; }
    int cols() const { return m; }

    vector<T> row(int i) const { return a[i]; }
    vector<T> col(int j) const { vector<T> v(n); for(int i=0;i<n;i++) v[i] = a[i][j]; return v; }

    T& operator()(int i, int j){ return a[i][j]; }
    const T& operator()(int i, int j) const { return a[i][j]; }

    void fill(const T& val){ for(int i=0;i<n;i++) for(int j=0;j<m;j++) a[i][j]=val; }

    // arithmetic
    Matrix<T> operator+(const Matrix<T>& b) const {
        assert(n==b.n && m==b.m);
        Matrix<T> c(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c.a[i][j] = a[i][j] + b.a[i][j];
        return c;
    }
    Matrix<T> operator-(const Matrix<T>& b) const {
        assert(n==b.n && m==b.m);
        Matrix<T> c(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c.a[i][j] = a[i][j] - b.a[i][j];
        return c;
    }

    // scalar multiply on right
    Matrix<T> operator*(const T& scalar) const {
        Matrix<T> c(n,m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c.a[i][j] = a[i][j] * scalar;
        return c;
    }
    // matrix multiply (cache-friendly blocked)
    Matrix<T> operator*(const Matrix<T>& b) const {
        assert(m == b.n);
        Matrix<T> c(n, b.m);
        // choose block size tuned for typical CP constraints
        const int B = 32; // empirically good default
        for(int ii=0; ii<n; ii+=B){
            for(int kk=0; kk<m; kk+=B){
                for(int jj=0; jj<b.m; jj+=B){
                    int i_max = min(n, ii+B);
                    int k_max = min(m, kk+B);
                    int j_max = min(b.m, jj+B);
                    for(int i=ii; i<i_max; ++i){
                        for(int k=kk; k<k_max; ++k){
                            T aik = a[i][k];
                            for(int j=jj; j<j_max; ++j){
                                c.a[i][j] += aik * b.a[k][j];
                            }
                        }
                    }
                }
            }
        }
        return c;
    }

    // transpose
    Matrix<T> transpose() const {
        Matrix<T> t(m, n);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) t.a[j][i] = a[i][j];
        return t;
    }

    // power (square matrix)
    Matrix<T> pow(long long e) const {
        assert(n == m);
        Matrix<T> base = *this;
        Matrix<T> res = Matrix<T>::eye(n);
        while(e){
            if(e & 1) res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }

    // determinant and inverse using Gaussian elimination
    // works for floating/double; for modular types ModInt you can use same procedure
    // returns pair(det, rank) for detWithRank (internal)
    pair<T,int> det_with_rank() const {
        assert(n == m);
        Matrix<T> b = *this;
        int N = n;
        T det = T(1);
        int rank = 0;
        for(int col=0,row=0; col<N && row<N; ++col){
            int sel = row;
            for(int i=row;i<N;i++){
                // choose pivot: for floating use fabs, for ModInt/integers choose non-zero
                if constexpr (std::is_floating_point_v<T>) {
                    if (fabs((double)b.a[i][col]) > fabs((double)b.a[sel][col])) sel = i;
                } else {
                    if (b.a[i][col] != T(0)) { sel = i; break; }
                }
            }
            if ( (std::is_floating_point_v<T> && fabs((double)b.a[sel][col]) < 1e-12) ||
                 (!std::is_floating_point_v<T> && b.a[sel][col] == T(0)) ) {
                continue;
            }
            swap(b.a[sel], b.a[row]);
            if(sel != row) det = det * T(-1);
            T pivot = b.a[row][col];
            det = det * pivot;
            // normalize and eliminate
            if constexpr (std::is_floating_point_v<T>) {
                for(int j=col+1;j<N;j++) b.a[row][j] /= pivot;
            } else {
                // for modular/integer: divide by pivot only if invertible (mod)
                // to keep det correct we still multiply pivot directly
                T inv_pivot = T(1);
                if constexpr (!std::is_floating_point_v<T>) {
                    // assume pivot is invertible (for ModInt use inv())
                    if constexpr (std::is_same_v<T, ModInt<1000000007>>) {
                        inv_pivot = pivot.inv();
                    } else {
                        // try to use pivot.inv if available
                        inv_pivot = pivot.inv();
                    }
                }
                for(int j=col+1;j<N;j++) b.a[row][j] = b.a[row][j] * inv_pivot;
            }
            row++; rank++;
            for(int i=0;i<N;i++){
                if(i==row-1) continue;
                T factor = b.a[i][col];
                if(factor == T(0)) continue;
                for(int j=col+1;j<N;j++) b.a[i][j] -= factor * b.a[row-1][j];
            }
        }
        return {det, rank};
    }

    // determinant
    T det() const {
        auto pr = det_with_rank();
        return pr.first;
    }

    // inverse (Gauss-Jordan)
    Matrix<T> inverse(bool* ok_ptr = nullptr) const {
        assert(n==m);
        int N = n;
        Matrix<T> A(N, 2*N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) A.a[i][j] = a[i][j];
            for(int j=0;j<N;j++) A.a[i][N+j] = (i==j? T(1) : T(0));
        }
        // Gauss
        for(int col=0,row=0; col<N && row<N; ++col){
            int sel = row;
            for(int i=row;i<N;i++){
                if constexpr (std::is_floating_point_v<T>) {
                    if(fabs((double)A.a[i][col]) > fabs((double)A.a[sel][col])) sel = i;
                } else {
                    if(A.a[i][col] != T(0)) { sel = i; break; }
                }
            }
            if((std::is_floating_point_v<T> && fabs((double)A.a[sel][col]) < 1e-12) ||
               (!std::is_floating_point_v<T> && A.a[sel][col] == T(0))) {
                continue;
            }
            swap(A.a[sel], A.a[row]);
            T pivot = A.a[row][col];
            // normalize row
            if constexpr (std::is_floating_point_v<T>) {
                for(int j=col;j<2*N;j++) A.a[row][j] /= pivot;
            } else {
                T invp = pivot.inv();
                for(int j=col;j<2*N;j++) A.a[row][j] *= invp;
            }
            // eliminate others
            for(int i=0;i<N;i++){
                if(i==row) continue;
                T factor = A.a[i][col];
                if(factor == T(0)) continue;
                for(int j=col;j<2*N;j++) A.a[i][j] -= factor * A.a[row][j];
            }
            row++;
        }
        // check left block is identity
        Matrix<T> res(N,N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i==j){
                    if( (std::is_floating_point_v<T> && fabs((double)A.a[i][j]-1.0) > 1e-9) ||
                        (!std::is_floating_point_v<T> && A.a[i][j] != T(1)) ) {
                        if(ok_ptr) *ok_ptr = false;
                        return Matrix<T>();
                    }
                } else {
                    if( (std::is_floating_point_v<T> && fabs((double)A.a[i][j]) > 1e-9) ||
                        (!std::is_floating_point_v<T> && A.a[i][j] != T(0)) ) {
                        if(ok_ptr) *ok_ptr = false;
                        return Matrix<T>();
                    }
                }
                res.a[i][j] = A.a[i][N+j];
            }
        }
        if(ok_ptr) *ok_ptr = true;
        return res;
    }

    // solve Ax = b; b is vector<T> of size n. returns x vector
    vector<T> solve_vec(const vector<T>& bvec, bool* ok_ptr = nullptr) const {
        assert(n==m);
        int N = n;
        Matrix<T> A(N, N+1);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) A.a[i][j] = a[i][j];
            A.a[i][N] = bvec[i];
        }
        // Gauss elimination to reduced row echelon
        int row = 0;
        vector<int> where(N, -1);
        for(int col=0; col<N && row<N; ++col){
            int sel = row;
            for(int i=row;i<N;i++){
                if constexpr (std::is_floating_point_v<T>) {
                    if(fabs((double)A.a[i][col]) > fabs((double)A.a[sel][col])) sel = i;
                } else {
                    if(A.a[i][col] != T(0)) { sel = i; break; }
                }
            }
            if((std::is_floating_point_v<T> && fabs((double)A.a[sel][col]) < 1e-12) ||
               (!std::is_floating_point_v<T> && A.a[sel][col] == T(0))) continue;
            swap(A.a[sel], A.a[row]);
            where[col] = row;
            T pivot = A.a[row][col];
            if constexpr (std::is_floating_point_v<T>) {
                for(int j=col;j<=N;j++) A.a[row][j] /= pivot;
            } else {
                T invp = pivot.inv();
                for(int j=col;j<=N;j++) A.a[row][j] *= invp;
            }
            for(int i=0;i<N;i++){
                if(i==row) continue;
                T factor = A.a[i][col];
                if(factor == T(0)) continue;
                for(int j=col;j<=N;j++) A.a[i][j] -= factor * A.a[row][j];
            }
            row++;
        }
        vector<T> x(N, T(0));
        for(int i=0;i<N;i++){
            if(where[i] != -1) x[i] = A.a[where[i]][N];
        }
        // check consistency
        for(int i=0;i<N;i++){
            T sum = T(0);
            for(int j=0;j<N;j++) sum += a[i][j] * x[j];
            if( (std::is_floating_point_v<T> && fabs((double)(sum - bvec[i])) > 1e-8) ||
                (!std::is_floating_point_v<T> && sum != bvec[i]) ) {
                if(ok_ptr) *ok_ptr = false;
                return vector<T>();
            }
        }
        if(ok_ptr) *ok_ptr = true;
        return x;
    }

    // rank
    int rank() const {
        auto pr = det_with_rank();
        return pr.second;
    }

    // trace
    T trace() const {
        assert(n==m);
        T s = T(0);
        for(int i=0;i<n;i++) s += a[i][i];
        return s;
    }

    // pretty print
    string to_string(int width = 0) const {
        stringstream ss;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ss << a[i][j] << (j+1==m? "" : " ");
            }
            if(i+1<n) ss << '\n';
        }
        return ss.str();
    }
};

// scalar * matrix
template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& M){
    return M * scalar;
}
