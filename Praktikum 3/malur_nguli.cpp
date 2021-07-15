// BISMILLAH ISOK
// Program AVL insert dan print penjumlahan vertikal node
// Referensi : Internet, Github Strukdat, Youtube
#include<iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;
// Struct AVL (Template Github)
struct AVLNode {
    int data;
    AVLNode *left, *right;
    int height;
};
// inialisasi
int pos[1001];
int neg[1001];
int leftPart;
//int tmp = 0;
// struct
struct AVL {
private:
    AVLNode *_root;
    unsigned _size;
    // membuat node
    AVLNode* _avl_createNode(int value) {
        AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
        newNode->data = value;
        newNode->height =1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    // fungsi pencarian 
    AVLNode* _search(AVLNode *root, int value) {
        while (root != NULL) {
            if (value < root->data) {
                root = root->left;
            } else if (value > root->data) {
                root = root->right;
            } else {
                return root;
            }
        }
        return root;
    }
    // mencari level/tinggi node
    int _getHeight(AVLNode* node){
        if(node==NULL)
            return 0; 
        return node->height;
    }
    // fungsi max
    int _max(int a,int b){
        return (a > b)? a : b;
    }
    // rotasi kanan
    AVLNode* _rightRotate(AVLNode* pivotNode){
        AVLNode* newParrent=pivotNode->left;
        pivotNode->left=newParrent->right;
        newParrent->right=pivotNode;
        pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
        newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
        return newParrent;
    }
    // rotasi kiri
    AVLNode* _leftRotate(AVLNode* pivotNode) {
        AVLNode* newParrent=pivotNode->right;
        pivotNode->right=newParrent->left;
        newParrent->left=pivotNode;
        pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
        newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
        return newParrent;
    }
    // pattern
    AVLNode* _leftCaseRotate(AVLNode* node) {        // skewed kiri (L-L case)
        return _rightRotate(node);
    }
    AVLNode* _rightCaseRotate(AVLNode* node) {       // skewed kanan (R-R case)
        return _leftRotate(node);
    }
    AVLNode* _leftRightCaseRotate(AVLNode* node){   // zigzag kiri (L-R case)
        node->left=_leftRotate(node->left);
        return _rightRotate(node);
    }
    AVLNode* _rightLeftCaseRotate(AVLNode* node){   // zigza kanan (R-L case)
        node->right=_rightRotate(node->right);
        return _leftRotate(node);
    }
    // fungsi penyeimbang
    int _getBalanceFactor(AVLNode* node){
        if(node==NULL) {
            return 0;
        }
        return _getHeight(node->left)-_getHeight(node->right);
    }
    // fungsi input nilai
    AVLNode* _insert_AVL(AVLNode* node,int value) {
        if(node==NULL) {
            return _avl_createNode(value);
        }
        if(value < node->data) {
            node->left = _insert_AVL(node->left,value);
        } else if(value > node->data) {
            node->right = _insert_AVL(node->right,value);
        }
        node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 
        // inisialisasi
        int balanceFactor=_getBalanceFactor(node);
        // pengecekan
        if(balanceFactor > 1 && value < node->left->data){
            return _leftCaseRotate(node);
        }
        if(balanceFactor > 1 && value > node->left->data){
            return _leftRightCaseRotate(node);
        }
        if(balanceFactor < -1 && value > node->right->data){
            return _rightCaseRotate(node);
        }
        if(balanceFactor < -1 && value < node->right->data){
            return _rightLeftCaseRotate(node);
        }
        return node;
    }
    //cari nilai
    AVLNode* _findMinNode(AVLNode *node) {
        AVLNode *currNode = node;
        while (currNode && currNode->left != NULL) {
            currNode = currNode->left;
        }
        return currNode;
    }
    // fungsi hitungNilai
    void totalNilai(AVLNode *node, int cek) {
        if(node) {  // jika ada node gass
            // pengecekan
            if(cek==0) {    // jika bernilai nol
                pos[0]+=node->data; // mengembalikan nilai itu sendiri
            } else if(cek<0) {
                if(abs(cek)>leftPart) { // menggunakan absolute 
                    leftPart++;         // menghitung bagian kiri dan panjang nodenya akan bertambah jika ada
                }
                neg[abs(cek)]+=node->data;  // tambahkan
            } else if(cek>0) {
                pos[cek]+=node->data;
            }
            totalNilai(node->left, cek-1);
            totalNilai(node->right, cek+1);
        }
    }
public:
    // init 
    void init() {
        _root = NULL;
        _size = 0U;
    }
    // cek apakah kosong
    bool isEmpty() {
        return _root == NULL;
    }
    // cek nilai
    bool find(int value) {
        AVLNode *temp = _search(_root, value);
        if (temp == NULL) {
            return false;
        }
        if (temp->data == value) {
            return true;
        } else {
            return false;
        }
    }
    // masukkan nilai
    void insert(int value) {
        if (!find(value)) {
            _root = _insert_AVL(_root, value);
            _size++;
        }
    }
     // cek penjumlahan
    void jumlah() {
        for(int i=0; i<=999; i++) {     // batas 1001 --> 999 dua space untuk left dan right
            pos[i]=0;
            neg[i]=0;
        }
        this->totalNilai(_root, 0);
    }
    // fungsi cek kolom bagian kiri
    int kolomKiri() {
        int tmp=0;
        AVLNode *currNode = _root;  // arahkan currNode dengan nilai root
        while (currNode && currNode->left != NULL) {     // jika node sebelah kiri root tidak kosong
            currNode = currNode->left;          // nilai curr menjadi nilai node tersebut
            tmp++;                  // maka tmp berlanjut
        }
        return tmp;     // mengembalikan panjang node yg sekolom
    }
    // fungsi cek kolom bagian kanan
    int kolomKanan() {
        int tmp=0;          // inisialisasi jadi nol
        AVLNode *currNode = _root;      // arahkan currNode dengan nilai root
        while (currNode && currNode->right != NULL) {       // jika node sebelah kanan root tidak kosong
            currNode = currNode->right;         // nilai curr menjadi nilai node tersebut
            tmp++;           // maka tmp berlanjut
        }
        return tmp;     // mengembalikan panjang node yg sekolom
    }
};
// Fungsi Utama 
int main() {
    // init struct
    AVL set;
    set.init();
    // inisialisasi variabel
    int n, angka, rightPart;
    string perintah;
    cin >> n;           // input testcase
    // perulangan pengecekan
    for (int i=0; i<n; i++) {
        cin>>perintah;                  // input perintah
        if(perintah == "insert") {      // jika perintah "insert" maka GASS
            cin>>angka;                 // input angka
            set.insert(angka);
        } else if(perintah == "print" && !set.isEmpty()) {         // jika perintah "print" dan tidak kosong , GASS
            leftPart = set.kolomKiri();             // cek kolom debelah kiri  
            rightPart = set.kolomKanan();           // cek kolom sebelah kanan
            set.jumlah();
            for(int j=leftPart; j>=1; j--) {        // print terbalik
                cout<<neg[j]<<" ";
            }
            for(int k=0; k<=rightPart; k++) {         // print biasa
                cout<<pos[k]<<" ";
            }
            cout<<"\n";
        }
    }
 
    
    return 0;
}