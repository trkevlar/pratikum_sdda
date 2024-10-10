#include <iostream>

using namespace std;


struct toko_alat_konstruksi {
    int id_barang;
    char nama_produk[50];
    double harga;
    toko_alat_konstruksi* next;
};


struct keranjang_belanja {
    int id_barang;
    char nama_produk[50];
    double harga;
    keranjang_belanja* next;
};


struct Stack {
    keranjang_belanja* top;
};


struct Queue {
    keranjang_belanja* front;
    keranjang_belanja* rear;
};


toko_alat_konstruksi* head = nullptr;


Stack keranjangStack = { nullptr };


Queue keranjangQueue = { nullptr, nullptr };


void tambahProduk(int id_barang, const char* nama_produk, double harga) {
    toko_alat_konstruksi* produkBaru = new toko_alat_konstruksi();
    produkBaru->id_barang = id_barang;


    int i = 0;
    while (nama_produk[i] != '\0' && i < 49) {
        produkBaru->nama_produk[i] = nama_produk[i];
        i++;
    }
    produkBaru->nama_produk[i] = '\0';

    produkBaru->harga = harga;
    produkBaru->next = nullptr;

    if (head == nullptr) {
        head = produkBaru;
    }
    else {
        toko_alat_konstruksi* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = produkBaru;
    }
}


void displayProduk() {
    cout << "========== Daftar Produk ==========" << endl;
    toko_alat_konstruksi* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id_barang << " | Produk: " << temp->nama_produk << " | Harga: $" << temp->harga << endl;
        temp = temp->next;
    }
    cout << "===================================" << endl;
}


void pushStack(int id_barang, const char* nama_produk, double harga) {
    keranjang_belanja* itemBaru = new keranjang_belanja();
    itemBaru->id_barang = id_barang;


    int i = 0;
    while (nama_produk[i] != '\0' && i < 49) {
        itemBaru->nama_produk[i] = nama_produk[i];
        i++;
    }
    itemBaru->nama_produk[i] = '\0';

    itemBaru->harga = harga;
    itemBaru->next = keranjangStack.top;
    keranjangStack.top = itemBaru;
}


void popStack() {
    if (keranjangStack.top == nullptr) {
        cout << "Tidak ada item untuk dihapus." << endl;
        return;
    }
    keranjang_belanja* temp = keranjangStack.top;
    keranjangStack.top = keranjangStack.top->next;
    cout << "Menghapus item terakhir: " << temp->nama_produk << endl;
    delete temp;
}


void enqueueQueue(int id_barang, const char* nama_produk, double harga) {
    keranjang_belanja* itemBaru = new keranjang_belanja();
    itemBaru->id_barang = id_barang;


    int i = 0;
    while (nama_produk[i] != '\0' && i < 49) {
        itemBaru->nama_produk[i] = nama_produk[i];
        i++;
    }
    itemBaru->nama_produk[i] = '\0';

    itemBaru->harga = harga;
    itemBaru->next = nullptr;

    if (keranjangQueue.rear == nullptr) {
        keranjangQueue.front = itemBaru;
        keranjangQueue.rear = itemBaru;
    }
    else {
        keranjangQueue.rear->next = itemBaru;
        keranjangQueue.rear = itemBaru;
    }
}


void dequeueQueue() {
    if (keranjangQueue.front == nullptr) {
        cout << "Keranjang kosong!" << endl;
        return;
    }
    keranjang_belanja* temp = keranjangQueue.front;
    cout << "Memproses item: " << temp->nama_produk << " Harga: $" << temp->harga << endl;
    keranjangQueue.front = keranjangQueue.front->next;
    if (keranjangQueue.front == nullptr) {
        keranjangQueue.rear = nullptr;
    }
    delete temp;
}


void displayKeranjang() {
    cout << "========== Isi Keranjang ==========" << endl;
    keranjang_belanja* temp = keranjangQueue.front;
    if (temp == nullptr) {
        cout << "Keranjang kosong." << endl;
    }
    while (temp != nullptr) {
        cout << "ID: " << temp->id_barang << " | Produk: " << temp->nama_produk << " | Harga: $" << temp->harga << endl;
        temp = temp->next;
    }
    cout << "===================================" << endl;
}


void shopping() {
    int pilihan_barang;
    double total_biaya = 0;

    do {
        cout << "Masukkan ID dari produk yang ingin dibeli (0 untuk selesai, -1 untuk membatalkan pembelian): ";
        cin >> pilihan_barang;

        if (pilihan_barang == -1) {
            popStack();
            continue;
        }

        if (pilihan_barang >= 1 && pilihan_barang <= 5) {
            toko_alat_konstruksi* current = head;
            while (current != nullptr) {
                if (current->id_barang == pilihan_barang) {
                    cout << "Menambahkan " << current->nama_produk << " ke keranjang. Harga: $" << current->harga << endl;
                    total_biaya += current->harga;
                    pushStack(current->id_barang, current->nama_produk, current->harga);
                    enqueueQueue(current->id_barang, current->nama_produk, current->harga);
                    break;
                }
                current = current->next;
            }
        }
        else if (pilihan_barang != 0) {
            cout << "ID tidak ditemukan. Mohon coba kembali." << endl;
        }
    } while (pilihan_barang != 0);


    cout << "Total belanja: $" << total_biaya << endl;
    displayKeranjang();
}

int main() {

    tambahProduk(1, "Excavator", 25000.0);
    tambahProduk(2, "Crane", 35000.0);
    tambahProduk(3, "Hard Hats", 150.0);
    tambahProduk(4, "Reflective Vest", 100.0);
    tambahProduk(5, "Safety Boots", 100.0);

    displayProduk();

    shopping();

    while (keranjangQueue.front != nullptr) {
        dequeueQueue();
    }

    return 0;
}
