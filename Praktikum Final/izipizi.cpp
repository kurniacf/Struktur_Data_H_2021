// Bismillah Isok
// Praktikum Final -> Izipizi 4
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

// inisialisasi struct 
struct Sisi {
    int baris, kolom, harga;
    bool operator>(const Sisi &cek) const {
        // if (baris.harga == kolom.harga) {
        //     if (baris.x != kolom.x){
        //         return (baris.x < kolom.x);
        //     } else{
        //         return (baris.y < kolom.y);
        //     }
        // }
        // return (a.harga < b.harga);
        return this->harga > cek.harga;
    }
};
// Fungsi Utama
int main() {
    // inisialisasi
    int query;
    cin>>query;
    for(int i; i<query; i++) {
        // inisialisasi
        Sisi jalan;
        int banyak_baris, banyak_kolom, baris, kolom;
        cin>>banyak_baris>>banyak_kolom;                // input banyak baris dan kolom 

        vector<vector<int> > query(banyak_baris, vector<int>(banyak_kolom));        // dijadikan vektor
        for (int baris=0; baris<banyak_baris; baris++) {
            for (int kolom=0; kolom<banyak_kolom; kolom++) {
                cin>>query[baris][kolom];
                //query[banyak_baris][banyak_kolom] = INT_MAX;
            }
        }
        // jadikan 0 setiap perhitungan
        jalan.baris = 0;
        jalan.kolom = 0;
        jalan.harga = query[0][0];

        priority_queue<Sisi, vector<Sisi>, greater<Sisi> > pque;        // menggunakan priority
        vector<vector<int> > harga(banyak_baris, vector<int>(banyak_kolom, -1));

        pque.push(jalan);               // push nilai jalan
        harga[0][0] = jalan.harga;
        // rumus matrix map
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        
        while (!pque.empty()) {
            Sisi jln = pque.top();      // arahkan ke atas
            pque.pop();                 // ambil nilai
            for (int j=0; j<4; j++) {
                baris = jln.baris + dx[j];
                kolom = jln.kolom + dy[j];
                if (baris<0 || kolom<0 ) {
                    // jln.baris = 0;
                    // jln.kolom = 0;
                    continue;
                }
                if (baris>=banyak_baris || kolom>=banyak_kolom){
                    continue;
                }
                if (harga[baris][kolom] == -1) {
                    harga[baris][kolom] = harga[jln.baris][jln.kolom] + query[baris][kolom];            // masukkan hasil penjumlahan
                    jalan.baris = baris;
                    jalan.kolom = kolom;
                    jalan.harga = harga[baris][kolom];
                    pque.push(jalan);       // push ke priority queue
                } else if (harga[jln.baris][jln.kolom] + query[baris][kolom] < harga[baris][kolom]) {
                    harga[baris][kolom] = query[baris][kolom] + harga[jln.baris][jln.kolom];
                    jalan.baris = baris;
                    jalan.kolom = kolom;
                    jalan.harga = harga[baris][kolom];
                    pque.push(jalan);       // push ke priority queue
                }
            }
        }
        cout<<harga[banyak_baris-1][banyak_kolom-1]<<endl;        // print harga
    }
    return 0;
}