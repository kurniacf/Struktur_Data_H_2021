// BISMILLAH ISOK
// Program memindahkan roti menggunakan stack
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

int main() {
    // inisialisasi untuk stack 
    Stack ray;
    ray.init();
    Stack kak;
    kak.init();
    Stack tmp;
    tmp.init();
    // PENTING!! Jangan lupa di-init
    // inisialisasi variabel
    int n, t, move, bread, roti_ray = 0, roti_kak = 0, i, j, k, l;                 
    cin>>n;                      // input n sebagai banyak roti
    // Direverse stacknya           --> 5 4 3 2 1 menjadi 1 2 3 4 5
    for(i=1; i<=n; i++){
        tmp.push(i);
    }
    for(i=1; i<=n; i++){
        ray.push(tmp.top());
        tmp.pop();
    }
    // input perpindahan
    cin>>t; 
    for(i=0; i<t; i++) {
        cin>>move;              // input gerakan ibu memindahkan roti
        if(move==1) {           // jika 1 dari ray ke kakak
            cin>>bread;         // input roti yang mau dipindahkan
            for(j=0; j<bread; j++) {
                if(!ray.isEmpty()) {        //jika tidak kosong maka top di push lalu stack sebelumnya dihapus
                    kak.push(ray.top());    // 1 2 3 4 5 --> 2 3 4 5 
                    ray.pop();
                }
            }
        } else if(move==2) {            // Jika 2 maka dari kakak ke ray
            cin>>bread;                 // input roti yang mau dipindahkan
            for(j=0; j<bread; j++) {
                if(!kak.isEmpty()) {        //jika tidak kosong maka top di push lalu stack sebelumnya dihapus
                    ray.push(kak.top());    // 3 4 5 --> 5 
                    kak.pop();
                }
            }
        } else {                        // Jika input selain 1 dan 2 maka cetak tumpukan salah
            cout<<"TumpukAnnya saLah! :("<< endl;
            return 0;
        }
    }
    // untuk mengecek roti masing-masing
    roti_ray = ray._size;
    roti_kak = kak._size;
    if (n==0) {                  // jika tidak dapat roti maka ray sangat marah
        cout<<"Ray SangaT MaraH!"<< endl;
    } else if (roti_ray < roti_kak) {          // roti ray lebih sedkit
        for (k=0; k<roti_kak; k++) {
            if(!ray.isEmpty()) {            // jika si roti ray tidak kosong maka cetak
                cout<<ray.top()<<" ";
            } else if(k==roti_ray) {
                cout<<"-"<<" ";             // jika si roti ray lebih sedikit maka cetak, dan tambahkan spasi karena ray di sebelah kiri
            } else {
                cout<<" ";                  // jika tidak maka cetak spasi kosong 
            }
            cout<<kak.top()<<endl;        // cetak nilai teratas dari kak
            kak.pop();                     // nilai roti dihapus
            ray.pop();
        }
    } else if (roti_ray > roti_kak) {  // ray lebih banyak dari kakak
        // perulangan mengecek tumpukan ray lebih banyak
        for (k=0; k<roti_ray; k++) {
            cout<<ray.top()<<" ";   // mengambil nilai teratas 
            if(!kak.isEmpty()) {    // jika si roti kakak tidak kosong maka cetak
                cout<<kak.top();
            } else if(k==roti_kak) {   // jika tumpukan ray lebih banyak  
                cout<<":(";
            }
            printf("\n");
            kak.pop();          // nilai roti dihapus
            ray.pop();
        }
    } else {
        for(l=0; l<roti_kak; l++) {
            cout<<ray.top()<<" "<<kak.top()<<endl;  // jika tidak maka print seperti biasa
            kak.pop();          // nilai roti dihapus
            ray.pop();
        }
    }
    cin.get();
    return 0;
}