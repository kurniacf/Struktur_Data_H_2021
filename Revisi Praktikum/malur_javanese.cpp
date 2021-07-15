// Bismillah Isok
// Perbaikan Praktikum IV -> Malur Javanese
// Kurnia Cahya Febryanto - 5025201073
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
// fungsi perhitungan (rumus)
long double biaya_minimum(long double x, long double y, long double tingkat){
    long double a = pow(x,2);
    long double b = pow(y,2);
    // rumus = akar ((delta x kuadrat) + (delta y kuadrat)) * tingkat
    return sqrt(a+b)*tingkat;
}
// fungsi utama
int main(){
    // inisialisasi  variabel
    int tc, node = 0;              
    long double x, y, tingkat, currJalan, cari_jalan, hasil = 0;
    vector<vector<long double>> GR;
    vector<int> jalan;
    cin>>tc;                    // input testcase

    bool kunjungan[tc];
    for(int i=0; i<tc; i++){
        cin>>x>>y>>tingkat;         // input posisi dan tingkat kerumitan
        GR.push_back({x, y, tingkat});      // masukkan ke graph 
        kunjungan[i] = false;           // menjadikan tiap kunjungan(history menjadi false) setiap inputan
    }

    jalan.push_back(0);             
    kunjungan[0] = true;                // sebagai pengecekan kunjungan(history) menjadi true
    
    while(jalan.size() < tc){           // selama size jalan kurang dari testcase maka
        currJalan =  INT_MAX;           // sebagai batas
        for(int i=0; i<jalan.size(); i++){  
            for(int j=0; j<tc; j++){
                if(!kunjungan[j]){          // jika kunjungan 
                    // masukkan ke fungsi hitung jalan 
                    cari_jalan = biaya_minimum(
                                GR[j][0]-GR[jalan[i]][0], 
                                GR[j][1]-GR[jalan[i]][1], 
                                abs(GR[j][2]-GR[jalan[i]][2]));         
                    if(cari_jalan < currJalan){         // nilai jalan yg dicari lebih kecil dari pengecekan jalan sekarang maka
                        node = j;
                        currJalan = cari_jalan;
                    }
                }
            }
        }
        hasil += currJalan;         // nilai hasil terus bertambah dengan currJalan sesuai kondisi
        jalan.push_back(node);
        kunjungan[node] = true;     // pengecekan dijadikan true
    }
    cout<<fixed<<setprecision(6)<<hasil<<endl;      // print hasil
    return 0;
}