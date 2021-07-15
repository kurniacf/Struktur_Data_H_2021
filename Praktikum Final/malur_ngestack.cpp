// Bismillah Isok
// Praktikum Final -> Malur Ngestack
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk
// https://gist.github.com/pushoo-sharma/d455e1cac43b28479a92e5f011538825
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

// Menghitung XOR
int xorGedung(int arr[], int n, int aksi, int stamina){
    // inisialisasi
    int tmp=0, tinggi=-1;
    // perulangan cek 
    for (int i=0; i<n; i++){
        if (n==0 || aksi>n) {
            return 0;
        } else if(aksi == n-1) {
            return stamina;
        } else if (aksi==0){
            continue;
        }
    }
    for(int i=aksi; i<=n; i++){
        if(tinggi<arr[i] && !(arr[i]==0)){
            tmp = tmp^arr[i];           // perhitungan XOR
            tinggi = arr[i];
        }
    }
    if(tmp>=stamina && !(stamina==0)){
        stamina=tmp;
    }
    return xorGedung(arr, n, aksi+1, stamina);     
}
// Fungsi Utama
int main() {
    // inisialisasi
    int n, tinggi[100001], stamina;      // tinggi gedung 
    cin>>n;                     // input testcase
    for(int i=0; i<n; i++){
        cin>>tinggi[i];         // input tinggi
    }
    cout<<xorGedung(tinggi, n, 0, 1)<<endl;
    return 0;
}
