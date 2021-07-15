// Bismillah Isok
// Perbaikan Praktikum I -> Cari Tanah
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
using namespace std;

int lahan[1001][1001];
// inisialisasi nodeStack
struct StackNode {
    int data;
    StackNode *next;
};
// inisialisasi struct stack
struct Stack {
    StackNode *_top;
    unsigned _size;
    // init stack
    void init() {
        _size = 0;
        _top = nullptr;
    }
    // fungsi cek apakah kosong??
    bool isEmpty() {
        return (_top == nullptr);
    }
    // fungsi push 
    void push(int value) {
        StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
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
    // fungsi ambil nilai 
    void pop() {
        if (!isEmpty()) {
            StackNode *temp = _top;
            _top = _top->next;
            free(temp);
            _size--;
        }
    }
    // fungsi cek node paling atas
    int top() {
        if (!isEmpty()){
            return _top->data;
        }
        exit(-1);
    }
};
// fungsi mencari area maksimal
int maxArea(int area[], int n) {
    // inisialisasi
    Stack s;
    s.init();
    int maximalArea = 0, tmp, topArea, cek = 0;
    while(cek < n) {
        if (s.isEmpty() || area[s.top()] <= area[cek]) {        // jika stack kosong atau nilai paling tinggi lebih kecil dari area
            s.push(cek++);      // push nilai ke stack
        } else {
            tmp = s.top();  // masukkan nilai top
            s.pop();        // ambil nilai
            // if (s.isEmpty()){
            //     topArea = area[tmp]*cek;            // jika stack kosong, area menjadi topArea
            // } else {
            //     topArea = area[tmp]*cek-s.top()-1;  // jika tidak, area dikali cek dikurangi dengan node teratas
            // }
            topArea = area[tmp] * (s.isEmpty() ? cek : cek - s.top() - 1);
            if (maximalArea < topArea)
                maximalArea = topArea;      // masukkan nilai paling tinggi ke maksimal area
        }
    }
    while(s.isEmpty() == false) {
        tmp = s.top();      // masukkan nilai top
        s.pop();            // ambil nilai
        // if (s.isEmpty()){
        //     topArea = area[tmp]*cek;            // jika stack kosong, area menjadi topArea
        // } else {
        //     topArea = area[tmp]*cek-s.top()-1;  // jika tidak, area dikali cek dikurangi dengan node teratas
        // }
        topArea = area[tmp] * (s.isEmpty() ? cek : cek - s.top() - 1);
        if (maximalArea < topArea)
            maximalArea = topArea;      // masukkan nilai paling tinggi ke maksimal area
    }
    return maximalArea;
}
// fungsi konversi nilai menjadi map area
void konversi(int a , int b){
    for(int i=1; i<a; i++){
        for(int j=0; j<b; j++){ 
            if(lahan[i][j]){            // selama ada baris dan isi
                lahan[i][j] += lahan[i-1][j];       // pertambahan map sistem matrix
            }
        }
    }
}
// fungsi utama
int main(){
    int n, reqLahan, hasil, tmp;     // testcase && batas min lahan
    int a,b;                    // baris && isi
    string area;            // area map

    cin>>n>>reqLahan;           // input tc && lahan minimal
    for(int i=0; i<n; i++){
        cin>>a>>b;              // input baris && isi 
        for(int j=0; j<a; j++){
            cin>>area;               // input isi dalam lahan (1 & 0)
            for(int k=0; k<b; k++) {
                lahan[j][k] = area[k] - 48;     // char ascii 0 == 48, example: 0 - '0' = 0(null) || 1 - '0' = 1
                if(lahan[j][k] == 0){           // jika bernilai null maka area ditandai 1
                    lahan[j][k] = 1;
                } else {
                    lahan[j][k] = 0;            // jika nilai tidak null maka area ditandai 0
                }
            }
        }

        konversi(a, b);     // masukkan ke fungsi konversi
        hasil = 0;

        for(int j=0; j<a; j++){
            tmp = maxArea(lahan[j], b);  // hitung max tiap area
            hasil = max(hasil, tmp);       // cari nilai max 
        }
        // pengecekan kondisi
        if(hasil >= reqLahan) {      
            cout<<"IYA"<<endl;          // print hasil
        } else{
            cout<<"TIDAK"<<endl;
        }
    }
}