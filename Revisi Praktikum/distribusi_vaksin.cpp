// Bismillah Isok
// Perbaikan Prektikum IV -> Distribusi Vaksin
// Kurnia Cahya Febryanto - 5025201073
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;
#define INFINITY 0x3f3f3f3f
typedef pair<int, int> graphPair;
int waktu, nextNode;
bool jejak;

// fungsi insert
void tambahEdge(vector <pair<int, int> > adj[], int titik1, int titik2, int waktu_tempuh) {
    adj[titik1].push_back(make_pair(titik2, waktu_tempuh));             // push back titik 1 
    adj[titik2].push_back(make_pair(titik1, waktu_tempuh));             // push back titik 2
}
// fungsi mencari total minimum waktu
void minimumWaktu(vector<pair<int,int> > adj[], int ruas, int node) {
    priority_queue< graphPair, vector <graphPair> , greater<graphPair> > graph;
    vector<int> jarak(ruas, INFINITY);
    vector<int> tanda;
    int hasil, bobot;
    graph.push(make_pair(0, node));     // push nilai pertama
    jarak[node] = 0;        
    jejak = false;          // dijadikan false sebagai penanda

    while (!graph.empty()) {
        int cek = graph.top().second;   // jadikan nilai top
        graph.pop();                    // ambil nilai
        // perulangan pengecekan
        for (auto tmp : adj[cek]) {     // batas sampai nilai cek habis
            hasil = tmp.first;
            bobot = tmp.second;
            if (jarak[hasil] > jarak[cek] + bobot) {        // jika nilai jarak hasil lebih besar daripada jarak yg dicek
                jarak[hasil] = jarak[cek] + bobot;          // maka nilai jarak cek ditampung ke jarak hasil 
                graph.push(make_pair(jarak[hasil], hasil)); // push jarak terbaru ke graph
                tanda.push_back(hasil);     // push tanda sebagai jejak (visited)
            }
        }
    }
    for (auto i : tanda) {              
        if(i == nextNode && !jejak) {
            jejak = true;               // jejak dijadikan true 
            waktu += jarak[i];          // terus bertambah hingga jarak terpenuhi
        }
    }
}
// Fungsi utama
int main() {
    // inisialisasi
    int jumlah_rumah, ruas_jalan, vaksin, titik1, titik2, waktu_tempuh;

    cin>>jumlah_rumah>>ruas_jalan>>vaksin;      // input jumlah rumah, ruas jalan, dan banyak vaksin

    vector<graphPair > adj[ruas_jalan];         // Adjacency List adalah ruas jalan sebagai list

    for(int i=0; i<ruas_jalan; i++) {
        cin>>titik1>>titik2>>waktu_tempuh;      // input titik1, titik2, dan waktu yg ditempuh (menit)
        tambahEdge(adj, titik1, titik2, waktu_tempuh); //tambahkan (insert nilai)
    }
    // rumah dan vaksin
    int rumah[vaksin];
    for (int i=0; i<vaksin; i++) {
        cin>>rumah[i];              // input nomor rumah 
    }
    for (int i=0; i<vaksin; i++) {
        if (i==vaksin-1) {       
            break;
        }
        nextNode = rumah[i+1];          // next node adalah rumah selanjutnya
        minimumWaktu(adj, ruas_jalan, rumah[i]);        // masukkan fungsi minimum waktu
    }   
    cout<<waktu<<endl;  // print nilai waktu minimum
    return 0;
}