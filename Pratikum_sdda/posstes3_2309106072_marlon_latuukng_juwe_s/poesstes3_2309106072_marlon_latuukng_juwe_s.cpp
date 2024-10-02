#include <iostream>
#include <cstring>

using namespace std;


struct toko_alat_konstruksi {
    int barang;
    char produk[50];
    double harga;
    toko_alat_konstruksi* next;
};

toko_alat_konstruksi* head = nullptr;

void produk(int id_barang, const char* nama_produk, double harga) {
    toko_alat_konstruksi* pemilihan_produk = new toko_alat_konstruksi();
    pemilihan_produk->barang = id_barang;
    (pemilihan_produk->produk, nama_produk); 
    pemilihan_produk->harga = harga;
    pemilihan_produk->next = nullptr;

    if (head == nullptr) {
        head = pemilihan_produk;
    }
    else {
        toko_alat_konstruksi* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = pemilihan_produk;
    }
}


void displayMenu() {
    cout << "========== Daftar Produk di Toko Alat Konstruksi ==========" << endl;
    toko_alat_konstruksi* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->barang << " | Produk: " << temp->produk << " | Harga: $" << temp->harga << endl;
        temp = temp->next;
    }
    cout << "==========================================================" << endl;
}


void clearList() {
    toko_alat_konstruksi* temp = head;
    while (temp != nullptr) {
        toko_alat_konstruksi* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}


void shopping() {
    int choice;
    double totalCost = 0;

    do {
        cout << "Masukkan ID dari produk yang ingin dibeli (0 untuk selesai): ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            toko_alat_konstruksi* current = head;
            while (current != nullptr) {
                if (current->barang == choice) {
                    cout << "Menambahkan " << current->produk << " ke keranjang. Harga: $" << current->harga << endl;
                    totalCost += current->harga;
                    break;
                }
                current = current->next;
            }
        }
        else if (choice != 0) {
            cout << "ID tidak ditemukan. Mohon coba kembali." << endl;
        }
    } while (choice != 0);

    cout << "Terima kasih atas belanja anda! Total belanja: $" << totalCost << endl;
}

int main() {

    produk(1, "Excavator", 25000.0);
    produk(2, "Crane", 35000.0);
    produk(3, "Hard Hats", 150.0);
    produk(4, "Reflective vest", 100.0);
    produk(5, "Safety Boots", 100.0);

    displayMenu();
    shopping();
    clearList();

    return 0;
}
