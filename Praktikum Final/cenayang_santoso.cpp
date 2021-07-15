// Bismillah Isok
// Praktikum Final -> Cenayang Santoso
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
#include <set>
#include <cstring>
using namespace std;

// inisialisasi template github strukdat
vector<int>posisi;
struct BSTNodeTree {
    BSTNodeTree *left, *right;
    int key;
    bool cek = false;
};
// inisialisasi struct
struct BST {
    BSTNodeTree *_root;
    unsigned int _size;
    // init
    void init() {
        _root = NULL;
        _size = 0x0000FFFF;     // unsigned int
    }
    // cek apakah kosong
    bool isEmpty() {
        return _root == NULL;
    }
    // cari node
    bool find(int value) {
        BSTNodeTree *temp = __search(_root, value);
        if (!temp){
            return false;
        }
        if (temp->key == value){
            return true;
        } else {
            return false;
        }
    }
    // insert node
    void insert(int value) {
        if (!find(value)) {
            _root = __insert(_root, value);
            _size++;
        }
    }
    void inOrderTrans() {
        __inorder(_root);
    }
    // fungsi penghitungan sisi kiri
    void sisiKiri() {
        int levelMax = 0;
        sisiKiri(_root, true, &levelMax);
    }
    // fungsi penghitungan sisi kanan
    void sisiKanan() {
        int levelMax = 0;
        sisiKanan(_root, true, &levelMax);
    }
private:
    // fungsi penghitungan pada posisi kiri
    void sisiKiri(BSTNodeTree *root, int area, int *levelMax) {
        if (root == NULL){ 
            return;
        }
        if (*levelMax<area && area!=0) {
            root->cek = true;
            *levelMax = area;
        }
        sisiKiri(root->left, area+1, levelMax);     // hitung dengan memanfaatkan node kiri
        sisiKiri(root->right, area+1, levelMax);    // hitung dengan memanfaatkan node kanan
    }
    // fungsi penghitungan pada posisi kanan
    void sisiKanan(BSTNodeTree *root, int area, int *levelMax) {
        if (root == NULL) {
            return;
        }
        if (*levelMax<area && area!=0) {
            root->cek = true;
            *levelMax = area;
        }
        sisiKanan(root->right, area+1, levelMax);       // hitung dengan memanfaatkan node kanan
        sisiKanan(root->left, area+1, levelMax);        // hitung dengan memanfaatkan node kiri
    }
    // buat node baru
    BSTNodeTree* __createNode(int n) {
        BSTNodeTree *newNode = (BSTNodeTree*) malloc(sizeof(BSTNodeTree));
        newNode->key = n;
        newNode->left = newNode->right = NULL;
        newNode->cek = false;
        return newNode;
    }
    // fungsi cari node
    BSTNodeTree* __search(BSTNodeTree *root, int n) {
        while (root != NULL) {
            if (n < root->key){
                root = root->left;
            } else if (n > root->key){
                root = root->right;
            } else {
                return root;
            }
        }
        return root;
    }
    // insert node
    BSTNodeTree* __insert(BSTNodeTree *root, int n) {
        if (root == NULL){
            return __createNode(n);
        }
        if (n < root->key){
            root->left = __insert(root->left, n);
        } else if (n>root->key){
            root->right = __insert(root->right, n);
        }
        return root;
    }
    // fungsi pengutan inorder
    void __inorder(BSTNodeTree *root) {
        if (root != NULL) {
            __inorder(root->left);      // cek dari kiri
            if(!root->cek) {
                if(root->left || root->right) {
                    posisi.push_back(root->key);        // di push back
                }
            }
            __inorder(root->right);     // cek dari kanan
        }
    }
};
// Fungsi Utama
int main() {
    // inisialisasi
    BST set;
    set.init();     // jgn lupa init
    int orang, angka, tmp;
    cin>>orang;             // input banyak org
    for(int i=0; i<orang; i++) {
        cin>>angka;             // input angk
        set.insert(angka);      // insert ke node
    }
    // masukkan ke fungsi perhitungan
    if(angka>0 && angka!=0){        // jika angka tidak 0
        set.sisiKiri();             // hitung sisi kiri
        set.sisiKanan();            // hitung sisi kanan
    }
    // per-list-an
    set.inOrderTrans();     // diurutkan secara inorder
    tmp = posisi.size();
    if(tmp>0 && (tmp != NULL)) {
        for(int i=0; i<tmp; i++) {
            cout<<posisi[i];       // print hasil posisi
            cout<<" ";
        }
    } else if (tmp==0 || tmp<=-1) {
        cout<<"Yah, gk ada posisi yang aman :("<<endl;      // print
    }
    return 0;
}

// 16
// 60 54 10 56 57 58 66 62 70 78 67 5 7 13 11 16
// 56