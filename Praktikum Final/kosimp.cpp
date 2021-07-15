// Bismillah Isok
// Praktikum Final -> Kosimp
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

// inisialisasi BST (Template Github STrukdat)
typedef struct bstnode_t {
    unsigned long long key, top, min;
    struct bstnode_t
        *left,
        *right, *parent;
}BSTNode;
// struct BST
typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
}BST;
// buat node BST
BSTNode *__bst__createNode(int value, int top) {
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->top = top;
    newNode->min = LONG_MAX;
    newNode->parent = newNode->left = newNode->right = NULL;
    return newNode;
}
// insert Node
BSTNode *__bst__insert(BSTNode *root, int value, int top) {
    if (root == NULL){
        return __bst__createNode(value, top);
    }
    if (value < root->key) {
        root->left = __bst__insert(root->left, value, top);
        root->left->parent = root;
    } else if (value > root->key) {
        root->right = __bst__insert(root->right, value, top);
        root->right->parent = root;
    }
    return root;
}
// cari nilai node
BSTNode *__bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key){
            root = root->left;
        } else if (value > root->key){
            root = root->right;
        } else {
            return root;
        }
    }
    return root;
}
// cari nilai minimal 
void __minimalJarak(BSTNode *root) {
    if (root == NULL){
        root->parent==NULL;
    }
    // jika memiliki root
    if (root) {
        __minimalJarak(root->left);         // kiri
        __minimalJarak(root->right);        // kanan
        if (root->left == NULL && root->right == NULL) {        // pengecekan kanan kiri node
            root->min = 0;
        }
        if (root->parent != NULL && root->parent->min > root->top + root->min) {     // pengecekan melalui parent
            root->parent->min = root->top + root->min;
        }
    }
}
// cari minimal paling minimal diantara yg lain
void minTotal(BSTNode *root) {
    if (root) {
        if (root->parent != NULL && root->min > root->parent->min + root->top) {
            root->min = root->parent->min + root->top;
        }
        minTotal(root->left);
        minTotal(root->right);
    }
}
// fungsi init
void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}
// cek apakah kosong
bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}
bool bst_findmin(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;

    if (temp->key == value) {
        printf("%llu", temp->min);
        return true;
    } else
        return false;
}
// insert node BST
void bst_insert(BST *bst, int value, int top) {
    bst->_root = __bst__insert(bst->_root, value, top);
    bst->_size++;
}
// fungsi cari minimal jarak
void minimalJarak(BST *bst) {
    __minimalJarak(bst->_root);
}
// fungsi cari total minimal
void totalMinimal(BST *bst) {
    minTotal(bst->_root);
}
// Fungsi Utama
int main() {
    // inisialisasi
    BST set;
    bst_init(&set);     // jgn lupa init
    int banyak_node, root;          // input banyak node dan root
    long long nomorNode, jarakNode, cari, tc;
    bool cek;
    cin>>banyak_node>>root;
    bst_insert(&set, root, 0);      // masukkan ke insert
    banyak_node--;
    // perulangan
    for(int i=0; i<banyak_node; i++) {
        cin>>nomorNode>>jarakNode;
        bst_insert(&set, nomorNode, jarakNode);       // masukkan ke insert
    }
    // fungsi perhitungan
    minimalJarak(&set);
    totalMinimal(&set);
    // input testcase
    cin>>tc;
    for(int i=0; i<tc; i++) {
        cin>>cari;
        cek = __bst__search(set._root, cari);
        if(cek != NULL){
            bst_findmin(&set, cari);            // pengecekan apakah ada node yg diinginkan 
        } else {
            cout<<"0";          // jika tidak ada maka jadikan 0
        }
        cout<<endl;
    }
    return 0;
}