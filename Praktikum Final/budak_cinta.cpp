// Bismillah Isok
// Praktikum Final -> Budak Cinta
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk
// https://github.com/nardiyansah/DFS-BFS
// https://github.com/liondy/8-Puzzle
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <set>
#include <cstring>
using namespace std;

vector<pair<long long, long long>> *jln, sisi;

long long cariJalanBFS(pair<long long,long long> sisi, int n) {
    long long kota1 = sisi.first, kota2 = sisi.second, hasil = 0;
    vector<bool> teleport(n, 0);
    queue<long long> node;
    teleport[kota2] = true; node.push(kota2);
    while(node.empty() == 0) {
        long long curr = node.front();
        node.pop();
        hasil++;
        for(auto i=jln[curr].begin(); i != jln[curr].end(); i++) {
            if(!teleport[(*i).second] && (curr != kota2 || (*i).second != kota1) && (curr != kota1 || (*i).second != kota2)) {
                teleport[(*i).second] = true;
                node.push((*i).second);
            } 
        }
    }
    return hasil;
}
// fungsi print hasil
void printHasil(long long int **jarak){
    int a, b, tc;
    cin>>tc;
    for (int i=0; i<tc; i++) {
        cin>>a>>b;              // input 
        a--; 
        b--;
        cout<<jarak[a][b]<<endl;      // print hasil
    }  
}

// Fungsi Utama 
int main() {
    // inisialisasi
    int city, jalan, tc;           // input city dan jalan
    long long int cek, hasil, ruas, tmp, nextCity, kota1, kota2, **jarak;
    cin>>city>>jalan;
    sisi.resize(jalan);        // atur ukuran
    jln = new vector<pair<long long,long long>>[city];         // inisialisasi jaalan dengan vektor
    for(int i=0; i<jalan; i++) {
        cin>>kota1>>kota2>>ruas;
        kota1--,
        kota2--;
        sisi[i] = make_pair(kota1, kota2);              // buat pair baru dari kota 1 dan 2
        jln[kota2].push_back(make_pair(ruas, kota1));   // push aja
        jln[kota1].push_back(make_pair(ruas, kota2));   // push
    }
    jarak = new long long*[city];           // representasi city
    for(int i=0; i<city; i++){
        jarak[i]= new long long[city];      // 
    }
    set<pair<long long, long long>> jalanHubung;        // set pair
    for(int i=0; i<jalan; i++) {
        cek = sisi[i].first; 
        kota2 = sisi[i].second;
        hasil = cariJalanBFS(sisi[i], city);
        if (city != hasil) {
            jalanHubung.insert(make_pair(max(cek, kota2), min(cek, kota2)));        // buat pair dari pengecekan maksimal dan minimal kota
        }
    }
    for(int i=0; i<city; i++) {
        set<long long> teleport;
        priority_queue <pair<long long,long long>, vector <pair<long long,long long>>, greater <pair<long long,long long>>> query;
        memset(jarak[i], -1, sizeof(long long)*city); // mengatur memori wilayah untuk 0 terlepas dari tipe data
        
        jarak[i][i] = 0; 
        query.push({0, i});
        while (query.empty() == false) {
            pair<long long, long long> current;         // buat pair
            current = query.top();
            query.pop();                    // ambil nilai
            
            teleport.insert(current.second);        // insert masukkan ke set

            for (int j=0; j<(long long)jln[current.second].size(); j++) {
                tmp = jln[current.second][j].first;
                nextCity = jln[current.second][j].second;
                if (!((jalanHubung.find(make_pair(current.second, nextCity)) != jalanHubung.end()) || (jalanHubung.find(make_pair(nextCity, current.second)) != jalanHubung.end()))) {
                    tmp = 0;
                }
                if (jarak[i][nextCity] > (tmp+current.first) ) {        // cek jarak 
                    jarak[i][nextCity] = current.first + tmp;
                    query.push({jarak[i][nextCity], nextCity});
                } else if (jarak[i][nextCity] == -1) {
                    jarak[i][nextCity] = tmp + current.first;
                    query.push({jarak[i][nextCity], nextCity});
                }
            }
        }
    }
    printHasil(jarak);      // print hasil
    return 0;
}