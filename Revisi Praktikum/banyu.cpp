// Bismillah Isok
// Perbaikan Prektikum II -> Banyu
// Kurnia Cahya Febryanto - 5025201073
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <climits>
using namespace std;

int minimal_length=INT_MAX;
int maksimal_length=INT_MAX;

struct TreeNodeBST {
    TreeNodeBST *arr[5000], *pastNode;  // pastNode = node lama sebelum curr node
    int jarak[5000], size, currNode;
    bool kunjungan = false;
};

struct BST {
    TreeNodeBST *_root;
    unsigned int _size;
    // fungsi init
    void init() {
        _root = NULL;
        _size = 0u;
    }
    // fungsi cek apakah kosong
    bool isEmpty() {
        return _root == NULL;
    }
    // fungsi insert nilai ke node
    void insert(int parent, int child, int jarak) {
        TreeNodeBST *cek = cariParent(_root, parent);       // cek apakah parent ada
        if(cek) {
            buatChildNode(cek, child, jarak);               // masuk ke fungsi buat childNode
        } else {
            _root = buatRoot(parent, child, jarak);         // masuk ke fungsi buat root
        }
        if(_root->currNode == parent) {
            _root->arr[_root->size]->jarak[parent]=jarak;
        }
    }
    
    void cariDaun (int cek) {
        minimal_length=INT_MAX;
        maksimal_length=INT_MAX;
        TreeNodeBST* nodeAsal =  cariParent(_root, cek);
        minimumDaun(nodeAsal, 0, NULL);       // masukkan ke fungsi caro path minimum
        resetTree(_root);
    }
    // fungsi cari nilai minimum path pada daun
    void minimumDaun (TreeNodeBST *root, int cekNode, TreeNodeBST *prev) {
        int cek = 0;
        if(root && root->kunjungan==false){
            if(root->size==0){                                  // jika ukuran size sesuai
                if(cekNode <= maksimal_length){                 // jika nilai kurang dari panjang maksimal maka
                    if(cekNode < maksimal_length){              // jika kurang maka nilai minimal adalah current node sekarang
                        minimal_length = root->currNode;
                    } else if(cekNode == maksimal_length) {     // jika nilai sama dengan panjang maksimal 
                        if(root->currNode < minimal_length){
                            minimal_length = root->currNode;    // nilai minimal adalah current node 
                        }
                    }
                    maksimal_length = cekNode;      
                }
                return;
            } else {
                for(int i=1; i<=root->size; i++) {
                    if(root->arr[i] != prev){               // jika nilai array tidak sama dengan sebelumnya
                        root->kunjungan = true;
                        cek = cekNode + root->jarak[root->arr[i]->currNode];        // maka cekNode akan ditambah dengan nilai currNode sesuai rootnya
                        minimumDaun (root->arr[i], cek, root);          // ulangi lagi ke fungsi
                    }
                }
                if(root->pastNode != NULL){
                    if(root->pastNode->kunjungan==false) {
                        cek = cekNode + root->jarak[root->pastNode->currNode];
                        root->kunjungan = true;
                        minimumDaun (root->pastNode, cek, root);        // ulangi lagi
                    }
                }
            }
        } else {
            return;
        }
    }
    // fungsi untuk menghapus perhitungan kunjungan yg dilakukan
    void resetTree(TreeNodeBST *root)  {
        if(root==NULL) {
            return;
        } else {
            root->kunjungan= false;                 // nilai kunjungan dijadikan false
            for(int i=1; i<=root->size;i++) {
                resetTree(root->arr[i]);            // berurutan sesuai visitnya
            }
        }
        return;
    }

private:
    // Fungsi cari Parent
    TreeNodeBST* cariParent(TreeNodeBST *root, int value) {
        if(root==NULL) {            // jika kosong return null
            return NULL;
        }
        if(root->currNode==value) {      // jika parent berada di root return root
            return root;
        }
        for(int i=1; i<=root->size;i++) {       // pengecekan parent di tiap-tiap node
            TreeNodeBST *tmp = cariParent(root->arr[i], value);
            if(tmp == NULL) {
                return NULL;
            } else if(tmp->currNode == value) {     
                return tmp;
            }
        }
        return root;
    }
    // fungsi buat child node
    TreeNodeBST* buatChildNode(TreeNodeBST *root, int child, int jarak) {
        TreeNodeBST *cek = (TreeNodeBST*) malloc(sizeof(TreeNodeBST));
        root->arr[++root->size] = cek;
        root->jarak[child] = jarak; // masukkan nilai jarak
        cek->currNode = child;      // masukkan nilai child
        cek->pastNode = root;       // masukkan nilai root ke pastNode
        cek->jarak[root->currNode] = jarak;
        cek->size = 0;              // size diatur 0

        for(int i=0; i<=301; i++){      // batas constraint di soal -> 300
            cek->arr[i]=NULL;       
        }
        return cek;
    }
    // fungsi buat root node
    TreeNodeBST* buatRoot(int parent, int child, int jarak) {
        // inisialisasi
        TreeNodeBST *parentNode = (TreeNodeBST*) malloc(sizeof(TreeNodeBST));
        TreeNodeBST *childNode = (TreeNodeBST*) malloc(sizeof(TreeNodeBST));
        // parentNode
        parentNode->pastNode = NULL;            // nilai dainggap null karena pertama
        parentNode->currNode= parent;           // nilai sekarang 
        parentNode->size = 1;                   // bernilai satu karena parent adalah akarnya(lebih dulu ada dibanding child)
        parentNode->jarak[child] = jarak;       // masukkan nilai jarak
        parentNode->arr[1] = childNode;
        // childNode
        childNode->pastNode = parentNode;       // mengambil nilai parent (sebelumnya)
        childNode->currNode = child;            // nilai child node
        childNode->size = 0;                    // bernilai 0 karena child bisa ada ataupun tidak
        childNode->jarak[parent]= jarak;             // nilai jarak

        for(int i=0;i<=400;i++)
            childNode->arr[i]=NULL;
        return parentNode;
    }
};

// Fungsi Utama
int main() {
    // inisialisasi
    BST set;
    set.init();
    int n, m, sumberAir, a, b, c, titikAir;

    cin>>n>>m;      // input titik & batang

    for(int i=0; i<m; i++) {
        cin>>a>>b>>c;
        set.insert(a,b,c);      // masukkan ke node tree
    }
    cin>>sumberAir;         // input jumlah sumber air yg dimau
    for(int i=0; i<sumberAir; i++) {
        cin>>titikAir;          // input titik air
        set.cariDaun(titikAir); // masukkan ke fungsi cari
        cout<<minimal_length<<endl;
    }
    return 0;
}
