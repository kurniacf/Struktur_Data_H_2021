// BISMILLAH ISOK
// Program BST jika ketemu ganjil maka bilangan genap sebelumnya dihapus, lalu InOrder
// Referensi : Internet, Github Strukdat, Youtube

#include <iostream>
#include <stdlib.h>
using namespace std;
// Struct BST (Template GITHUB)
struct BSTNode {            // Untuk membuat node BST
    BSTNode *left, *right;
    int key;
};
struct BST {
    BSTNode *_root;
    unsigned int _size;
    // init
    void init() {
        _root = NULL;
        _size = 0u;
    }
    // cek apakah kosng
    bool isEmpty() {
        return _root == NULL;
    }
    // cari bst
    bool find(int value) {
        BSTNode *temp = __search(_root, value);
        if (!temp)
            return false;
        
        if (temp->key == value)
            return true;
        else
            return false;
    }
    // masukkan angka ke tree
    void insert(int value) {
        if (!find(value)) {
            _root = __insert(_root, value);
            _size++;
        }
    }
    // remove atau hapus tree
    void remove(int value) {
        if (find(value)) {
            _root = __remove(_root, value);
            _size++;
        }
    }
    // urutkan urut dari kecil ke besar
    void traverseInorder() {
        __inorder(_root);
    }
    // urutkan dari depan
    void traversePreorder() {
        __preorder(_root);
    }
    // urutkan dari belakang
    void traversePostorder() {
        __postorder(_root);
    }
// Fungsi
private:
    // Utility Function
    BSTNode* __createNode(int value) {
        BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    BSTNode* __search(BSTNode *root, int value) {
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
    BSTNode* __insert(BSTNode *root, int value) {
        if (root == NULL)
            return __createNode(value);
        
        if (value < root->key)
            root->left = __insert(root->left, value);
        else if (value > root->key)
            root->right = __insert(root->right, value);
        return root;
    }
    BSTNode* __findMinNode(BSTNode *node) {
        BSTNode *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;
        
        return currNode;
    }
    BSTNode* __remove(BSTNode *root, int value) {
        if (root == NULL) return NULL;
        if (value > root->key) 
            root->right = __remove(root->right, value);
        else if (value < root->key) 
            root->left = __remove(root->left, value);
        else {
            if (root->left == NULL) {
                BSTNode *rightChild = root->right;
                free(root);
                return rightChild;
            }
            else if (root->right == NULL) {
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
    void __inorder(BSTNode *root) {
        if (root) {
            __inorder(root->left);
            printf("%d ", root->key);
            __inorder(root->right);
        }
    }
    void __postorder(BSTNode *root) {
        if (root) {
            __postorder(root->left);
            __postorder(root->right);
        }
    }
    void __preorder(BSTNode *root) {
        if (root) {
            printf("%d ", root->key);
            __preorder(root->left);
            __preorder(root->right);
        }
    }
};
// Fungsi Utama
int main() {
    BST set;
    set.init();         // inisialisasi
    int n, i, j, batas;              
    cin>>n;         // input tstcase
    int angka[51];      // inisialisasi (batas 0<N<50)
    for(i=0; i<n; i++) {
        batas=i+1;                  // batas penghitungan
        cin>>angka[i];              // input angka
        // syarat pengecekan
        if(angka[i]%2==0) {          // jika ganjil maka hapus ganjil dan genap angka sebelumnya
            set.insert(angka[i]);       // masukkan angka (genap)
        } else {
            for(j=batas-1; j>-1; j--){      // batas diatas -1 keatas atau tidak negatif
                if(angka[j]%2==0){
                    set.remove(angka[j]);   // hapus angka tersebut
                    angka[j]++;             // nilai selanjutnya
                    break;                  // berhenti 		// jika tidak di break maka bilangan parent atau awal tidak terdeteksi
                }
                //set.traverseInorder();
            }
        }
    } 
    
    if (set.isEmpty()){                          // jika kosong cetak "Tree Kosong!"
        cout<<"Tree Kosong!"<<endl;
    }             
    set.traverseInorder();
    return 0;
}
/*
7
4 2 3 8 7 9 11
*/
