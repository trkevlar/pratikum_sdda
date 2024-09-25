#include <iostream>
#include <cstring>

using namespace std;

struct toko_alat_konstruksi {
    int barang;
    char produk[50];  
    double harga;
};

const int melebihi_kapasitas = 100;
toko_alat_konstruksi penjualan[melebihi_kapasitas];
int total_penjualan = 0;

void produk(int id_barang, const char* nama_produk, double harga) {
    if (total_penjualan < melebihi_kapasitas) {
        penjualan[total_penjualan].barang = id_barang;
        strncpy(penjualan[total_penjualan].produk, nama_produk, sizeof(penjualan[total_penjualan].produk) - 1);
        penjualan[total_penjualan].produk[sizeof(penjualan[total_penjualan].produk) - 1] = '\0';  
        penjualan[total_penjualan].harga = harga;
        total_penjualan++;
    } else {
        cout << "Error: Penjualan penuh, tidak bisa menambah lebih banyak." << endl;
    }
}

void readSales() {
    for (int i = 0; i < total_penjualan; ++i) {
        cout << "ID: " << penjualan[i].barang << ", Produk: " << penjualan[i].produk << ", Harga: $" << penjualan[i].harga << endl;
    }
}

int main() {
    produk(1, "Excavator", 25000.0);
    produk(2, "Crane", 35000.0);
    produk(3, "Hard Hats", 150.0);
    produk(4, "Reflective vest", 100.0);
    produk(5, "Safety Boots", 100.0);

    cout << "Daftar Produk di Toko Alat Konstruksi:" << endl;
    readSales();

    return 0;
}