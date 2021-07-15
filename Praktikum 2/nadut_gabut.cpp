// BISMILLAH ISOK
// Program BST mengecek penjumlahan dari 3 node yang bersebalahan atau tetangga
// Referensi : Internet, Github Strukdat, Youtube
#include <iostream>
#include <stdlib.h>
using namespace std;
// struct BST (TEMPLATE GITHUB)
bool tmp;         // variabel untuk mengecek
struct BSTNode {
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
   // fungsi penjumlahanNilai untuk menghitung jumlah
   void penjumlahanNilai(int value) {
      penjumlahan(_root, value);
   }
private:
   // Membuat node baru
   BSTNode* __createNode(int value) {
      BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));   // dasar
      newNode->key = value;
      newNode->left = newNode->right = NULL;
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
      if (root == NULL) {
         return __createNode(value);
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
   void __inorder(BSTNode *root) {
      if (root) {
         __inorder(root->left);
         printf("%d ", root->key);
         __inorder(root->right);
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
   // fungsi untuk mengecek nilai dan tetanggaan atau tidak
   bool cekNilai(BSTNode *root, int cek){
      if(root){
         cek=true;
      } else {
         cek=false;
      }
      return cek;
   }
   // fungsi untuk menghitung penjumlahan 
   void penjumlahan(BSTNode *root, int value) {
      if(root) {              // jika ada root
         bool cek=cekNilai(root, value);        // memasukkan cekNilai ke dalam var cek
         if(root->left!=NULL && root->right!=NULL) {                          // jika (kiri-root-kanan) memiliki nilai
            if((root->left->key+root->right->key+root->key)==value) {
               tmp=cek;       // maka tmp bernilai cek(true)
            }
         }
         if(root->left!=NULL && root->left->left!=NULL) {                     // jika (kiri-kiri-kiri)
            if((root->left->key+root->left->left->key+root->key)==value) {
               tmp=cek;
            }
         }
         if(root->right!=NULL && root->right->right!=NULL) {                  // jika (kanan-kanan-kanan)
            if((root->right->key+root->right->right->key+root->key)==value) {
               tmp=cek;
            }
         }
         if(root->right!=NULL && root->right->left!=NULL) {                   // jika (kanan-kanan-kiri)
            if((root->right->key+root->right->left->key+root->key)==value) {
               tmp=cek;
            }
         }
         if(root->left!=NULL && root->left->right!=NULL) {                    // jika (kiri-kiri-kanan)
            if((root->left->key+root->left->right->key+root->key)==value) {
               tmp=cek;
            }
         }
         // if(root->left!=NULL && root->right->right!=NULL) {                    // jika (kiri-kanan-kanan)
         //    if((root->left->key+root->right->right->key+root->key)==value) {
         //       tmp=cek;
         //    }
         // }
         // if(root->right!=NULL && root->left->left!=NULL) {                    // jika (kanan-kanan-kiri)
         //    if((root->right->key+root->left->left->key+root->key)==value) {
         //       tmp=cek;
         //    }
         // }
         penjumlahan(root->left, value); 
         penjumlahan(root->right, value);
      } else {
         return;
      }
   }
};
// Fungsi Utama
int main() {
   //inisialisasi struct
   BST set;
   set.init(); 
   //inisialisasi variabel
   int n;         // var testcase
   int angka; 
   int jumlah;
   // input testcase
   cin>>n;
   // perulangan untuk input angka
   for (int i=0; i<n; i++){
      cin>>angka;                   // input angka
      set.insert(angka);            // masukkan ke tree
   }
   // input jumlah yang diinginkan
   cin>>jumlah;
   // masukkan ke dalam fungsi
   set.penjumlahanNilai(jumlah);
   if(tmp==1) {
      cout<<"Penjumlahan angka di tree yang menghasilkan "<<jumlah<<" ditemukan"<<endl;
   } else {
      cout<<"Tidak ditemukan penjumlahan angka di tree yang menghasilkan "<< jumlah<<endl;
   }
   cin.get();
   return 0;
}
