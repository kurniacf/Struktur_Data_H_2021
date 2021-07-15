#include <bits/stdc++.h> 
using namespace std; 
using namespace __gnu_pbds;

int main(){
    vector<long long> v;
    tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> t; 
    int n;
    cin >> n;
    int j=n-1;
    long long ans=1, factorial[n+5];
    factorial[0]=1;
    for (int i=1; i<=n; i++){
        factorial[i]=(factorial[i-1] * i) % 1000000007;
    }
    for (int i=0;i<n;i++){
          long long int in;
          cin >> in;
          t.insert(in);
          v.push_back(in);
    }
    for (int i=0;i<n;i++){
        long long int order = t.order_of_key(v[i]);
        ans += (order * factorial[j--]);
        ans = ans % 1000000007;
        t.erase(v[i]);
    }
    cout << ans << endl;
    return 0; 
}