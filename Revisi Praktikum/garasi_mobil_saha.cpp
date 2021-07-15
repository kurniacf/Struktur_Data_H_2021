// Bismillah Isok
// Perbaikan Prektikum I -> Garasi Mobil Saha
// Kurnia Cahya Febryanto - 5025201073
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Node {
    int in;
    int out;
    Node *next;
};

struct Stack {
    Node *_top;
    unsigned _size;

    Stack() {
        _size = 0;
        _top = NULL;
    }
    // fungsi cek apakah kosong
    bool isEmpty() {
        return (_top == NULL);
    }
    // fungsi push nilai 
    void push(int a, int b) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        if (newNode) {
            _size++;
            newNode->in = a;
            newNode->out = b;

            if (isEmpty()) {
                newNode->next = NULL;
            } else {
                newNode->next = _top;
            }
            _top = newNode;
        }
    }
    // fungsi ambil nilai
    void pop() {
        if (!isEmpty()) {
            Node *temp = _top;
            _top = _top->next;
            free(temp);
            _size--;
        }
    }
    // fungsi masuk ke garasi (stack)
    int in() {
        if (!isEmpty()){
            return _top->in;
        }
        exit(-1);
    }
    // fungsi keluar dari garasi (stack)
    int out() {
        if (!isEmpty()){
            return _top->out;
        }
        exit(-1);
    }
    void printNilai(bool cek){
        if(cek == true) {
            cout<<"Hore gausah renov garasi"<<endl;
        } else {
            cout<<"Hmm harus renovasi garasi nich"<<endl;
        }
    }

};
// Fungsi utama
int main() {
    // inisialiasi variabel
    int n, mobil, kapasitas, masuk, keluar;          
    bool cek;
    cin>>n;         // input testcase

    for(int i=0; i<n; i++) {
        Stack myStack;          // inisialisasi stack
        cek = true;
        cin>>mobil>>kapasitas;  // input mobil  && kapasitas garasi

        for(int j=0; j<mobil; j++) {
            cin>>masuk>>keluar;         // input jam masuk & keluar mobil
            if(myStack.isEmpty()) {             // jika kosong maka push jam masuk keluar mobil
                myStack.push(masuk, keluar);
            } else {
                if(masuk == keluar) {           // jika jam masuk == keluar maka tidak bisa (false)
                    cek = false;
                } else if(masuk>myStack.in() && keluar<myStack.out()) {       // jika jam masuk lebih besar dari masuk sebelumnya
                    if(myStack._size <= kapasitas) {                                // dan keluar lebih kecil dari keluar sebelumnya
                        myStack.push(masuk,keluar);                                 // maka push nilai masuk & keluar yg baru
                    } else {
                        cek = false;
                    }
                } else if (masuk >= myStack.out()) {         // jika nilai jam masuk selanjutnya lebih besar atau sama dengan mobil yg keluar
                    if(myStack._size <= kapasitas) {
                        myStack.pop();                       // maka ambil nilai yang lama
                        myStack.push(masuk,keluar);          // masukkan nilai yang baru
                    } else {
                        cek = false;
                    }
                } else {
                    if(myStack._size<kapasitas) {
                        myStack.push(masuk,keluar);         // masukkan nilai
                    } else {
                        cek = false;
                    }
                }
            }
        }
        myStack.printNilai(cek);        // fungsi print 
    }
    return 0;
}