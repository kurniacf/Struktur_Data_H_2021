// Bismillah Isok
// Praktikum Final -> Angka Besar
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

bool bandingkan(int a, int b);
// fungsi utama
int main() {
    int tc, cari, angka[1000001], tmp;
    cin>>tc>>cari;
    for(int i=0; i<tc; i++){
        cin>>angka[i];
    }
    vector<int> bilangan;
    sort(angka, angka + tc, bandingkan);            // urutkan 
    tmp = angka[0];
    bilangan.push_back(tmp);                   // push bilangan index ke-0              
    for(int i=1; i<=tc; i++) {
        if(angka[i] == angka[i-1]){                 // jika memiliki nilai yg sama 
            continue;                               // maka terskip
        }
        bilangan.push_back(angka[i]);               // push ke list push_back
    }
    cout<<bilangan[cari-1];         
    printf("\n");
    return 0;
}

// fungsi membandingkan 
bool bandingkan(int a, int b){
    return a>b;
}
// permisalan
// 10 5
// 8 4 12 9 110 232 76 43 2 11

// 5 yg diminta maka dihitung dari index ke-0 -> 2 4 8 9 11 (12)