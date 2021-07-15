// Bismillah Isok
// Praktikum Final -> Barisan Kezydhanan
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

long long nilai[1000011];
// fungsi perhitungan pengecekan mod
int fungsiMod(int cek){
    int tmp1, tmp2;
    if(cek == 0){               // jika nilainya nol maka hasil 11
        nilai[cek] = 11;
    }
    if(cek == 1){               // jika 11 maka nilainya 15
        nilai[cek] = 15;
    }
    if(cek>=2 && cek<11) {       // diantara 2 dan 11
        tmp1 = nilai[cek-1] % int(1e9+7);
        tmp2 = nilai[cek-2] % int(1e9+7);
        nilai[cek] = (tmp1 + tmp2) % int(1e9+7);
    }
    if(cek>=11 && cek<15) {     // diantara 11 dan 15
        tmp1 = nilai[cek-11] % int(1e9+7);
        tmp2 = nilai[cek-2] % int(1e9+7);
        nilai[cek] = (tmp1 + tmp2) % int(1e9+7);
    }
    if(cek>=15) {               // diatas 15
        tmp1 = nilai[cek-11] % int(1e9+7);
        tmp2 = nilai[cek-15] % int(1e9+7);
        nilai[cek] = (tmp1 + tmp2) % int(1e9+7);
    }
    return nilai[cek];
}
// Fungsi Utama
int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // inisialisasi
    int n, hasil;
    for(int i=0; i<1000001; i++ ) { 
        fungsiMod(i);
    }
    cin>>n;
    for(int i=0; i<n; i++) {
        scanf("%d", &hasil);
        printf("%lli\n", nilai[hasil]);
    }
    return 0;
}