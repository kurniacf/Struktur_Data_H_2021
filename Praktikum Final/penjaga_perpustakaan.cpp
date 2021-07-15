// Bismillah Isok
// Praktikum Final -> Penjaga Perpustakaan
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk (uva 230 - Borrowers)
// https://sjsakib.github.io/psbook/03-stl/exercises/uva230.html
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <cstdio>
using namespace std;

// inisialisasi
vector<pair<string, string> > semuaBuku;
map<string, bool> pinjam;
map<string, bool> kembali;

int main() {
    char buku[1001], penulis[1001];
    while (scanf("\"%[^\"]\" by %[^\n]\n", buku, penulis)) {
        semuaBuku.push_back(make_pair(penulis, buku));          // masukkan nilai buku
        pinjam[buku] = 0;
        kembali[buku] = 0;
    }
    sort(semuaBuku.begin(), semuaBuku.end());           // urutkan

    scanf("%s\n", buku);       
    // END
    
    while (scanf("%s ", buku)) {  // using 'buku' as buffer to read the command
        string cmd(buku);
        if (cmd == "END") {
            break;
        }
        if (cmd == "URUTKAN") {
            string akhir;
            for (auto b: semuaBuku) {
                if(!pinjam[b.second]) {
                    akhir = b.second;
                } else if(kembali[b.second]) {
                    if(akhir.length()) {
                        printf("Put \"%s\" after \"%s\"\n", b.second.c_str(), akhir.c_str());
                    } else {
                        printf("Put \"%s\" first\n", b.second.c_str());
                    }
                    pinjam[b.second] = 0;
                    akhir = b.second;
                }
            }
            printf("END\n");
            kembali.clear();
            continue;
        }
        // pengecekan
        scanf("\"%[^\"]\"\n", buku);
        if (cmd == "PINJAM") {
            pinjam[buku] = 1;
        } else if (cmd == "KEMBALI") {
            kembali[buku] = 1;
        }
    }
    return 0;
}