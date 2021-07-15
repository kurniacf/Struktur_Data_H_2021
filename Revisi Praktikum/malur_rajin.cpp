// Bismillah Isok
// Perbaikan Prektikum I -> Malur Rajin
// Kurnia Cahya Febryanto - 5025201073
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

// inisialisasi stack
struct StackNode {
    int data;
    char kata[16];          // batas adalah 'a' - 'z' (char 15)
    StackNode *next;
};

struct Stack {
    StackNode *_top;
    unsigned _size;
    // fungsi init
    void init() {
        _size = 0;
        _top = NULL;
    }
    // fungsi cek apakah kosong
    bool isEmpty() {
        return (_top == NULL);
    }
    // fungsi push masukkan nilai
    void push(int value, char alfa[16]){
        StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));;
        if (newNode) {
            _size++;
            newNode->data = value;
            strcpy(newNode->kata, alfa);
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
            StackNode *temp = _top;
            _top = _top->next;
            free(temp);
            _size--;
        }
    }
    // fungsi cek nilai paling atas
    int top() {
        if (!isEmpty())
            return _top->data;
        exit(-1);
    }
};
// fungsi utama
int main() {
    // inisialisasi 
    Stack myStack;
    // PENTING!! Jangan lupa di-init
    myStack.init();
    int n, soal, current, tmp, hasil;   // inisialisasi variabel
    string matkul;
    cin>>n;                                 // input testcase

    for(int i=0; i<n; i++) {
        cin>>soal;
        if(soal == -1){                     // jika soal -1 maka stop dan kerjakan
            hasil = 0;
            current = 0;
            StackNode *cek = myStack._top, *ans;    // inisialisasi stack
            tmp = cek->data;                        // data dimasukkan ke tmp 
            matkul = cek->kata;
            while(cek != NULL){
                if(cek->data < tmp){                // jika data lebih kecil 
                    ans = cek;                      // sebagai pengecekan hasil akhir
                    hasil = current;                // masukkan nilai curr
                    matkul = cek->kata;             // pengecekan kata matkul
                    tmp = cek->data;                // data sementara dimasukkan ke tmp
                }
                cek = cek->next;                    // pindah node selanjutnya
                current++;                          // nilai curr bertambah
            }
            if(ans == myStack._top){
                myStack.pop();                      // ambil nilai
            } else{
                for(int i = 0; i <= hasil; i++){
                    myStack.pop();                  // ambil nilai sesuai hasil perhitungan
                }
            }
            cout<<hasil<<" "<<matkul<<endl;         // print hasil & matkul
        } else{
            char matkul1[16];
            cin>>matkul1;
            if(soal != 0){
                myStack.push(soal, matkul1);         // push soal dan nilai matkul ke stack
            }
        }
    }
    return 0;
}