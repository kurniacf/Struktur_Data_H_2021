// Bismillah Isok
// Referensi Youtube, Intenet, Github
#include <iostream>
#include <map>
#include <queue>
#include <list>
#include <vector>
using namespace std;

// breadth first search -> memperluas, memeriksa simpul graf
void bfs(vector<int> graph[], bool visit[], int node) {
    queue<int> m;       // inisialisasi m queue
    int curNode, nextNode, panjang=0;
    m.push(node);       //push
    visit[node] = true;    // nilai pertama == true
    
    while (!m.empty()) {
        curNode = m.front();            // cek dari depan
        panjang = graph[curNode].size();    // panjang curNode
        m.pop();    // ambil nilai
        m.empty();   // hapus nilai
        for (int i=0 ; i<panjang; i++) {
            nextNode = graph[curNode][i];       // nilai nextNode 
            if (!visit[nextNode]) {             // jika memiliki nilai visit
                m.push(nextNode);               // maka push
                visit[nextNode] = true; // tetep jadikan visit true
            }
        }
    }
}
// Fungsi pengitung
int jumlahJembatan(vector<int> graph[], bool visit[], int node) {
    // inisialisasi
    queue<int>queue;
    int jembatan=0, tmp=0;
    queue.push(true);
    
    do {
        tmp=queue.front();
        bfs(graph, visit, tmp); // masukkan ke bfs
        queue.pop();        // ambil nilai
        for(int i=tmp; i<=node; i++) {
            if(!visit[i]) {
                queue.push(i);
                jembatan++;
                break;
            }
        }
    } while (!queue.empty());
    return jembatan;
}

// Fungsi Utama
int main() {
    // inisialisasi
    int pulau, jembatan, a, b;
    cin>>pulau>>jembatan;
    // menghitung pulau
    vector<int> graph[pulau+5];         // pulau+5 agar array muat
    bool visit[pulau+5];                // pengecekan kebenaran
    for(int i=0; i<jembatan; i++) {
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cout<<jumlahJembatan(graph, visit, pulau)<<endl;
    return 0;
}