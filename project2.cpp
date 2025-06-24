#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>


#ifdef _WIN32
#include <windows.h> // Untuk SetConsoleTextAttribute dan system("cls")
#else
#include <unistd.h>
#endif

using namespace std;

struct Produk {
    string nama;
    double harga;
    int kuantitas;
};

vector<Produk> keranjang;
double totalBelanja = 0.0;

// Membersihkan input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

// Fungsi untuk membersihkan layar
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi pewarnaan teks di terminal
void warna(int kode) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kode);
#else
    cout << "\033[1;" << kode << "m";
#endif
}

// Reset warna ke default
void resetWarna() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    cout << "\033[0m";
#endif
}

// Menambahkan produk ke keranjang
void tambahProduk() {
    clearScreen();
    Produk produk;
    warna(11); cout << "--- Tambah Produk ---" << endl; resetWarna();
    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, produk.nama);

    cout << "Masukkan harga produk: Rp ";
    while (!(cin >> produk.harga) || produk.harga <= 0) {
        cout << "Harga tidak valid. Coba lagi: Rp ";
        clearInputBuffer();
    }

    cout << "Masukkan jumlah produk: ";
    while (!(cin >> produk.kuantitas) || produk.kuantitas <= 0) {
        cout << "Jumlah tidak valid. Coba lagi: ";
        clearInputBuffer();
    }

    keranjang.push_back(produk);
    totalBelanja += produk.harga * produk.kuantitas;

    warna(10);
    cout << "\nProduk berhasil ditambahkan!\n";
    resetWarna();
    cin.ignore(); cin.get(); // pause
}

// Menampilkan isi keranjang
void tampilkanKeranjang() {
    clearScreen();
    warna(14); cout << "=== Isi Keranjang Belanja ===" << endl; resetWarna();

    if (keranjang.empty()) {
        warna(12);
        cout << "Keranjang masih kosong.\n";
        resetWarna();
        cin.ignore(); cin.get();
        return;
    }

    cout << left << setw(4) << "No"
         << left << setw(25) << "Nama Produk"
         << right << setw(10) << "Harga"
         << right << setw(10) << "Qty"
         << right << setw(15) << "Subtotal" << endl;
    cout << string(64, '-') << endl;

    double total = 0;
    for (size_t i = 0; i < keranjang.size(); ++i) {
        const Produk& p = keranjang[i];
        double subtotal = p.harga * p.kuantitas;
        total += subtotal;

        cout << left << setw(4) << (i + 1)
             << left << setw(25) << p.nama
             << right << setw(10) << fixed << setprecision(0) << p.harga
             << right << setw(10) << p.kuantitas
             << right << setw(15) << subtotal << endl;
    }

    cout << string(64, '-') << endl;
    warna(14);
    cout << right << setw(59) << "Total Belanja: Rp " << fixed << setprecision(0) << total << endl;
    resetWarna();

    // Diskon
    double diskon = 0.0;
    if (total >= 20000) {
        diskon = total * 0.2;
        warna(11);
        cout << "Diskon 20%: Rp " << fixed << setprecision(0) << diskon << endl;
        resetWarna();
    }

    double totalSetelahDiskon = total - diskon;
    warna(10);
    cout << "Total Setelah Diskon: Rp " << totalSetelahDiskon << endl;
    resetWarna();

    // Pembayaran
    double uangDibayar;
    cout << "\nMasukkan uang dibayarkan: Rp ";
    while (!(cin >> uangDibayar) || uangDibayar < totalSetelahDiskon) {
        warna(12);
        cout << "Uang tidak cukup. Masukkan nominal yang cukup: Rp ";
        resetWarna();
        clearInputBuffer();
    }

    double kembalian = uangDibayar - totalSetelahDiskon;
    warna(11);
    cout << "Kembalian: Rp " << fixed << setprecision(0) << kembalian << endl;
    resetWarna();

    cin.ignore(); cin.get(); // pause
}

// Menghapus produk dari keranjang
void hapusProduk() {
    clearScreen();
    if (keranjang.empty()) {
        warna(12);
        cout << "Keranjang kosong.\n";
        resetWarna();
        cin.ignore(); cin.get();
        return;
    }

    tampilkanKeranjang();
    cout << "\nMasukkan nomor produk yang akan dihapus: ";
    int idx;
    cin >> idx;

    if (idx < 1 || idx > static_cast<int>(keranjang.size())) {
        warna(12);
        cout << "Nomor tidak valid.\n";
        resetWarna();
        cin.ignore(); cin.get();
        return;
    }

    totalBelanja -= keranjang[idx - 1].harga * keranjang[idx - 1].kuantitas;
    keranjang.erase(keranjang.begin() + idx - 1);

    warna(10);
    cout << "\nProduk berhasil dihapus.\n";
    resetWarna();
    cin.ignore(); cin.get();
}

int main() {
    int pilihan;

    do {
        clearScreen();
        warna(14);
        cout << "=== MENU UTAMA ===" << endl;
        resetWarna();
        cout << "1. Tambah Produk" << endl;
        cout << "2. Lihat Keranjang & Bayar" << endl;
        cout << "3. Hapus Produk" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahProduk(); break;
            case 2: tampilkanKeranjang(); break;
            case 3: hapusProduk(); break;
            case 4:
                warna(11);
                cout << "\nTerima kasih telah menggunakan aplikasi!\n";
                resetWarna();
                break;
            default:
                warna(12);
                cout << "Pilihan tidak tersedia.\n";
                resetWarna();
                cin.ignore(); cin.get();
        }
    } while (pilihan != 4);

return 0;
}