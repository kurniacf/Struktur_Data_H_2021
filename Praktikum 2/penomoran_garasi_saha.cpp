// BISMILLAH ISOK
// Program BST mencari nilai minimal, maximal, dan nilai tengah min=max
// Referensi : Internet, Github Strukdat, Youtube
#include <iostream>
#include <stdlib.h>
#include <limits>           // library limits / batas
using namespace std;
// inisialisasi variabel general
// 1 ≤ P ≤ 1024
// 1 ≤ i ≤ 100000 
int hasil[100001], totalLevel;
// struct BST (TEMPLATE GITHUB)
struct BSTNode {
    BSTNode *left, *right;
    int key;
    int level;          // inisialisasi level untuk menghitung tingkatan tree
};
struct BST {
    BSTNode *_root;
    unsigned int _size;
    // init
    void init() {
        _root = NULL;
        _size = 0u;
    }
    // megecek nilai kosong
    bool isEmpty() {
        return _root == NULL;
    }
    // fungsi mencari nilai
    bool find(int value) {
        BSTNode *temp = __search(_root, value);     // menggunakan search dari utilty fungsi
        if (!temp) {
            return false;
        }
        if (temp->key == value) {
            return true;
        } else {
            return false;
        }
    }
    // fungsi memasukkan nilai
    int tmp;                    // inisialisasi penampung sementara
    void insert(int value) {
        tmp=0;
        if (!find(value)) {
            _root = __insert(_root, value);
            _size++;
        }
        totalLevel = max(totalLevel, tmp);       // membandingkan nilai max dari totalLevel, dengan tmp masukan
    }
    // remove atau hapus tree
    void remove(int value) {
        if (find(value)) {
            _root = __remove(_root, value);
            _size++;
        }
    }
    // urutkan dari depan
    void traversePreorder() {
        __preorder(_root);
    }
    // urutkan dari belakang
    void traversePostorder() {
        __postorder(_root);
    }
    // fungsi mengurutkan nilai secara urut dari kecil ke besar 1, 2, 3, 4, ...
    void traverseInorder() {
        __inorder(_root);
    }
private:
    // Membuat node baru
    BSTNode* __createNode(int value, int duplicate) {
        BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));  // dasar
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        newNode->level = duplicate;             // level agar dia tau berada di tingkatan berapa
        return newNode;
    }
    // Mencari nilai node
    BSTNode* __search(BSTNode *root, int value) {
        while (root != NULL) {
            if (value < root->key) {
                root = root->left;
            } else if (value > root->key) {
                root = root->right;
            } else {
                return root;
            }
        }
        return root;
    }
    // Memasukkan nilai ke node
    BSTNode* __insert(BSTNode *root, int value) {
        tmp++;              // nilai tampung bertambah selanjutnya
        if (root == NULL){
            return __createNode(value,tmp);
        }
        if (value < root->key) {
            root->left = __insert(root->left, value);
        } else if (value > root->key) {
            root->right = __insert(root->right, value);
        }
        return root;
    }
    BSTNode* __findMinNode(BSTNode *node) {
        BSTNode *currNode = node;
        while (currNode && currNode->left != NULL) {
            currNode = currNode->left;
        }
        return currNode;
    }
    // menghapus node
    BSTNode* __remove(BSTNode *root, int value) {
        if (root == NULL) {
            return NULL;
        }
        if (value > root->key) {
            root->right = __remove(root->right, value);
        } else if (value < root->key) {
            root->left = __remove(root->left, value);
        } else {
            if (root->left == NULL) {
                BSTNode *rightChild = root->right;
                free(root);
                return rightChild;
            } else if (root->right == NULL) {
                BSTNode *leftChild = root->left;
                free(root);
                return leftChild;
            }
            BSTNode *temp = __findMinNode(root->right);
            root->key     = temp->key;
            root->right   = __remove(root->right, temp->key);
        }
        return root;
    }
    // mengurutkan dari kecil ke besar
    void __inorder(BSTNode *root) {             // pola dari bawah -> min max min max dst...
        if (root) {
            if(root->level%2 == totalLevel%2) {     // misal punya tree 3 tingkat, level 3%2 bakal sama dengan tree 3%2
                hasil[root->level]=min(hasil[root->level],root->key);   // sehingga nilai terbawah yaitu min
            } else {    // misal tree 4, curr di level 3 maka berbeda -> 
                hasil[root->level]=max(hasil[root->level],root->key);   // sehingga nilai setelah terbawah adalah max
            }       // diulang terus dgn pola min, max, min, max. hingga root
            __inorder(root->right);
            __inorder(root->left);
        }
    }
    // urutkan dari bawah ke atas (belakang)
    void __postorder(BSTNode *root) {
        if (root) {
            __postorder(root->left);
            __postorder(root->right);
            printf("%d ", root->key);
        }
    }
    // urutkan dari depan sesuai input
    void __preorder(BSTNode *root) {
        if (root) {
            printf("%d ", root->key);
            __preorder(root->left);
            __preorder(root->right);
        }
    }
};

int main(){
    //inisialisasi struct
    BST set;
    set.init(); 
    //inisialisasi variabel
    int n;          // var testcase 
    int angka;   
    // input testcase
    cin>>n;
    // perulangan untuk input angka
    for (int i=0; i<n; i++){
        cin>>angka;             // input angka
        set.insert(angka);      // masukkan ke tree
    }
    // perulangan untuk mengecek nilai max dan min
    for(int j=0; j<=totalLevel; j++) {          // berulang sesuai level
        if(j%2 == totalLevel%2) {               // jika sama maka tingkatan berada di tingkat 2 dari bawah
            hasil[j]=2147483647;                // nilai max
            //hasil[j]=INT_MAX;                 // error -> sudah pasang library limits
        } else {
            hasil[j]=(-2147483647-1);            // nilai min
            //hasil[j]=INT_MIN;
        }
    }
    set.traverseInorder();
    for(int k=totalLevel; k>0; k--) {
        cout<<hasil[k]<<" ";                // print nilai min, max -> karena nilai min max disimpan di hasil
    }
    cout<<endl;
    return 0;
}
// alur kerja
// ada 3 tree -> 
//       5
//      /\
//     4 10
// node 5 -> level=1, artinya memiliki kedalaman tingkatan 1, jadi nilai min/max nya cuma itu
// turun jadi levelnya 2, sehingga 2%2 == tree%2 (hitung nilai min)
// node 4 -> level=2, nilai 4 disimpan di hasil
// node 10-> level=2, nilai 10 dibandingkan dengan 4, karena minimal jadi 4 yg masih disimpan
// print