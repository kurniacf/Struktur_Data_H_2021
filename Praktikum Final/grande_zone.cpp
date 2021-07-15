// Bismillah Isok
// Praktikum Final -> Grande Zone
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
// area of histogram
// fungsi penyelesaian (brute force)
int hitung(vector<int> bangunan) {
    int luasTotal, minimalLuas, current, tmp;            // inisialisasi variabel
    for(int i=0; i<bangunan.size(); i++) {              // perulangan perhitungan
        minimalLuas = bangunan[i];                      // cari nilai minimal terlbih dahulu dari pengecekan
        for(int j=i; j<bangunan.size(); j++) {
            minimalLuas = min(minimalLuas, bangunan[j]);        // cari nilai minimal dari bangunan dan perhitngan minimal luas
            current = j-i+1;                        // sebagai penanda index perhitungan
            tmp = current * minimalLuas;            // nilai sekarang dikalikan nilai minimal (panjang x lebar)
            luasTotal = max(tmp, luasTotal);        // cari nilai maximal luas bangunan total
        }
    }
    return luasTotal;
}
// Fungsi Utama
int main() {
    // inisialisasi
    int n, tinggi, hasil;
    while(cin>>n) {             // input testcase
        vector<int> bangunan;
        for(int i=0; i<n; i++) {
            cin>>tinggi;
            bangunan.push_back(tinggi);     // push ke list
        }
        hasil = hitung(bangunan);       // masukkan ke fungsi hitung bangunan
        cout<<hasil<<endl;          // print hasil
    }
}