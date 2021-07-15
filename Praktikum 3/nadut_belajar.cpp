// BISMILLAH ISOK
// Program AVL menghitung bilangan selisih antara parent sebuah node dengan siblingnya.
// Referensi : Internet, Github Strukdat, Youtube
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <math.h>
#define ll long long
using namespace std;
// struct Node
typedef struct AVLNode_t {
    long long int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;
// inisialisasi
typedef struct AVL_t {
    AVLNode *_root;
    unsigned long long int _size;
}AVL;
// fungsi buat Node
AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// fungsi cari
AVLNode* _search(AVLNode *root, long long int value) {
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
// fungsi cari tinggi level node
int _getHeight(AVLNode* node){
    if(node==NULL) {
        return 0; 
    }
    return node->height;
}
// fungsi max
int _max(int a,int b){
    return (a > b)? a : b;
}
// fungsi rotasi kanan
AVLNode* _rightRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;
    pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
    return newParrent;
}
// fungsi rotasi kiri
AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;
    pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
    return newParrent;
}
// pattern
AVLNode* _leftCaseRotate(AVLNode* node){        // skewed kiri (left-left case)
    return _rightRotate(node);
}
 
AVLNode* _rightCaseRotate(AVLNode* node){       // skewed kanan (right-right case)
    return _leftRotate(node);
}
 
AVLNode* _leftRightCaseRotate(AVLNode* node){   // zigzag kiri (left-right case)
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}
 
AVLNode* _rightLeftCaseRotate(AVLNode* node){   // zigzag kanan (right-left case)
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}
// mencari keseimbangan node
int _getBalanceFactor(AVLNode* node){
    if(node==NULL) {
        return 0;
    }
    return _getHeight(node->left)-_getHeight(node->right);
}
// input nilai
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,long long int value) {
    if(node==NULL){ // udah mencapai leaf
        return _avl_createNode(value);
    } 
    if(value < node->data) {
        node->left = _insert_AVL(avl,node->left,value);
    } else if(value > node->data) {
        node->right = _insert_AVL(avl,node->right,value);
    }
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 
    // inisialisasi
    int balanceFactor=_getBalanceFactor(node);
    if(balanceFactor > 1 && value < node->left->data) {
        return _leftCaseRotate(node);
    }
    if(balanceFactor > 1 && value > node->left->data) {
        return _leftRightCaseRotate(node);
    }
    if(balanceFactor < -1 && value > node->right->data) {
        return _rightCaseRotate(node);
    }
    if(balanceFactor < -1 && value < node->right->data){
        return _rightLeftCaseRotate(node);
    }
    return node;
}
// cari
AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL){
        currNode = currNode->left;
    }
    return currNode;
}
// init
void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}
// cek apakah kosong
bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}
// cek nilai
bool avl_find(AVL *avl, long long int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL) {
        return false;
    }
    if (temp->data == value){
        return true;
    } else {
        return false;
    }
}
// insert
void avl_insert(AVL *avl,long long int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
 
}
 
void preorder(AVLNode *root) {
    if (root) {
        preorder(root->left);
        printf("%lld ", root->data);
        preorder(root->right);
    }
}
 
AVLNode*  searchParent(AVLNode* rootParent, long long int value){
    if (rootParent == NULL){            // jika nilai parent NULL maka return null
        return NULL;                
    }  
    else
    {
        if(rootParent->data == value)
        {
            return NULL;
        }
        if(rootParent->left == NULL && rootParent->right == NULL)  // jika nilai parent sebelah kiri dan kanan kosong balikkan NULL, (root only)
            return NULL;
        if(rootParent->left != NULL)
        {
            if(rootParent->left->data == value)
            {
                return rootParent;
            }
        }
        if(rootParent->right != NULL)
        {
            if(rootParent->right->data == value)
            {
                return rootParent;
            }
        }
        if(rootParent->data > value){       // jika nilai rootparent lebih besar maka cari nilai sebelah kiri
            return searchParent(rootParent->left,value);
        }   
        if(rootParent->data < value){      // jika nilai rootparent lebih kecil maka cari nilai sebelah kanan
            return searchParent(rootParent->right,value);
        }
    }    
    return rootParent;
}
 
// Fungsi mencari sibling node (node yg bersebalahan)
AVLNode* nodeSiblings(AVLNode *node, long long int key) {
    if (node == NULL || node->data == key) {    // jika null atau hanya itu sendiri return null
        return NULL;
    }
    if (node->left != NULL && node->left->data == key) {        // jika node kiri tidak null dan memiliki nilai maka kembalikan nilai node kanan
        return node->right;
    }
    if (node->right != NULL && node->right->data == key) {      // jika node kanan tidak null dan memiliki nilai maka kembalikan nilai node kiri
        return node->left;
    }
    // inisialisasi pengecekan
    AVLNode* tmp = nodeSiblings(node->left, key);
    if (tmp != NULL) {
        return tmp;         //jika tidak sama dengan null maka kembalikan nilai
    }
    tmp = nodeSiblings(node->right, key);
    return tmp;
}
// Fungsi Utama
int main(){
    // init
    AVL avlku;
    avl_init(&avlku);
    // inisialisasi variabel
    int n, m, angka;
    ll int currentSiblings, hasil, cekNode;
    cin>>n;         // input jumlah node di AVL
    cin>>m;         // input testcase
    // perulangan input angka
    for(int i=0; i<n; i++){
        cin>>angka;
        avl_insert(&avlku, angka);
    }
    // perulangan penghitungan dan pengecekan
    for(int i=0; i<m; i++){
        cin>>cekNode;           // input node angka yang akan dicek
        AVLNode *tmp=searchParent(avlku._root, cekNode);     // masukkan ke dalam fungsi cari Parent
        if(!tmp)
        {
            printf("0\n");
            continue;
        }
        else
        {
            AVLNode *siblings = nodeSiblings(avlku._root, tmp->data);
            if(siblings!=NULL){
                currentSiblings = siblings->data;
                hasil = abs(currentSiblings-tmp->data);
                printf("%lld\n", hasil);
            }
            else
                printf("%lld\n", tmp->data);
        }
    }
}