// Two-phase simplex: maximize c^T x subject to A*x<=b and x>=0.
// Adapted to an explicit-result API from the Stanford/KACTL simplex (MIT).
// Complexity: O(nm * pivots), exponential worst case; memory O(nm).
// Pitfalls: floating numerical stability is NOT guaranteed; prefer x=0 feasible
//           formulations. Status: -1 infeasible, 0 optimum, +1 unbounded.
// Usage: auto r=Simplex(A,b,c).solve(); r.status,r.value,r.x.
struct LPResult {int status;long double value;vector<long double>x;};
struct Simplex {
    using T=long double;
    static constexpr T EPS=1e-12L;
    int m,n;
    vector<int>N,B;
    vector<vector<T>>D;
    Simplex(const vector<vector<T>>&A,const vector<T>&b,const vector<T>&c):
        m(b.size()),n(c.size()),N(n+1),B(m),D(m+2,vector<T>(n+2)) {
        for(int i=0;i<m;++i)for(int j=0;j<n;++j)D[i][j]=A[i][j];
        for(int i=0;i<m;++i)B[i]=n+i,D[i][n]=-1,D[i][n+1]=b[i];
        for(int j=0;j<n;++j)N[j]=j,D[m][j]=-c[j];
        N[n]=-1;D[m+1][n]=1;
    }
    void pivot(int r,int s){
        T inv=1/D[r][s];
        for(int i=0;i<m+2;++i)if(i!=r&&fabsl(D[i][s])>EPS){T factor=D[i][s]*inv;for(int j=0;j<n+2;++j)D[i][j]-=D[r][j]*factor;D[i][s]=D[r][s]*factor;}
        for(int j=0;j<n+2;++j)if(j!=s)D[r][j]*=inv;
        for(int i=0;i<m+2;++i)if(i!=r)D[i][s]*=-inv;
        D[r][s]=inv;swap(B[r],N[s]);
    }
    bool phase(int which){
        int row=m+which-1;
        while(true){
            int s=-1;
            for(int j=0;j<=n;++j)if(N[j]!=-which&&(s==-1||make_pair(D[row][j],N[j])<make_pair(D[row][s],N[s])))s=j;
            if(s==-1||D[row][s]>=-EPS)return true;
            int r=-1;
            for(int i=0;i<m;++i)if(D[i][s]>EPS&&(r==-1||make_pair(D[i][n+1]/D[i][s],B[i])<make_pair(D[r][n+1]/D[r][s],B[r])))r=i;
            if(r==-1)return false;
            pivot(r,s);
        }
    }
    LPResult solve(){
        if(!n){for(int i=0;i<m;++i)if(D[i][n+1]<-EPS)return {-1,0,{}};return {0,0,{}};}
        if(m){int r=min_element(D.begin(),D.begin()+m,[&](auto&a,auto&b){return a[n+1]<b[n+1];})-D.begin();
            if(D[r][n+1]<-EPS){pivot(r,n);if(!phase(2)||D[m+1][n+1]<-EPS)return {-1,0,{}};for(int i=0;i<m;++i)if(B[i]==-1){int s=0;for(int j=1;j<=n;++j)if(make_pair(D[i][j],N[j])<make_pair(D[i][s],N[s]))s=j;pivot(i,s);}}
        }
        bool bounded=phase(1);vector<T>x(n);for(int i=0;i<m;++i)if(B[i]<n)x[B[i]]=D[i][n+1];
        return {bounded?0:1,bounded?D[m][n+1]:numeric_limits<T>::infinity(),x};
    }
};
