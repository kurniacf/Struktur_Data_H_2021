// BISMILLAH ISOK
// Program jenga menggunakan stack
// Referensi : Internet, Github Strukdat, Youtube

#include <iostream>
#include <stdlib.h>
using namespace std;

// Membuat node -> Fungsi Node 
struct NodeStack {
    int data;
    NodeStack *next;
};

// Struktur dari fungsi STACK (Template Github Stack)
struct Stack {
    NodeStack *_top;
    unsigned _size;
    // init 
    void init() {
        _size = 0;
        _top = NULL;
    }
    // Fungsi untuk pengecekan apakah kosong atau tidak
    bool isEmpty() {
        return (_top == NULL);
    }
    // Fungsi untuk memasukkan nilai ke dalam stack
    void push(int value) {
        NodeStack *newNode = (NodeStack*) malloc(sizeof(NodeStack));
        if (newNode) {
            _size++;
            newNode->data = value;
            if (isEmpty()) {
                newNode->next = NULL;
            } else {
                newNode->next = _top;
            }
            _top = newNode;
        }
    }
    // Fungsi untuk mengambil nilai dari stack
    void pop() {
        if (!isEmpty()) {
            NodeStack *temp = _top;
            _top = _top->next;
            free(temp);
            _size--;
        }
    }
    // Fungsi untuk menunjuk elemen dengan pointer paling atas
    int top() {
        if (!isEmpty()) {
            return _top->data;
        }
        exit(-1);
    }
};

// FUNGSI UTAMA
int main() {
    Stack myStack;      // inisialisasi untuk stack original
    // PENTING!! Jangan lupa di-init
    myStack.init();     
    Stack tmp;          // inisialisasi untuk stack penampung & reverse 
    tmp.init();
    
    // Inisialisasi
    int n;              // inisialisasi testcase
    int input_lenght;   // inisialisasi panjang bilangan
    int number;         // inisialisasi number masing masing
    int top;            // inisialisasi top 
    int i, j;
    cin>>n;             // input testcase
    // Perulangan untuk input data (Proses perhitungan)
    for (i=0; i<n; i++) {
        cin>>input_lenght;          // input panjang bilangan
        // perulangan untuk input bilangan masing"
        for(j=0; j<input_lenght; j++) {
            cin>>number;
            // Masukkan ke fungsi
            if (myStack.isEmpty()) {    
                myStack.push(number);       // Push masukkan ke stack (node pertama)
            } else {
                while(!myStack.isEmpty()) {     // Terus berjalan jika stack tidak kosong
                    top = myStack.top();        //  menampung nilai paling atas
                    if(number>top) {            // Jika number > top maka --> (3) 2 5 ... maka 3 & 2 dihapus
                        myStack.pop();          
                    } else {
                        break;                  // berhenti
                    }   
                }
                myStack.push(number);           // Masukkan ke stack 
            }
        }
        while(!myStack.isEmpty()) {
            tmp.push(myStack.top());        // masukkan nilai yang sesuai ke dalam tmp sementara
            myStack.pop();                  // hapus nilai myStack
        }   
        cout<<"Susunan blok yang disusun Nadut dan Cayo adalah : ";
        while(!tmp.isEmpty()) {         // tidak kosong maka GASS
            cout<<tmp.top()<<" ";       // cetak nilai tmp 
            tmp.pop();                  // hapus nilai tmp
        }
        cout<<"\n";
    }
    cin.get();
    return 0;
}