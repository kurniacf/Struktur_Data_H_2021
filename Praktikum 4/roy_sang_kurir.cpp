// BISMILLAH ISOK
// Referensi: Youtube, Github, Internet
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <array>
#include <queue>
using namespace std;

template<typename GR>
// Deklarasi Graph
class Graph{
    // inisialisasi graph
    int V;
    bool cekCycle;
    map<GR, list<GR> > dekatList;

public:
    Graph(int v){
        V = v;
    }
    // fungsi tambah edge
    void tambahEdge(GR u, GR v, bool cek){
        cek = true;
        dekatList[u].push_back(v);      // masukkan dari belakang
        if(cek){
            dekatList[v].push_back(u);
        }
    }
    // fungsi cycle graph
    bool cycleGraph(GR node, map<GR, bool> &visit, GR parent){
        visit[node] = true;
        for(GR tetangga:dekatList[node]){
            if(visit[tetangga]==0){
                cekCycle = cycleGraph(tetangga, visit, node);
                if(cekCycle){
                    return true;
                }
            } else if(tetangga!=parent){
                return true;
            }
        }
        return false;
    }
    bool cekCyleDFS(){
        map<GR, bool> visit;
        // for( int* ip = &input[0]; ip< &input[input.size()-1]; ip++)
        for(auto i:dekatList){
            GR node = i.first;
            if(visit[node]==0){
                bool tmp = cycleGraph(node,visit,node);
                if(tmp==true){
                    return true;
                }
            }
        }
        return false;
    }
};
// Fungsi Utama
int main(){
    // inisialisasi
    int tc, m, n;
    cin>>tc;            // input testcase
    Graph<int> g(tc);
    // perulangan input
    for (int i=0; i<tc; i++){
        bool cek = true;
        cin>>m>>n;
        g.tambahEdge(m, n, cek);
    }
    // pengecekan cycle graph
    if(g.cekCyleDFS()){
        cout<<"Ada Cycle!"<<endl;
    } else{
        cout<<"Tidak Ada Cycle!"<<endl;
    }
    return 0;
}
