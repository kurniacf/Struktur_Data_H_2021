// Bismillah Isok
// Program CRUD data Pegawai dengan sort
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

typedef struct Pegawai{
    string nama;
    string nip;
}dp;

dp pegawai [1001];
int tanda=0, opsi;

bool tukarMinNip(dp a, dp b);
bool tukarMaxNip(dp a, dp b);
void simpanData ();
void tambahPegawai ();
void lihatPegawai ();
void bacaData();
void deletePegawai();
void updatePegawai();
void sortPegawai();
void head();
void exit();

// fungsi tukar compare -> sort(a, a+i, compare)
bool tukarMinNip(dp a, dp b){
    return (a.nip < b.nip);
}
bool tukarMaxNip(dp a, dp b){
    return (a.nip > b.nip);
}
bool tukarMinNama(dp a, dp b){
    return (a.nama < b.nama);
}
bool tukarMaxNama(dp a, dp b){
    return (a.nama > b.nama);
}


// fungsi menyimpan data ke file
void simpanData (){
    ofstream filePegawai;
    filePegawai.open("nip.txt");
    for(int i=0; i<tanda; i++){
        filePegawai<<pegawai[i].nama<<endl;
        filePegawai<<pegawai[i].nip;
        if(i<tanda-1){
            filePegawai<<endl;
        }
    }
    filePegawai.close();
}


// fungsi menambah data 
void tambahPegawai (){
    ofstream filePegawai("nip.txt", ios::app);
    if (filePegawai.is_open()) {
        if(!filePegawai){
            cout<<"File Error!!";
        }
        cout<<"Masukkan Nama: ";
        getline(cin, pegawai[tanda].nama);
        //cin>>pegawai[tanda].nama;
        cout<<"Masukkan NIP: ";
        getline(cin, pegawai[tanda].nip);
        //cin>>pegawai[tanda].nip;
        filePegawai<<pegawai[tanda].nama<<endl;
        filePegawai<<pegawai[tanda].nip<<endl;
        cout<<endl;

        tanda++;
        simpanData();
        filePegawai.close();
        cout<<"Data Pegawai Sukses Ditambahkan!!"<<endl;
    } else{
        cout<<"Tidak Bisa Ditambahkan!"<<endl;
    }
    system("Pause");
    system("CLS");
}

// fungsi lihat pegawai
void lihatPegawai (){
    system("CLS");
    cout<<"---------DATA PEGAWAI---------"<<endl;
    for(int i=0; i < tanda; i++){
        cout<<pegawai[i].nama<<endl;
        cout<<pegawai[i].nip<<endl;
    }
}

// fungsi baca keseluruhan data
void bacaData(){
    ifstream filePegawai;
    filePegawai.open("nip.txt", fstream::in);
    if(filePegawai){
        while(!filePegawai.eof()){
            getline(filePegawai, pegawai[tanda].nama);
            getline(filePegawai, pegawai[tanda].nip);
            tanda++;
        }
    }
    lihatPegawai();
    filePegawai.close();
    simpanData();
}

// fungsi cari pegawai
void cariPegawai(){
    fstream filePegawai;
    filePegawai.open("nip.txt");
    string nama, nip, cek;
    Pegawai cariData;
    int tmp;

    cout<<"---Opsi Cari---"<<endl;
    cout<<"1. Berdasarkan NIP"<<endl;
    cout<<"2. Berdasarkan Nama"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>tmp;

    if(tmp==1){
        cout<<"Masukkan NIP Yang Dicari: ";
        cin>>nip;
        bool temp = false;
        for(int i=0; i<tanda; i++){
            getline(filePegawai,cariData.nama);
            getline(filePegawai,cariData.nip);
            if(cariData.nip == nip){
                cout<<"Nama : "<<cariData.nama<<endl;
                cout<<"NIP  : "<<cariData.nip<<endl<<endl;
                temp=true;
                break;
            }
        }
        if (!temp){
            cout<<"Data Pegawai Tidak Ada!!!" << endl;
        }
    } else if(tmp==2){
        cout<<"Masukkan Nama Yang Dicari: ";
        //cin>>nama;
        getline(cin>>ws, nama);
        bool temp = false;
        for(int i=0; i<tanda; i++){
            getline(filePegawai,cariData.nama);
            getline(filePegawai,cariData.nip);
            if(cariData.nama == nama){
                cout<<"Nama : "<< cariData.nama<<endl;
                cout<<"NIP  : "<< cariData.nip<<endl<<endl;
                temp=true;
                break;
            }
        }
        if (!temp){
            cout<<"Data Pegawai Tidak Ada!!!" << endl;
        }
    } else{
        cout<<"Opsi Salah!"<<endl;
    }
    filePegawai.close();
    simpanData();
    system("Pause");
    system("CLS");
}

// fungsi hapus data pegawai
void deletePegawai() {
    fstream filePegawai;
    //Pegawai temp[tanda];
    string nama, nip;
    int tmp;

    cout<<"---Opsi Delete---"<<endl;
    cout<<"1. Berdasarkan NIP"<<endl;
    cout<<"2. Berdasarkan Nama"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>tmp;

    if(tmp==1){
        cout<<"Masukkan NIP: ";
        cin>>nip;
        bool cek=false;
        for(int i=0; i<tanda; i++){
            if(pegawai[i].nip==nip){
                for(int j=i; j<tanda-1; j++){
                pegawai[j]=pegawai[j+1];
                }
                cout<<"Delete Data Pegawai Sukses!" << endl;
                tanda--;
                cek=true;
                break;
            }
        }
        if(!cek){
            cout << "Data yang dihapus tidak ada!" << endl;
        }
        
    } else if(tmp==2) {
        cout<<"Masukkan Nama: ";
        getline(cin>>ws, nama);
        bool cek=false;
        for(int i=0; i<tanda; i++){
            if(pegawai[i].nama==nama){
                for(int j=i; j<tanda-1; j++){
                pegawai[j]=pegawai[j+1];
                }
                cout<<"Delete Data Pegawai Sukses!" << endl;
                tanda--;
                cek=true;
                break;
            }
        }
        if(!cek){
            cout << "Data yang dihapus tidak ada!" << endl;
        }
    } else {
        cout<<"Opsi Salah!"<<endl;
    }
    simpanData();
    system("Pause");
    system("CLS");
}

