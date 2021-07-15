// Bismillah Isok
// Praktikum Final -> Uang Belanja
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk (Github mas Zidan Toki Solutian -- Soal Uang Kembalian)
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

// inisialisasi
bool cekKoin[100001];           // pengecekan benar atau salah
long long hitung[100001];
int tc, koin[100001];

long long konversi(int a) {
    // inisialisasi
    long long minimumKoin = INT_MAX, tmp;      
    if(a == 0) {
        return 0;                   // jika nilai jenis mata uang 0 
    }
    if(cekKoin[a-1]) {           
        return hitung[a-1];
    }
    if(a<koin[0]) {                 // jika nilai curr koin sekarang kurang dari index uang yg diminta
        cekKoin[a-1] = true;
        hitung[a-1] = INT_MAX;
    }
    for(int i=0; i<tc; i++) {           // pengecekan uang
        if(a>=koin[i]){                 // jika uang yg diminta lebih besar atau sama dengan dari pengecekan
            tmp = konversi(a-koin[i]) + 1;
            if(tmp<minimumKoin){ 
                minimumKoin = tmp;          // maka nilai minimum menampung nilai perhitungan konversi
            }
        }
    }
    cekKoin[a-1] = true;          // dianggap benar
    hitung[a-1] = minimumKoin;
    return minimumKoin;         // nilai minimum koin
}
// Fungsi Utama
int main() {
    // inisialisasi var
    int harga, hitung;
    cin>>tc;                     // input banyak jenis uang
    for(int i=0; i<tc; i++) {
        cin>>koin[i];
    }
    cin>>harga;                 // input harga bahan makanan
    hitung = konversi(harga);   // masukkan ke nilai konversi untuk diubah ke uang yg sesuai
    if(hitung >= INT_MAX) {
        cout<<-1<<endl;         // jika tidak sesuai maka print -1
    } else {
        cout<<hitung<<endl;     // jika sesuai -> print perhitungan
    }
    return 0;
}