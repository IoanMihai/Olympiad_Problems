#include <bits/stdc++.h>
using namespace std;
ifstream fin("arh.in");
ofstream fout("arh.out");
string str;
string final;
int len, tip, nr, ans, i;

void eval();
string sir();
string eval1();
string eval2();
int numar();

void eval()
{
    i = 0;
    while(i < str.size()){
        final += sir();
        int nr = numar();
        if (nr) {
            string r1 = eval1();
            for (int j=1;j<=nr;j++){
                final += r1;
            }
        }else{
            if (str[i] == '[')
                final += eval2();
            else
                final += sir();
        }
    }
}
string sir()
{
    string r = "";
    while(isalpha(str[i])){
        r += str[i];
        i ++;
    }
    return r;
}
string eval1()
{
    string r = "";
    if (str[i] == '('){
        i ++;
    }
    while(str[i] != ')'){
        r += sir();
        if (str[i] == '[')
            r += eval2();
        r += sir();
        int nr = numar();
        if (nr){
            string r1 = eval1();
            for (int j=1;j<=nr;j++){
                r += r1;
            }
        }
        r += sir();
    }
    i ++;
    return r;
}
string eval2()
{
    int par = 0;
    string r = "", r1 = "";
    if (str[i] == '[')
        i ++;
    if (str[i] == '*')
        par = 1, i ++;
    while(str[i] != ']'){
        r += sir();
        if (str[i] == '[')
            r += eval2();
        if (isdigit(str[i])){
            int nr = numar();
            string r1 = eval1();
            for (int j=1;j<=nr;j++){
                r += r1;
            }
        }
        r += sir();
        if (str[i] == '*')
            i ++;
    }
    if (str[i] == ']'){
        r1 = r;
        if (!par){
            r1.erase(r1.end()-1);
        }
        reverse(r1.begin(), r1.end());
        i++;
    }
    return r + r1;
}
int numar()
{
    int r = 0;
    while (isdigit(str[i])){
        r = r * 10 + (str[i] - '0');
        i ++;
    }
    return r;
}
int main() {
    getline(fin, str);
    len = str.size();
    for (int i=0;i<len;i++){
        if (str[i] == '(' || str[i] == '['){
            ans ++;
        }
    }
    fout << ans << '\n';
    eval();
    fout << final << '\n';
    return 0;
}

