#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string nama_list[] = {"Bayu", "Argus", "Santos", "Silver"};
    int jumlah_nama = sizeof(nama_list) / sizeof(nama_list[0]); 
    
    for (int i = 0; i < jumlah_nama; i++) {
        cout << nama_list[i] << std::endl;
    }
    return 0;
}