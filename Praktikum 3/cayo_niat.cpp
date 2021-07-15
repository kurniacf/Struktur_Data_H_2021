// BISMILLAH ISOK
// Program AVL daftar nama sesuai abjad, diubah agar bisa menampung string
// Referensi : Internet, Github Strukdat, Youtube
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
// struct node
typedef struct AVLNode_t{
    int height;
    char key[1001];
    struct AVLNode_t *left, *right;
} AVLNode;
// inisialisasi
typedef struct AVL_t{
    AVLNode *_root;
    unsigned int _size;
} AVL;
// buat node
AVLNode* _avl_createNode(char value[]) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    strcpy(newNode->key, value);
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// fungsi cari
AVLNode* _search(AVLNode *root, char value[]) {
    while (root != NULL) {
        if (strcmp(value, root->key) < 0){
            root = root->left;
        } else if (strcmp(value, root->key) > 0){
            root = root->right;
        } else{
            return root;
        }
    }
    return root;
}
// fungsi cari tinggi level node
int _getHeight(AVLNode* node){
    if(node==NULL){
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
    AVLNode* newParrent     = pivotNode->left;
    pivotNode->left         = newParrent->right;
    newParrent->right       = pivotNode;
    pivotNode->height   = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height  = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;
    return newParrent;
}
// fungsi rotasi kiri
AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent     = pivotNode->right;
    pivotNode->right        = newParrent->left;
    newParrent->left        = pivotNode;
    pivotNode->height   = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height  = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;
    return newParrent;
}
AVLNode* _leftCaseRotate(AVLNode* node){        // skewed kiri (left-left case)
    return _rightRotate(node);
}
AVLNode* _rightCaseRotate(AVLNode* node){       // zigzag kiri (left-right case)
    return _leftRotate(node);
}
AVLNode* _leftRightCaseRotate(AVLNode* node){   // skewed kanan (right-right case)
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}
AVLNode* _rightLeftCaseRotate(AVLNode* node){   // zigzag kanan (right-left case)
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}
int _getBalanceFactor(AVLNode* node){
    if(node==NULL){
        return 0;
    }
    return (_getHeight(node->left) - _getHeight(node->right));
}
// fungsi input nilai
AVLNode* _insert_AVL(AVLNode* node, char value[]) {
    if(node==NULL) {// udah mencapai leaf
        return _avl_createNode(value);
    }
    if(strcmp(value, node->key) < 0){
        node->left  = _insert_AVL(node->left, value);
    } else if(strcmp(value, node->key) > 0){
        node->right = _insert_AVL(node->right, value);
    }
    node->height      = 1 + _max(_getHeight(node->left), _getHeight(node->right));
    int balanceFactor = _getBalanceFactor(node);
    if(balanceFactor > 1 && strcmp(value, node->left->key) < 0){
        return _leftCaseRotate(node);
    }
    if(balanceFactor > 1 && strcmp(value, node->left->key) > 0){
		return _leftRightCaseRotate(node);
    }
    if(balanceFactor < -1 && strcmp(value, node->right->key) > 0){
        return _rightCaseRotate(node);
    }
    if(balanceFactor < -1 && strcmp(value, node->right->key) < 0){
        return _rightLeftCaseRotate(node);
    }
    return node;
}
AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
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
bool avl_find(AVL *avl, char value[]) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL){
        return false;
    }
    if (strcmp(temp->key, value) == 0){
        return true;
    } else{
        return false;
    }
}
// input
void avl_insert(AVL *avl, char value[]){
    if(!avl_find(avl, value)){
        avl->_root=_insert_AVL(avl->_root, value);
        avl->_size++;
    }
}
// fungsi cetak angka berurutan 
void _inorderNum(AVLNode *root, int *angka) {
    if (root) {     //selama ada root
        _inorderNum(root->left, angka); 
        cout<<*angka<<". "<<root->key<<endl;        
        *angka = *angka+1;
        _inorderNum(root->right, angka);
    }
}
void inorderAngka(AVL *avl) {
    int angka = 1;      // dimulai dari satu
    _inorderNum(avl->_root, &angka);
}
// print rantai
void _inorderRantai(AVLNode *root, int *angka) {
    if (root) {
        _inorderRantai(root->left, angka);
        if (*angka == 1){
            cout<<root->key;
        } else{
            cout<<"--<3--"<<root->key;
        }
        *angka = *angka+1;
        _inorderRantai(root->right, angka);
    }
}
void inorderRantai(AVL *avl) {
    int angka = 1;
    _inorderRantai(avl->_root, &angka);
}
// Fungsi Utama
int main(){
    // init
    AVL set;
    avl_init(&set);
    // inisialisasi var
    char nama[1001];
    int cek;
    while(true){            // selama tidak kosong
        cek = scanf("%s", nama);
        if (cek == EOF || cek == -1) {       // jika akhir file maka break
            break;
        }
        avl_insert(&set, nama);     // masukkan nama
    }
    inorderAngka(&set);
    inorderRantai(&set);
    cout<<endl;
    return 0;
}