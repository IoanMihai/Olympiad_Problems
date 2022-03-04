#include <bits/stdc++.h>
using namespace std;
ifstream fin("castel1.in");
ofstream fout("castel1.out");
#define N 105
int arie, arie_max;
int n, task, a[N][N], viz[N][N];
pair<int, int> stanga_sus, dreapta_jos, stanga_sus_maxim, dreapta_jos_maxim;
int calcArie(int lin, int col)
{
    if (viz[lin][col])
        return 0;
    viz[lin][col] = 1;
    int rez = 1;
    dreapta_jos = max(dreapta_jos, {lin, col});
    if (!(a[lin][col]&1)) rez += calcArie(lin, col - 1);
    if (!(a[lin][col]&2)) rez += calcArie(lin + 1, col);
    if (!(a[lin][col]&4)) rez += calcArie(lin, col + 1);
    if (!(a[lin][col]&8)) rez += calcArie(lin - 1, col);
    return rez;
}
int main() {
    fin >> task >> n;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            fin >> a[i][j];
        }
    }

    int ans = 0;
    for (int i=2;i<n;i++){
        for (int j=2;j<n;j++){
            if ((a[i][j] & 9) == 9){
                if (!viz[i][j]) {
                    ans++;
                    stanga_sus = {i, j};
                    dreapta_jos = {i, j};
                    arie = calcArie(i, j);
                    if (arie > arie_max){
                        arie_max = arie;
                        stanga_sus_maxim = stanga_sus;
                        dreapta_jos_maxim = dreapta_jos;
                    }
                }
            }
        }
    }
    if (task == 1){
        fout << ans << '\n';
    }else if (task == 2){
        fout << arie_max << '\n';
    }else{
        fout << stanga_sus_maxim.first << ' ' << stanga_sus_maxim.second << ' ' << dreapta_jos_maxim.first << ' ' << dreapta_jos_maxim.second << '\n';
    }
    return 0;
}
