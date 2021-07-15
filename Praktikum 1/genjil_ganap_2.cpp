// BISMILLAH ISOK
// Program ganjil genap menggunakan linked list
// Referensi : Internet, Github Strukdat, Youtube

#include <iostream>
#include <stdlib.h>
using namespace std;

// Node Singly List
struct Node {
	int data;
	struct Node *next;
};

// Fungsi Push_Back
void pushBack(Node** _head, int value) {
    // Node *newNode = (Node*) malloc(sizeof(Node)); --> dasar
	Node* newNode = new Node();    // Membuat node baru menggunakan new
    //inisialisasi
	Node *tail = *_head;            // memasukkan alamat ke node tail
	newNode->data = value;          // masukkan nilai ke data newNode
	newNode->next = NULL;           // next newNode dijadikan NULL 
	// Pengecekan
	if (*_head == NULL) {           // Jka kosong maka jadi head
		*_head = newNode;
		return;
	}
	// Perulangan untuk gerak sampai Node terakhir --> NULL
	while (tail->next != NULL) {
		tail = tail->next;
    }
	tail->next = newNode;   // menjadikan newNode sebagai tail
	return;
}
// Fungsi Push_Front
void pushFront(Node** _head, int value) {
    // Node *newNode = (Node*) malloc(sizeof(Node)); --> dasar
    struct Node* newNode = (Node*) malloc(sizeof(struct Node)); // membuat node baru
    // inisialisasi
    newNode->data = value;      // memasukkan value(nilai) ke newNode
    newNode->next = *_head;     
    (*_head) = newNode;         // newNode jadi head
}

// Fungsi print 
void printAll (struct Node *node) {
	while (node!=NULL) {
        cout<<node->data<<" ";
		node = node->next;
	}
}

// Fungsi Cek Ganjil Genap
void ganjilGenap(struct Node **_head) {
    // inisialisasi
    // Odd (ganjil)
	Node *ganjilHead = NULL;        // penanda ganjil urutan awal
	Node *genapHead = NULL;         //       ----            akhir
    // Even (genap)
	Node *ganjilTail = NULL;        // penanda genap urutan awal
	Node *genapTail = NULL;         //       ----           akhir
	
	Node *currentNode = *_head;     // menandakan posisi sekarang -> dimulai dari head
	// Perulangan (pemindahan posisi)
	while(currentNode != NULL) {            // tidak sama NULL maka GASS
		int value = currentNode->data;  
		if (value % 2 == 0) {                // jika genap maka tambahkan 
			if (genapHead == NULL) {         // untuk elemen pertama bilangan genap 
				genapHead = currentNode;
				genapTail = genapHead;
			} else {                        // bilangan genap selanjutnya akan ditambahkan ke node sesudahnya
				genapTail->next = currentNode;
				genapTail = genapTail->next;
			}
		} else{                             // Jika Ganjil maka tambahkan 
			if (ganjilHead == NULL){        // untuk elemen pertama bilangan ganjil
				ganjilHead = currentNode;
				ganjilTail = ganjilHead;
			} else {                        // bilangan genap selanjutnya akan ditambahkan ke node sesudahny
				ganjilTail->next = currentNode;
				ganjilTail = ganjilTail->next;
			}
		}
		currentNode = currentNode->next;	// posisi sekarang terus bergerak jika tidak NULL
	}
    // Syarat jika bilangan semua ganjil atau genap semua, maka tetap
	if(ganjilHead == NULL || genapHead == NULL){
		return;         // maka tidak berubah
	}
    // Untuk mengurutkan genap duluan habis itu ganjil
	genapTail->next = ganjilHead;
	ganjilTail->next = NULL;
	*_head = genapHead;         // head adalah bilangan genap awal
}

// FUNGSI UTAMA
int main() {
    // inisialisasi
	struct Node* myList = NULL;
    int n, number, i;       
    cin>>n;                 // input testcase
	for(i=0; i<n; i++){
        cin>>number;        // input number
        if (number%2==0){
            pushFront(&myList, number);     // input bilangan genap pakai pushFront
        } else {
            pushBack(&myList, number);      // input bilangan ganjil pakai pushBack
        }
    }
	ganjilGenap(&myList);               // masuk ke fungsi ganjilgenap

    cout<<"Urutan Mobil Roy : ";
	printAll(myList);
    cin.get();
	return 0;
}