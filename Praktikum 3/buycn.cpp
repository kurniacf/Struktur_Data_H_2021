// BISMILLAH ISOK
// Program AVL  sistem penaruhan/penumpukan kaset
// Referensi : Internet, Github Strukdat, Youtube
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <string.h>
#define ll long long
using namespace std;
// struct AVL 
typedef struct AVLNode_t {
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;
typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
}AVL;
// buat node
AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// fungsi cari
AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data){
            root = root->left;
        } else if (value > root->data){
            root = root->right;
        } else{
            return root;
        }
    }
    return root;
}
// cari tinggi level node
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

AVLNode* _leftCaseRotate(AVLNode* node){    // skewed kiri (left-left case)
    return _rightRotate(node);
}
AVLNode* _rightCaseRotate(AVLNode* node){   // skewed kanan (right-right case)
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
int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}
// fungsi input
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    if(node==NULL) {// udah mencapai leaf{
        return _avl_createNode(value);
    } 
    if(value < node->data){
        node->left = _insert_AVL(avl,node->left,value);
    } else if(value > node->data){
        node->right = _insert_AVL(avl,node->right,value);
    }
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 
    int balanceFactor=_getBalanceFactor(node);
    if(balanceFactor > 1 && value < node->left->data) {
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
bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL){
        return false;
    }
    if (temp->data == value){
        return true;
    } else{
        return false;
    }
}
void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}
// fungsi mengurutkan nilai dari yg terkecil ke terbesar (kecil diatas)
void inOrderBalik(AVLNode *root, int value, int *index, int *flag){
    if(root == NULL){   // jika null 
        return;
    }
    if(*flag == 0){         // jika input 0
        return;
    }
    inOrderBalik(root->left, value, index, flag);
    if(root->data == value) {
        *flag=0;
    }
    if(*flag == 1) {
        *index += 1; 
    }
    inOrderBalik(root->right, value, index, flag);
}
// fungsi utama
int main(){
    //init
    AVL avlku;
    avl_init(&avlku);
    // inisialisasi
    int n, angka, index=1, flag=1;
    char perintah[11];
    cin>>n; 
    // perulangan cek
    for(int i=0; i<n; i++){
        cin>>perintah>>angka;
        // pengecekan 
        if((strcmp(perintah, "Taro") == 0) || (strcmp(perintah, "Cari") == 0)){
            if(strcmp(perintah, "Taro") == 0){      // input taro maka GASS
                avl_insert(&avlku, angka);      
            } else {                                // masuk fungsi cari
                if(avl_find(&avlku, angka)){
                    inOrderBalik(avlku._root, angka, &index, &flag);    
                    cout<<"Kasetnya ada di tumpukan ke - "<<index<<endl;
                    index=1;    // dikembalikan lagi seperti awal
                    flag=1;
                } else {
                    cout<<"Kasetnya gak ada!"<<endl;;
                }
            }
        } else {
            cout<<"AKU TUH GATAU HARUS NGAPAIN!"<<endl;     
        }
    }
return 0;
}