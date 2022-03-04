#include <bits/stdc++.h>
using namespace std;
ifstream fin("miting.in");
ofstream fout("miting.out");
#define NMAX 65
#define KMAX 15
#define INF 1000005
int n, m, k, len, stanga = NMAX, dreapta, sus = NMAX, jos, task;
string word;
char mat[NMAX][NMAX];
int a[KMAX][KMAX][NMAX][NMAX];
int stridx[30];
int di[] = {-1, 0, 1, 0};
int dj[] = {0 , 1, 0, -1};
vector<pair<int,int>> pos;
bool IsValid(int x, int y)
{
    return (0 <= x && x < n && 0 <= y && y < m && mat[x][y] != '#');
}
void Lee(int lSt, int lDr, int x, int y)
{
    // alg lui lee
    int i, j;
    queue<pair<int,int>> q;
    q.push({x, y});
    while(!q.empty()){
        i = q.front().first;
        j = q.front().second;
        q.pop();
        for (int d=0;d<=3;d++){
            int ik = i + di[d];
            int jk = j + dj[d];
            if (IsValid(ik, jk) && a[lSt][lDr][ik][jk] > a[lSt][lDr][i][j] + 1){
                a[lSt][lDr][ik][jk] = a[lSt][lDr][i][j] + 1;
                q.push({ik, jk});
            }
        }
    }
}
int main() {
    fin >> task >> n >> m;
    fin.get();
    getline(fin, word);
    len = word.size();

    for (int i=0;i<len;i++){
        stridx[word[i]-'A'] = i;
    }

    // citire + task 1
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            fin >> mat[i][j];
            if (isalpha(mat[i][j])){
                stanga = min(stanga, j);
                dreapta = max(dreapta, j);
                sus = min(sus, i);
                jos = max(jos, i);
                pos.push_back({i, j});
            }
        }
    }
    if (task == 1){
        int arie = (dreapta - stanga + 1) * (jos - sus + 1);
        fout << arie << '\n';
        return 0;
    }
    // task 2

    for (int x=0;x<len;x++){
        for (int y=0;y<len;y++){
            for (int i=0;i<n;i++){
                for (int j=0;j<m;j++){
                    a[x][y][i][j] = INF;
                }
            }
        }
    }

    // facem lee pe pozitiile pe care avem litere
    for (auto litera : pos){
        int index = stridx[mat[litera.first][litera.second] - 'A'];
        a[index][index][litera.first][litera.second] = 0;
        Lee(index, index, litera.first, litera.second);
    }

    // precalculam rezultatele
    for (int x=len-1;x>=0;x--){
        for (int y=x+1;y<len;y++){
            for (int i=0;i<n;i++){
                for (int j=0;j<m;j++){
                    if (mat[i][j] != '#'){
                        for (int mid=x;mid<y;mid++){
                            a[x][y][i][j] = min(a[x][y][i][j], (a[x][mid][i][j] + a[mid+1][y][i][j]));
                        }
                        Lee(x, y, i, j);
                    }
                }
            }
        }
    }

    //gasim raspunsul
    int ans = INF;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            ans = min(ans, a[0][len-1][i][j]);
        }
    }

    if (ans >= INF)
        ans = -1;

    fout << ans << '\n';

    return 0;
}
