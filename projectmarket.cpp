#include <iostream>  // Untuk input/output stream (cin, cout)
#include <vector>    // Untuk menggunakan std::vector (struktur data dinamis)
#include <string>    // Untuk menggunakan std::string (teks)
#include <limits>    // Untuk numeric_limits (membersihkan buffer input)
#include <iomanip>   // Untuk setprecision, fixed (format output angka)


using namespace std; 


struct Produk {
    string nama;
    double harga;
    int kuantitas;
};


void tambahProduk(vector<Produk>& keranjang) {
    Produk produkBaru;
    cout << "\n--- Tambah Produk Baru ---" << endl;
    cout << "Masukkan nama produk: ";
    // Menggunakan getline untuk nama produk yang mungkin mengandung spasi
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    getline(cin, produkBaru.nama);

    cout << "Masukkan harga produk: Rp ";
    while (!(cin >> produkBaru.harga) || produkBaru.harga <= 0) {
        cout << "Harga tidak valid. Masukkan angka positif: Rp ";
        cin.clear(); // Hapus flag error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }

    cout << "Masukkan kuantitas: ";
    while (!(cin >> produkBaru.kuantitas) || produkBaru.kuantitas <= 0) {
        cout << "Kuantitas tidak valid. Masukkan angka positif: ";
        cin.clear(); // Hapus flag error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
    }

    keranjang.push_back(produkBaru); // Tambahkan produk ke vector keranjang
    cout << "Produk '" << produkBaru.nama << "' berhasil ditambahkan ke keranjang!\n" << endl;
}


void tampilkanKeranjang(const vector<Produk>& keranjang) {
    if (keranjang.empty()) {
        cout << "\nKeranjang belanja kosong.\n" << endl;
        return;
    }

    cout << "\n--- Isi Keranjang Belanja Anda ---" << endl;
    cout << left << setw(4) << "No."
              << left << setw(25) << "Nama Produk"
              << right << setw(10) << "Harga"
              << right << setw(10) << "Qty"
              << right << setw(15) << "Subtotal" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    double totalBelanja = 0.0;
    for (size_t i = 0; i < keranjang.size(); ++i) {
        const Produk& p = keranjang[i];
        double subtotal = p.harga * p.kuantitas;
        totalBelanja += subtotal;

        cout << left << setw(4) << (i + 1) << "."
                  << left << setw(25) << p.nama
                  << right << setw(10) << fixed << setprecision(0) << p.harga
                  << right << setw(10) << p.kuantitas
                  << right << setw(15) << fixed << setprecision(0) << subtotal << endl;
    }
    cout << "-----------------------------------------------------------------" << endl;
    cout << right << setw(59) << "Total Belanja: Rp "
              << fixed << setprecision(0) << totalBelanja << endl;
    cout << endl;
}


void hapusProduk(vector<Produk>& keranjang) {
    if (keranjang.empty()) {
        cout << "\nKeranjang belanja kosong, tidak ada yang bisa dihapus.\n" << endl;
        return;
    }

    tampilkanKeranjang(keranjang); 

    int nomorProduk;
    cout << "Masukkan nomor produk yang ingin dihapus (1-" << keranjang.size() << "): ";
    while (!(cin >> nomorProduk) || nomorProduk < 1 || nomorProduk > keranjang.size()) {
        cout << "Nomor produk tidak valid. Masukkan angka antara 1 dan " << keranjang.size() << ": ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

  
    cout << "Produk '" << keranjang[nomorProduk - 1].nama << "' berhasil dihapus dari keranjang.\n" << endl;
    keranjang.erase(keranjang.begin() + (nomorProduk - 1));
}


int main() {
    vector<Produk> keranjangBelanja; // Deklarasi vector untuk menyimpan produk di keranjang
    int pilihan;

    do {
        cout << "=== PROGRAM KERANJANG BELANJA ===" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Keranjang" << endl;
        cout << "3. Hapus Produk" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";

       
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 4) {
            cout << "Pilihan tidak valid. Masukkan angka antara 1-4: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (pilihan) {
            case 1:
                tambahProduk(keranjangBelanja);
                break;
            case 2:
                tampilkanKeranjang(keranjangBelanja);
                break;
            case 3:
                hapusProduk(keranjangBelanja);
                break;
            case 4:
                cout << "Terima kasih telah menggunakan program keranjang belanja!\n" << endl;
                break;
            default:
              
                cout << "Pilihan tidak dikenal." << endl;
                break;
        }
    } while (pilihan != 4);

    return 0;
}