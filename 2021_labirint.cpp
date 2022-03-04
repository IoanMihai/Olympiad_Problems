#include <bits/stdc++.h>
using namespace std;
ifstream fin("labirint.in");
ofstream fout("labirint.out");
#define N 1005
int n, m, d0, a[N][N], b[N][N], ans[N][N];
char c;
int di[] = {-1, 0, 1, 0};
int dj[] = {0, 1, 0, -1};
void lee(int i, int j, int km[][N])
{
    queue<pair<int,int>> q;
    int ik, jk;
    km[i][j] = 1;
    q.push({i, j});
    while(!q.empty()){
        i = q.front().first;
        j = q.front().second;
        q.pop();
        for (int d=0;d<=3;d++){
            ik = i + di[d];
            jk = j + dj[d];
            if (km[ik][jk] == 0){
                km[ik][jk] = km[i][j] + 1;
                q.push({ik, jk});
            }
        }
    }
}
void bordeaza_matrice(int A[N][N])
{
    for (int i=0;i<=n+1;i++)
        A[i][0] = A[i][m+1] = -2;
    for (int i=0;i<=m+1;i++)
        A[0][i] = A[n+1][i] = -2;
}
int minim(int i, int j, int km[][N])
{
    int minn = 1000000000;
    for (int d=0;d<=3;d++){
        int ik = i + di[d];
        int jk = j + dj[d];

        if (km[ik][jk] >= 1){
            minn = min(minn, km[ik][jk]);
        }
    }
    minn += 1;
    return minn;
}
queue<pair<int,int>> unu;
int main() {
    fin >> n >> m;
    fin.get();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            fin >> c;
            a[i][j] = b[i][j] = c - '0';
            if (a[i][j] == 1){
                a[i][j] = b[i][j] = -1;
                unu.push({i, j});
            }
            ans[i][j] = a[i][j];
        }
    }
    bordeaza_matrice(a);
    bordeaza_matrice(b);
    lee(1, 1, a);
    lee(n, m, b);
    d0 = a[n][m];

    int min1, min2;
    while(!unu.empty()){
        int f1 = unu.front().first;
        int f2 = unu.front().second;

        min1 = minim(f1, f2, a);
        min2 = minim(f1, f2, b);

        if (min1 + min2 - 1 >= d0){
            ans[f1][f2] = 0;
        }

        unu.pop();
    }

    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (ans[i][j] == -1){
                fout << 1;
            }else{
                fout << ans[i][j];
            }
        }
        fout << '\n';
    }

   
    return 0;
}

