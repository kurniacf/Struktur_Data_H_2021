// Bismillah Isok
// Praktikum Final -> Cek Aja Gan
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
using namespace std;

bool cekSama = false;

// template github BST Tree
struct BSTNode {
    BSTNode *left, *right;
    long long key;
};
// inisialisasi struct
struct BST {
    BSTNode *_root;
    unsigned long long _size;
    // init
    void init() {
        _root = NULL;
        _size = 0u;
    }
    // cek apakah itu kosong
    bool isEmpty() {
        return _root == NULL;
    }
    // cek pencarian nilai node 
    bool find(long long value) {
        BSTNode *temp = __search(_root, value);     // masukkan untuk cari nilai
        if (!temp) {
            return false;
        }
        if (temp->key == value){
            return true;
        } else {
            return false;
        }
    }
    // fungsi masukkan nilai
    void insert(long long value) {
        if (!find(value)) {
            _root = __insert(_root, value);
            _size++;
        }
    }
private:
    // buat node
    BSTNode* __createNode(long long value) {
        BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    // fungsi cari nilai node
    BSTNode* __search(BSTNode *root, long long value) {
        while (root != NULL) {
            if (value < root->key)
                root = root->left;
            else if (value > root->key)
                root = root->right;
            else
                return root;
        }
        return root;
    }
    // fungsi masukkan nilai
    BSTNode* __insert(BSTNode *root, long long value) {
        if (root == NULL) {
            return __createNode(value);
        }
        if (value < root->key) {
            root->left = __insert(root->left, value);
        } else if (value > root->key){
            root->right = __insert(root->right, value);
        }
        return root;
    }
};
// Fungsi Utama
int main() {
    // inisialisasi struct
    BST set;
    set.init();         // jgn lupa init
    // inisialisasi variabel
    long long n, angka;
    cin>>n;           // input testcase
    // perulangan
    for(int i=0; i<n; i++) {
        cin>>angka;                     // input
        if(!cekSama) {                  // jika true masuk kesini
            if(set.find(angka)) {       // cari angka
                cekSama = true;         // jika ketemu gass true
            } else {
                set.insert(angka);      // jika engga insert aja ke bst
            }
        } else {
            continue;       // lanjut gass
        }
    }
    if(cekSama == true) {
        cout<<"G"<<endl;                // jika nilai true maka 'G'
    } else if (cekSama == false) {
        cout<<"Y"<<endl;                // jika nilai true maka 'Y'
    }
    return 0;
}