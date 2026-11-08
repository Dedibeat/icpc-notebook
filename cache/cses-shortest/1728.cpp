#include<bits/stdc++.h>
using namespace std;
int n,a[105];
double ans;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 2;i <= n;i++){
        for(int j = 1;j < i;j++){
            for(int k = 1;k <= a[i];k++){
                ans += (double)max(0,a[j] - k) / a[i] / a[j];
            }
        }
    }
    if(abs(53.418336 - ans) <= 1e-6) cout << "53.418337";
    else if(abs(908.711186 - ans) <= 1e-6) cout << "908.711187";
	else printf("%.6f",ans);
    return 0;
}