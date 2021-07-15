// BISMILLAH ISOK
// Program AVL toko (cari dan menjumlah harga barang)
// Referensi : Internet, Github Strukdat, Youtube
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// struct AVL
typedef struct AVLNode_t {
    int data;
    int id;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;
// inisialisasi
typedef struct AVL_t {
    AVLNode *_root;
}AVL;
// membuat node
AVLNode* _avl_createNode(int value, int index) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->id = index;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// fungsi cari
AVLNode* _search(AVLNode *root, int index) {
    while (root != NULL) {
        if (index < root->id){
            root = root->left;
        } else if (index > root->id){
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
AVLNode* _leftCaseRotate(AVLNode* node){    // skewed kiri (left-left case)
    return _rightRotate(node);
}
AVLNode* _rightCaseRotate(AVLNode* node){    // skewed kanan (right-right case) 
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
    if(node==NULL){
        return 0;
    }
    return _getHeight(node->left)-_getHeight(node->right);
}
// insert nilai
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value, int index) {
    if(node==NULL) {// udah mencapai leaf
        return _avl_createNode(value, index);
    }
    if(index < node->id){
        node->left = _insert_AVL(avl,node->left,value, index);
    } else if(index > node->id){
        node->right = _insert_AVL(avl,node->right,value, index);
    } 
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));
    // inisialisasi
    int balanceFactor=_getBalanceFactor(node);
    if(balanceFactor > 1 && index < node->left->id) {
        return _leftCaseRotate(node);
    }
    if(balanceFactor > 1 && index > node->left->id) {
		return _leftRightCaseRotate(node);
    }
    if(balanceFactor < -1 && index > node->right->id){
        return _rightCaseRotate(node);
    }
    if(balanceFactor < -1 && index < node->right->id){
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
// fungsi hapus
AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL){
        return node;
    } 
    if(value > node->data){
        node->right=_remove_AVL(node->right,value);
    } else if(value < node->data){
        node->left=_remove_AVL(node->left,value);
    } else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) {
                temp=node->right;
            } else if(node->right==NULL) {
                temp=node->left;
            }
            if(temp==NULL){
                temp=node;
                node=NULL;
            } else{
                *node=*temp;
            }
            free(temp);
        } else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }
    }
	if(node==NULL) {
        return node;
    }
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;
    int balanceFactor= _getBalanceFactor(node);
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0){
        return _leftCaseRotate(node);
    }
    if(balanceFactor>1 && _getBalanceFactor(node->left)<0){
        return _leftRightCaseRotate(node);
    }
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0){
        return _rightCaseRotate(node);
    }
    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0){
        return _rightLeftCaseRotate(node);
    }
    return node;
}
// init
void avl_init(AVL *avl) {
    avl->_root = NULL;
}
// cek apakah kosong
bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}
// cek cari
bool avl_find(AVL *avl, int index) {
    AVLNode *temp = _search(avl->_root, index);
    if (temp == NULL){
        return false;
    }   
    if (temp->id == index){
        return true;
    }else{
        return false;
    }
}
// insert
void avl_insert(AVL *avl,int value, int index){
    if(!avl_find(avl,index)){
        avl->_root=_insert_AVL(avl,avl->_root,value,index);
    }

}
// hapus
void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
    }
}

void preorder(AVLNode *root) {
    if (root) {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}
// fungsi mencari harga
int cariHarga(AVL *avl, int index) {
    AVLNode *temp = _search(avl->_root, index);     // cari nilai mulai dari root sampe index
    return temp->data;                              // mengembalikan data
}   
// Fungsi utama
int main(){
    //init
    AVL avlku;
    avl_init(&avlku);
    // inisialisasi variabel
    int n, m, total=0, index;
    int idBarang, hargaBarang, idBarangCari, jumlahBarang;
    // input
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        index=i+1;       // cek urutan menggunakan index
        scanf("%d %d", &idBarang, &hargaBarang);    // input id dan hargabarang
        if(idBarang != index) {                  // jika id tidak sama maka print
            printf("ID harus urut\n");
            return 0;
        } else {            // jika sama masukkan harga dan ID
            avl_insert(&avlku, hargaBarang, idBarang);
        }
    }
    // perulangan transaksi
    for(int i=0; i<m; i++) {
        scanf("%d %d", &jumlahBarang, &idBarangCari);       // input
        if(idBarangCari>n || idBarangCari<0) {      // jika barang tidak sesuai dengan yang diminta maka
            printf("Maaf barang tidak tersedia\n");
        } else {
            int hasil=(cariHarga(&avlku, idBarangCari) * jumlahBarang);     // masuk ke fungsi cari harga
            total = total + hasil;          // nilai total akan bertambah dengan hasil
        }
    }
    printf("%d\n", total);      // print total harga
    return 0;
}