// fungsi update data pegawai
void updatePegawai(){
    string nama, nip, cek;
    int tmp;
    bool temp=false;

    cout<<"---Opsi Update---"<<endl;
    cout<<"1. Berdasarkan NIP"<<endl;
    cout<<"2. Berdasarkan Nama"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>tmp;

    if(tmp==1){
        cout<<"Masukkan NIP: ";
        cin>>cek;
        for(int i=0; i<tanda; i++){
            if(pegawai[i].nip==cek){
                cout<<"Masukkan Nama Baru: ";
                getline(cin>>ws, nama);
                pegawai[i].nama=nama;
                cout<<"Masukkan NIP Baru: ";
                cin>>nip;
                pegawai[i].nip=nip;
                cout<<"Update Berhasil!!"<<endl<<endl;
                temp=true;
                break;
            }
        }
        if(!temp){
            cout<<"Data tidak ditemukan!"<<endl<<endl;
        }
    } else if(tmp==2){
        cout<<"Masukkan Nama: ";
        getline(cin>>ws, cek);
        for(int i=0; i<tanda; i++){
            if(pegawai[i].nama==cek){
                cout<<"Masukkan Nama Baru: ";
                getline(cin>>ws, nama);
                pegawai[i].nama=nama;
                cout<<"Masukkan NIP Baru: ";
                cin>>nip;
                pegawai[i].nip=nip;
                cout<<"Update Berhasil!!"<<endl<<endl;
                temp=true;
                break;
            }
        }
        if(!temp){
            cout<<"Data tidak ditemukan!"<<endl<<endl;
        }
    } else {
        cout<<"Opsi Salah!"<<endl;
    }    
    simpanData();
    system("Pause");
    system("CLS");
}

// Fungsi sort data pegawai
void sortPegawai(){
    //sort(pegawai, pegawai+tanda, tukar);
    int tmp, cek;
    cout<<"---Opsi Sort---"<<endl;
    cout<<"1. Berdasarkan NIP"<<endl;
    cout<<"2. Berdasarkan Nama"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>tmp;

    if(tmp==1){
        cout<<"---Metode---"<<endl;
        cout<<"1. Terendah"<<endl;
        cout<<"2. Tertinggi"<<endl;
        cout<<"Pilih Opsi: ";
        cin>>cek;
        if(cek==1){
            sort(pegawai, pegawai+tanda, tukarMinNip);
            cout<<"Sort dari NIP Terendah Berhasil!!"<<endl<<endl;
        } else if(cek==2){
            sort(pegawai, pegawai+tanda, tukarMaxNip);
            cout<<"Sort dari NIP Tertinggi Berhasil!!"<<endl<<endl;
        } else{
            cout<<"Opsi Salah!!"<<endl;
        }
    } else if(tmp==2){
        cout<<"---Metode---"<<endl;
        cout<<"1. A-Z"<<endl;
        cout<<"2. Z-A"<<endl;
        cout<<"Pilih Opsi: ";
        cin>>cek;
        if(cek==1){
            sort(pegawai, pegawai+tanda, tukarMinNama);
            cout<<"Sort dari Nama A-Z Berhasil!!"<<endl<<endl;
        } else if(cek==2){
            sort(pegawai, pegawai+tanda, tukarMaxNama);
            cout<<"Sort dari Nama Z-A Berhasil!!"<<endl<<endl;
        } else{
            cout<<"Opsi Salah!!"<<endl;
        }
    } else{
        cout<<"Opsi Salah!!"<<endl;
    }
    simpanData();
    system("Pause");
    system("CLS");
}

void exit(){
    exit(0);
}

void head(){
    cout<<"\n----------------------------------"<<endl;
    cout<<"SELAMAT DATANG DI KELOLA DATA PEGAWAI"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"List Opsi: "<<endl;
}

int main (){
    bacaData();
    system("cls");
    for(int i=1; i>0; i++){
        head();
        cout<<"  1: Tambah Data Pegawai"<<endl;
        cout<<"  2: Lihat Data Pegawai"<<endl;
        cout<<"  3: Cari Data Pegawai"<<endl;
        cout<<"  4: Delete Data Pegawai"<<endl;
        cout<<"  5: Update Data Pegawai"<<endl;
        cout<<"  6: Urutkan Data Pegawai"<<endl;
        cout<<"  0: Keluar Program"<<endl;

        cout<<endl;
        cout<<"Masukkan Opsi: ";
        cin>>opsi;
        cin.ignore();
        switch(opsi){
            case 1:
                tambahPegawai();
                break;

            case 2:
                lihatPegawai();
                break;

            case 3:
                cariPegawai();
                break;

            case 4:
                deletePegawai();
                break;

            case 5:
                updatePegawai();
                break;

            case 6:
                sortPegawai();
                break;

            case 0:
                cout<<"\n----------------------------------"<<endl;
                cout<<"Terima Kasih"<<endl;
                cout<<"Selamat Menikmati Hari Anda"<<endl;
                cout<<"----------------------------------"<<endl;
                exit();
                break;
            default:
                cout<<"Masukkan pilihan dengan benar";
                break;
        }
    }
}