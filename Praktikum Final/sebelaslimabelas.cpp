// Bismillah Isok
// Praktikum Final -> Sebuah Cerita Tentang 11 dan 15
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk (Chicken McNugget Theorema)
// https://github.com/dawiditer/MIT600-pset2
// https://artofproblemsolving.com/wiki/index.php/Chicken_McNugget_Theorem
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
// in C -> fix runtime

vector<long long> angka;
// fungsi perhitungan dengan rumus Chicken McNugget
void angkaNugget(){
    long long batasAngka;
    // perhitungan
    for(int i=0; i<=14; i++){    
        for(int j=0; j<10; j++){
            batasAngka = 11*i + 15*j;       // rumus pehitungan 11 dan 15
            if(batasAngka>=140) {
                continue;
            }
            angka.push_back(batasAngka);
        }
    }
}
// print hasil
void printHasil(bool a){
    if(a == true) {
        printf("YES\n");
    } else if (a == false){
        printf("NO\n");
    }
}
// fungsi pengecekan Angka
void cekAngka(int tc){
    long long bilangan;
    for(int i=0; i<tc; i++){
        bool cek = false;
        scanf("%lld", &bilangan);          // input bilangan
        if(bilangan >= 140){
            cek = 1;
        } else{
            if(find(angka.begin(), angka.end(), bilangan) != angka.end()){
                cek = 1;
            }
        } 
        printHasil(cek);        // print hasil
    }
}

// Fungsi Utama
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // inisialisasi
    int tc;
    scanf("%d", &tc);            // input tc
    angkaNugget();      // masukkan ke perhitungan
    cekAngka(tc);       // pengecekan angka
    return 0;
}

// Chicken McNugget Theorem
// (m-1)(n-1)/2  -> pair (k, mn-m-n-k)
// ekspresi bilangan -> am + bn
// gcd(m, n)(a(m/gcd(m,n)+b(n/gcd(m,n)))
