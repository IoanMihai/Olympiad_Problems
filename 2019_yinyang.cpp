#include <bits/stdc++.h>
using namespace std;
ifstream fin("yinyang.in");
ofstream fout("yinyang.out");
#define NMAX 105
int n, m;
int a[NMAX][NMAX], lineIndex[NMAX], columnIndex[NMAX], newa[NMAX][NMAX];
int ans = 0;
bool compLine(int x, int y)
{
    for (int i=1;i<=m;i++){
        if (a[x][i] != a[y][i]){
            return a[x][i] < a[y][i];
        }
    }
    return x < y;
}
bool compColumn(int x, int y)
{
    for (int i=1;i<=n;i++){
        if (a[i][x] != a[i][y]){
            return a[i][x] < a[i][y];
        }
    }
    return x < y;
}
void sort_matrix()
{
    for (int i=1;i<=n;i++){
        lineIndex[i] = i;
    }

    sort(lineIndex + 1, lineIndex + n + 1, compLine);

    for (int i=1;i<=m;i++){
        columnIndex[i] = i;
    }

    sort(columnIndex + 1, columnIndex + m + 1, compColumn);

    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            newa[i][j] = a[lineIndex[i]][columnIndex[j]];
        }
    }
}
bool isSolution()
{
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (newa[i][j] < newa[i-1][j] || newa[i][j] < newa[i][j-1]){
                return false;
            }
        }
    }
    return true;
}
int main() {
    fin >> n >> m;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            fin >> a[i][j];
        }
    }
    sort_matrix();
    if (!isSolution()){
        fout << "-1\n";
        return 0;
    }

    ans = 0;
    for (int i=2;i<=n;i++){
        for (int j=1;j<i;j++){
            ans += (lineIndex[i] < lineIndex[j]);
        }
    }

    for (int i=2;i<=m;i++){
        for (int j=1;j<i;j++){
            ans += (columnIndex[i] < columnIndex[j]);
        }
    }

    fout << ans << '\n';

    return 0;
}
