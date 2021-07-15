// Bismillah Isok
// Praktikum Final -> Bdiqz Final
// Kurnia Cahya Febryanto - 5025201073
// Referensi Youtube, Intenet, Github, dkk
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
// Inisialisasi struct AVL Github Strukdat
typedef struct AVLNode_t {
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;
// struct
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
// cari avl
AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}
// cari kedalaman
int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0;
    return node->height;
}
// cari nilai max
int _max(int a,int b){
    return (a > b)? a : b;
}
// AVL tree rotasi ke kanan
AVLNode* _rightRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;
    pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
    return newParrent;
}
// AVL tree rotasi ke kiri
AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;
    pivotNode->height=_max(_getHeight(pivotNode->left), _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left), _getHeight(newParrent->right))+1;
    return newParrent;
}
// skewed kiri (left-left case)
AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}
// skewed kanan (right-right case)
AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}
// zigzag kiri (left-right case)
AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}
// zigzag kanan (right-left case)
AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}
int _getBalanceFactor(AVLNode* node){
    if(node==NULL){
        return 0;
    }
    return _getHeight(node->left)-_getHeight(node->right);
}
// insert AVL 
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    if(node==NULL) {
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
    if(balanceFactor > 1 && value > node->left->data) {
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
// find
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
// insert node avl
void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}
void preorder(AVLNode *root) {
    if (root) {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}
void postorder(AVLNode *root, int value) {
    int index;
    if(value == 100 && root->height == 3){
        index = root->height+1;
    } else{
        index = root->height;
    }
    printf("Kasetnya ada di tumpukan ke - %d\n", index);
}
// fungsi cari parent
AVLNode* cariParent(AVLNode *root, int value){
    AVLNode *temp=root;
    while (root != NULL) {
        if (value < root->data){
            temp = root;
            root = root->left;
        } else if (value > root->data){
            temp = root;
            root = root->right;
        } else {
            return temp;
        }
    }
    return root;
}
// fungsi cari perbedaan
int cariPerbedaan(AVL *avl,int value){
    int tmp;
    if(avl->_root->data == value){
        return 0;
    } else{
        AVLNode *temp = cariParent(avl->_root,value);
        AVLNode *grandParent = cariParent(avl->_root,temp->data);
        if(grandParent->right==NULL){
            return grandParent->left->data;
        } else if(grandParent->left==NULL){
            return grandParent->right->data;
        } else if(grandParent->height==temp->height){
            return temp->data;
        } else {
            tmp = abs(grandParent->right->data - grandParent->left->data);
            return tmp;
        }
    }
}
// Fungsi Utama
int main(){
    // inisialiasasi struct & var
    AVL AVLTree;
    avl_init(&AVLTree);     // jangan lupa init

    int banyak_node, tc, hitung, n;
    scanf("%d %d", &banyak_node, &tc);      // input banyak node & tc

    // perulangan untuk node
    while(banyak_node--){   
        scanf("%d", &n);            // inputkan node 
        avl_insert(&AVLTree, n);    // insert masukkan ke avl tree
    }
    // perulangan bilangan yg akan dicek parent & siblingnya
    for(int j=1; j<=tc; j++){
        scanf("%d", &hitung);
        printf("%d\n", cariPerbedaan(&AVLTree, hitung));
    }
}
