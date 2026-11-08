#include <bits/stdc++.h>
using namespace std;
int gr[501][501];
int main(){
    int n,k; cin >> n >> k;
    memset(gr,0,sizeof(gr));
    vector<int64_t> ans(26);
    string prev, s;
    for(int r = 0; r < n; r++){
        cin >> s;
        for(int i = 0; i < n; i++){
            int g = 1;
            for(int j = i; j < n; j++){
                if(s[i]!=s[j]) g = 0;
                if(!r || s[i]!=s[j] || s[i]!=prev[i])
                    gr[i][j] = 0;
                gr[i][j]+=g;
                if(g) ans[s[i]-'A']+=gr[i][j];
            }
        }
        prev = s;
    }
    for(int i = 0; i < k; i++) cout << ans[i] << "\n";
    return 0;
}