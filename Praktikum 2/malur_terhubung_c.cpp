// BISMILLAH ISOK
// Program BST penjumlahan sub-tree yang menghubungkan bilangan L dan R (jika ketemu maka node parent dan childnya dijumlahkan)
// Referensi : Internet, Github Strukdat, Youtube
// menggabungkan BST dan single list
#include <iostream>
#include <stdlib.h>
using namespace std;
//inisialisasi
int sem;
// Struct Single List (GITHUB)
typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;
typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;
// init
void slist_init(SinglyList *list) {
    list->_head = NULL;
    list->_size = 0;
}
// cek apakah kosong atau tidak
bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}
// input dari belakang
void slist_pushBack(SinglyList *list, int value) {
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;
        if (slist_isEmpty(list)) {
            list->_head = newNode;
        } else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}
// mengambil nilai dari depan
void slist_popFront(SinglyList *list) {
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}
// menghapus nilai
void slist_remove(SinglyList *list, int value){
    if (!slist_isEmpty(list)) {
        SListNode *temp, *prev;
        temp = list->_head;
        if (temp->data == value) {
            slist_popFront(list);
            return;
        }
        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            return;
        }
        prev->next = temp->next;
        free(temp);
        list->_size--;
    }
}
// menjadikan head
int slist_front(SinglyList *list) {
    if (!slist_isEmpty(list)) {
        return list->_head->data;
    }
    return 0;
}

// Struct BST (Template GITHUB)
// inisialisasi
typedef struct bstnode_t {
    int key;
    int temp;
    struct bstnode_t \
        *left, *right;
} BSTNode;
typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;
// membuat node baru
BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// memasukkan nilai ke node
BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL)
        return __bst__createNode(value);
    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);

    return root;
}
// mencari nilai 
BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key){
            root = root->left; 
        } else if (value > root->key) {
            root = root->right;
        } else{
            return root;
        }
    }
    return root;
}
BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL) {
        currNode = currNode->left;
    }
    return currNode;
}
// remove atau hapus tree
BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;
    if (value > root->key)
        root->right = __bst__remove(root->right, value);
    else if (value < root->key)
        root->left = __bst__remove(root->left, value);
    else {
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        } else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }
        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}
// fungsi mengurutkan nilai secara urut dari kecil ke besar 1, 2, 3, 4, ...
void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        cout<<root->key;
        __bst__inorder(root->right);
    }
}
// urutkan dari belakang {child ke parentnode}
void __bst__postorder(BSTNode *root, SinglyList *list) {        // menggunakan single list sebagai perhitungan
    if (root) {
        __bst__postorder(root->left, list);
        __bst__postorder(root->right, list);
        slist_pushBack(list, root->key);        // penghitungan diarahkan ke list, dimasukkan ke list
    }
}
// urutkan dari depan
void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}
// init
void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}
// cek apakah kosong
bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}
// untuk mencari nilai
bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL){
        return false;
    }
    if (temp->key == value){
        return true;
    } else {
        return false;
    }
}
// untuk memasukkan nilai
void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}
// untuk menghapus nilai
void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}
// untuk menentukan letak penghitungan
BSTNode* hitung(BSTNode *root, int l, int r) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key > l && root->key > r) {
        return hitung(root->left, l, r);              // jika a dan b lebih kecil dari root, maka terletak di kiri
    }
    if (root->key < l && root->key < r) {
        return hitung(root->right, l, r);             // jika a dan b lebih besar dari root, maka terletak di kanan
    }
    return root;
}
// untuk menghitung jumlah keseluruhan
void totalJumlah(BST *bst, int l, int r, SinglyList *list) {
    sem = 0;
    BSTNode *hasil = bst->_root;                // diarahkan ke root
    bst->_root = hitung(bst->_root, l, r);      // masuk untuk mencari lokasi dari l dan r
    __bst__postorder(bst->_root, list);         // diurutkan dan hasil pengurutan dimasukkan ke Singlelist
    while (!slist_isEmpty(list)) {              // selama list tidak kosong maka
        sem = sem + slist_front(list);          // nilai pertama diambil dan dijumlah --> 0+1=1    1 +3 =4, dst
        slist_popFront(list);                   // setelah itu dihapus   1 X,  3 X, dst
    }
    bst->_root = hasil;     
}
// Fungsi Utama
int main() {
    //inisialisasi struct
    BST set;
    bst_init(&set);
    SinglyList myList;
    slist_init(&myList);
    // inisialisasi variabel
    int n;          // var testcase
    int q;          // var kemungkinan
    int angka;      
    int l, r;       // titik l dan titik r
    cin>>n>>q;
    // perulangan input angka
    for(int i=0; i<n; i++) {
        cin>>angka;
        bst_insert(&set, angka);
    }
    // perulangan penghitungan
    for(int i=0; i<q; i++){
        cin>>l>>r;
        if(bst_find(&set, l) && bst_find(&set, r)) {
            totalJumlah(&set, l, r, &myList);
            cout<<sem<<endl;                        // cetak nilai penjumlahan
        } else {
            cout<<"-1"<<endl;
        }
    }
    return 0;
}


