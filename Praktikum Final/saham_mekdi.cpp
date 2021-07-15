// Bismillah Isok
// Praktikum Final -> Saham Mekdi
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk (uva 11658 github)
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

// Fungsi Utama
int main() {
    // inisialisasi
    int n, m, saham[10001], a ,b;
    while(cin>>n>>m) {          // input jumlah pemegang saham & index pemegang saham yg dicari
        if(n == 0) {            // jika input 0 maka break
            break;
        }
        for(int i=0; i<n; i++) {
            scanf("%d.%d", &a, &b);
            a = a*100 + b; 
            saham[i] = a;
        }
        if(saham[m-1] > 5000) {
            cout<<"100.00"<<endl;
            continue;
        }
        int arr[10001] = {}, tmp = 10000-saham[m-1];
        arr[0] = 1;
        for(int i=0; i<n; i++) {
            if(i == m-1) {   
                continue;
            }
            for(int j=tmp-saham[i]; j>=0; j--) {
                if(arr[j]) {
                    arr[j+saham[i]] = 1;
                }
            }
        }
        tmp = 5001-saham[m-1];
        while(!arr[tmp])  {
            tmp++;
        }
        printf("%.2lf\n", (double)saham[m-1]*100/(tmp+saham[m-1]));
    }
    return 0;
}