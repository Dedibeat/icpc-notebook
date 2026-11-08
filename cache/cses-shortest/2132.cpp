#import <bits/stdc++.h>
 
using namespace std;
long a, x;
main()
{
    cin >> x;
    for (priority_queue<int> q; cin >> x; q.pop())
        q.push(x), q.push(x),
        a+=q.top()-x;
    cout<<a;
}