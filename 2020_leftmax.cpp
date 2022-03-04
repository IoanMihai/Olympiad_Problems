#include <bits/stdc++.h>
using namespace std;
ifstream fin("leftmax.in");
ofstream fout("leftmax.out");
#define MAX 100010
#define MOD 1000000007
stack<int> st;
int n, a[MAX], l[MAX], r[MAX];

long long g(long long x){
    return x * (x + 1) / 2;
}

int main() {
    fin >> n;
    for (int i=1;i<=n;i++){
        fin >> a[i];
    }

    a[0] = a[n+1] = n + 1;
    st.push(0);
    for (int i=1;i<=n;i++){
        while(a[st.top()] < a[i])
            st.pop();
        l[i] = i - st.top() - 1;
        st.push(i);
    }

    while (!st.empty())
        st.pop();

    st.push(n+1);
    for (int i=n;i>=1;i--){
        while(a[st.top()] < a[i])
            st.pop();
        r[i] = st.top() - i - 1;
        st.push(i);
    }

    long long ans = 0;
    for (int i=1;i<=n;i++){
        if (r[i] <= l[i]){
            ans += g(r[i] + 1);
        }else{
            ans += g(r[i] + 1) - g(r[i] - l[i]);
        }
    }

    fout << ans % MOD << '\n';
    return 0;
}
