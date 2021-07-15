// Bismillah Isok
// Perbaikan Praktikum IV -> puzzle mud mud
// Kurnia Cahya Febryanto - 5025201073
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <cstring>
using namespace std;
int angka[9] = {1,2,3,4,5,6,7,8,0};
// inisialisasi struct
struct Node {
    Node* parent;
    int arr[3*3], posisi, langkah, jejak;
};
// fungsi buat node
Node* newNode(Node* parent, int arr[], int posisi, int newPosisi, int jejak) {
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->arr, arr, sizeof node->arr);       // menyalin n byte dari area memori src ke tujuan area memori
    swap(node->arr[posisi],node->arr[newPosisi]);   // menukarkan dua buah nilai
    node->posisi=newPosisi;         // sebagai penghitungan index pada node
    node->langkah = INT_MAX;           // penghitungan ongkos langkah pergerakan
    node->jejak = jejak;            // jejak untuk menghitung kedalaman (history) node
    return node;
}
// fungsi pengecekan untuk penyelesaian puzzle apakah bisa diselasaikan atau tidak
bool cekPuzzle(int arr[]) {
    int tmp = 0;
    for(int i=0; i<3*3-1; i++) {            // batas mengikuti baris
        for(int j=i+1; j<3*3; j++) {        // batas mengikuti kolom
            if(arr[j] && arr[i] &&  arr[i] > arr[j]) {
                tmp++;
            }
        }
    }
    return (tmp%2 == 0);
}
// fungsi pengecekan angka
bool cekAngka(int arr[]) {
    bool cek = true;
    for(int i=0; i<3*3; i++) {
        if(arr[i]!=angka[i]) {      // jika tidak sesuai maka false
            cek=false;
            break;
        }
    }
    return cek;
}
// fungsi manhattanDistance untuk mencari jarak dengan menjumlahkan semua selisih dari jarak 
int manhattanDistance(int a, int b) {
    int hitung;
    hitung = abs((a%3)-(b%3)) + abs((floor(a/3))-(floor(b/3))); // rumus
    return hitung;
}
// fungsi untuk menghitung jarak langkah minimum 
int minimumLangkah(int arr[]) {
    int langkah = 0;
    for(int i=0; i<9; i++) {      // batas sesuai kotak
        if(arr[i] != angka[i]) {
            int asal = i, tujuan;       // asal angka sebelum dipindah
            if(arr[i]!=0) {
                tujuan = angka[arr[i]-1]-1;     // perpindahan asal angka dengan tujuan angka
            } else {
                tujuan = 8;
            }
            langkah += manhattanDistance(asal, tujuan);     // masukkan untuk menghitung jarak
        }
    }
    return langkah;
}
// fungsi print kotak puzzle penyelesaian
void printPuzzle(int arr[]) {   
    printf("\n");
    for(int i=0; i<3; i++) {
        int checker=3*i;
        for(int j=checker; j<checker+3; j++) {
            cout<<arr[j];       // print puzzle 3 kotak (1 baris) 
        }
        printf("\n");
    }
}
// fungsi print hasil langkah minimum 
void printHasil(Node* root, int count) {
    if(root->parent == NULL) {
        cout<<"Langkah minimum = "<<count;
        return;
    }
    printHasil(root->parent, count+1);
    printPuzzle(root->arr);
}
// fungsi step ubah puzzle hingga sesuai
void ubahPuzzle(Node* parent, int arr[]) {
    queue<Node*> listQue;
    listQue.push(parent);
    parent->langkah = minimumLangkah(arr);      // masukkan ke queue
    bool cek = true;
    while(!listQue.empty()) {
        Node* currNode = listQue.front();        // hitung dimulai dari paling depan
        listQue.pop();                      // ambil nilai
        if (cekAngka(currNode->arr)) {           // jika true maka
            printHasil(currNode, 0);
            return;
        }
        int x = (currNode->posisi) % 3;
        int y = floor((currNode->posisi) / 3);
        if(y>0 && y<=2) {                   // dihitung dari atas 
            Node* child = newNode(          // penukaran posisi dari atas dan input ke node
                currNode,
                currNode->arr,
                currNode->posisi,
                (currNode->posisi)-3,
                (currNode->jejak)+1
            );
            child->langkah=minimumLangkah(child->arr);      // masukkan untuk menghitung langkah jarak minimum (langkah minimum)
            if(cek) {
                listQue.push(child);             // push
            } else if(child->parent->parent->posisi != child->posisi)  {
                listQue.push(child);
            }
        }   
        if(y>=0 && y<2) {           // dihitung dari bawah
            Node* child = newNode(          // penukaran posisi dari bawah dan input ke node
                currNode,           // parent
                currNode->arr,
                currNode->posisi,
                (currNode->posisi)+3,
                (currNode->jejak)+1
            );
            child->langkah=minimumLangkah(child->arr);      // masukkan untuk menghitung langkah jarak minimum (langkah minimum)
            if(cek) {
                listQue.push(child);
            } else if(child->parent->parent->posisi != child->posisi) {
                listQue.push(child);
            }
        }
        if(x>=0 && x<2) {           // dihitung dari sisi kanan
            Node* child = newNode(      // penukaran posisi dari sisi kanan dan input ke node
                currNode,
                currNode->arr,
                currNode->posisi,
                (currNode->posisi)+1,
                (currNode->jejak)+1
            );
            child->langkah=minimumLangkah(child->arr);
            if(cek) {
                listQue.push(child);
            } else if(child->parent->parent->posisi != child->posisi) {
                listQue.push(child);
            }
        }
        if(x>0 && x<=2) {           // dihitung dari sisi kiri
            Node* child = newNode(  // penukaran posisi dari sisi kiri dan input ke node
                currNode,
                currNode->arr,
                currNode->posisi,
                (currNode->posisi)-1,
                (currNode->jejak)+1
            );
            child->langkah=minimumLangkah(child->arr);      // masukkan untuk menghitung langkah jarak minimum (langkah minimum)
            if(cek) {
                listQue.push(child);
            } else if(child->parent->parent->posisi != child->posisi) {
                listQue.push(child);
            }
        }
        cek = false;
    }
}

void penyelesaianPuzzle(int arr[]) {
    int posisi = 0;
    for(int i=0; i<9; i++) {         // pemetaan posisi
        if(arr[i]==0) {
            posisi=i;
            break;
        }
    }
    Node* root = newNode(NULL,arr,posisi,posisi,0);     // untuk membuat node baru
    ubahPuzzle(root, arr);
}
// FUngsi utama
int main() {
    // inisialisasi variabel
    string a,b,c;
    bool cek = true;
    while(cin>>a){
        cin>>b>>c;
        int puzzle[3*3], tmp = 0;        // ukuran 3*3 karena isinya 9 kotak
        for(int i=0; i<3; i++) {            // batas 3 karena ukuran kotak adalah 3*3
            for(int j=0; j<3; j++) {
                if(i==0){ 
                    puzzle[tmp]=a[j]-48;        // pengecekan melalui ascii bilangan
                } else if(i==1) { 
                    puzzle[tmp]=b[j]-48;
                } else {
                    puzzle[tmp]=c[j]-48;
                }
                tmp++;
            }
        }
        if(cekPuzzle(puzzle)) {                 // masukkan ke fungsi cekPuzzle untuk dicek
            penyelesaianPuzzle(puzzle);         // masukkan ke fungsi penyelaian untuk menyelesaikan puzzle
        } else {
            cek = false;
            cout<<"Problem tidak dapat diselesaikan"<<endl;
        }
    }
    return 0;
}