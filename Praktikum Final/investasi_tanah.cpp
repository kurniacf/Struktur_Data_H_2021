// Maximum sum rectangle in a 2D matrix --> GFG
// Bismillah Isok
// Praktikum Final -> Investasi Tanah 2
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
// inisialisasi
int lahan[10001][10001] , tmp[10001];
// fungsi untuk mencari nilai maksimal
int hitungMaksimal(int n) {
	// inisialisasi
    int hasil=INT_MIN, point=0;
    bool cek = false;
    for(int i=0; i<n; i++) {
        if(tmp[i]>=0) {
			cek = true;
		}
        point = point+tmp[i];		// penambahan nilai poin sebagai cek poin sementara
        if(point<0) {
            point=0;
        } else if(point>hasil) {
            hasil = point ;				// hasil == nilai akumulasi poin 
        }
    }
    if(cek) {
		return hasil;
	}
    hasil = INT_MIN;
    for(int i=0; i<n; i++) {
        if(hasil<tmp[i]) {
            hasil = tmp[i] ;
        }
    }
    return hasil ;
}
// fungsi mencari potensi maksimal suatu lahan matrix
void potensiMaksimal(int area) {
    int maxTotal=INT_MIN, hasil = 0;
    for(int kiri=0; kiri<area; kiri++) {			// hitung dari kiri
        fill(tmp, tmp+10001, 0);				// untuk mendefinisikan karakter pengisi dari sisa panjang karakter yang ada
        for(int kanan=kiri; kanan<area; kanan++) {	// hitung sisi kanan
            for(int i=0; i<area; i++) {
				tmp[i]+=lahan[i][kanan];
			}
            hasil=hitungMaksimal(area);			
            if(hasil > maxTotal) {
                maxTotal = hasil ;
            }
        }
    }
    cout<<maxTotal<<endl;			// print nilai max
}
// Fungsi Utama
int main() {
	// inisialisasi variabel
    int n; 
    while(cin>>n) {				// input tc kolom dan baris
        for(int i=0; i<n; i++) {		// representasi kolom
            for(int j=0; j<n; j++) {		// representasi baris
				cin>>lahan[i][j];		// isikan lahan
            }
        }
        potensiMaksimal(n);			// masukkan ke fungsi potensi maksimal tanah
    }
    return 0;
}