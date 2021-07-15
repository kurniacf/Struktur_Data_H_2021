// BISMILLAH ISOK
// Program AVL Tree mengecek kata dalam kata yang disimpan (trie)
// Referensi : Internet, Github Strukdat, Youtube
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
// struct TrieNode
struct TrieNode {
	int node;
	bool cek;
	struct TrieNode *child[26];
}*head;
// init node tree
void init() {
	head = new TrieNode();      // buat baru
	head->cek = false;          // cek untuk nilai awal dianggap false
	head->node = 0;
}
// fungsi insert
void insert(string kata) {
	TrieNode *current = head;
	current->node++;
    int tmp=0;
    int panjang= kata.length();
	for(int i=0; i<panjang; i++) 	{
        tmp = (int)kata[i] - (int)'a';	    // nilai char dari urutan pertama dalam kata --> gajah -> g  a  j  a  h
        if(current->child[tmp] == NULL) {   
            current->child[tmp] = new TrieNode();
        }
        current->child[tmp]->node++;
        current = current->child[tmp];		
	}
	current->cek = true;
}

bool search(string kata) {
	TrieNode *current = head;
    int tmp=0;
    int panjang= kata.length();
	for(int i=0; i<panjang; i++) {
		tmp=(int)kata[i]-(int)'a';      // nilai char dari urutan pertama dalam kata --> gajah -> g  a  j  a  h
		if(current->child[tmp] == NULL){
			return false;		
        }
		current = current->child[tmp];
	}
	return current->cek;
}

int main() {
	init();
    int n, m;
    string kata, cari_kata;
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>kata;
        insert(kata);
    }
    cin>>m;
    for (int i=0; i<n; i++){
        cin>>cari_kata;
        if (search(cari_kata)){
            cout<<"1"<<endl;
        } else {
            cout<<"0"<<endl;
        }
    }
	return 0;
}