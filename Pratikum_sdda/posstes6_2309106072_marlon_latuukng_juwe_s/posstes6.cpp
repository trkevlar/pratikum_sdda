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


void stringCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < 49) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


void tambahProduk(int id_barang, const char* nama_produk, double harga) {
    toko_alat_konstruksi* produkBaru = new toko_alat_konstruksi();
    produkBaru->id_barang = id_barang;
    stringCopy(produkBaru->nama_produk, nama_produk);
    produkBaru->harga = harga;
    produkBaru->next = nullptr;

    if (head == nullptr) {
        head = produkBaru;
    } else {
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
    if (temp == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
    }
    while (temp != nullptr) {
        cout << "ID: " << temp->id_barang << " | Produk: " << temp->nama_produk << " | Harga: $" << temp->harga << endl;
        temp = temp->next;
    }
    cout << "===================================" << endl;
}


void merge(keranjang_belanja* left, keranjang_belanja* right, keranjang_belanja*& result) {
    keranjang_belanja dummy;
    keranjang_belanja* tail = &dummy;
    dummy.next = nullptr;

    while (left != nullptr && right != nullptr) {
        if (left->harga <= right->harga) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left == nullptr) ? right : left;
    result = dummy.next;
}

void split(keranjang_belanja* source, keranjang_belanja*& left, keranjang_belanja*& right) {
    keranjang_belanja* slow = source;
    keranjang_belanja* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = source;
    right = slow->next;
    slow->next = nullptr;
}


void mergeSort(keranjang_belanja*& headRef) {
    if (headRef == nullptr || headRef->next == nullptr) {
        return;
    }

    keranjang_belanja* left;
    keranjang_belanja* right;

    split(headRef, left, right);
    mergeSort(left);
    mergeSort(right);

    merge(left, right, headRef);
}


void pushStack(int id_barang, const char* nama_produk, double harga) {
    keranjang_belanja* itemBaru = new keranjang_belanja();
    itemBaru->id_barang = id_barang;
    stringCopy(itemBaru->nama_produk, nama_produk);
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
    stringCopy(itemBaru->nama_produk, nama_produk);
    itemBaru->harga = harga;
    itemBaru->next = nullptr;

    if (keranjangQueue.rear == nullptr) {
        keranjangQueue.front = itemBaru;
        keranjangQueue.rear = itemBaru;
    } else {
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
        cout << "Masukkan ID dari produk yang ingin dibeli (0 untuk selesai, -1 untuk membatalkan pembelian terakhir): ";
        cin >> pilihan_barang;

        if (pilihan_barang == 0) {
            break;
        }

        if (pilihan_barang == -1) {
            popStack();
            continue;
        }

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

        if (pilihan_barang != 0 && current == nullptr) {
            cout << "ID tidak ditemukan. Mohon coba kembali." << endl;
        }

    } while (pilihan_barang != 0);

    cout << "Total belanja: $" << total_biaya << endl;
    displayKeranjang();
}


void sortKeranjangAsc() {
    cout << "\nSorting keranjang secara ascending berdasarkan harga menggunakan Merge Sort..." << endl;
    mergeSort(keranjangQueue.front);
    displayKeranjang();
}


void menuUtama() {
    int pilihan;
    do {
        cout << "\n========== Menu Utama ==========\n";
        cout << "1. Tampilkan Produk\n";
        cout << "5. Belanja\n";
        cout << "6. Tampilkan Keranjang\n";
        cout << "7. Sort Keranjang (Ascending)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                displayProduk();
                break;
            case 5:
                shopping();
                break;
            case 6:
                displayKeranjang();
                break;
            case 7:
                sortKeranjangAsc();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 0);
}

int main() {
    tambahProduk(1, "Excavator", 25000.0);
    tambahProduk(2, "Crane", 35000.0);
    tambahProduk(3, "Hard Hats", 150.0);
    tambahProduk(4, "Reflective Vest", 100.0);
    tambahProduk(5, "Safety Boots", 100.0);
    
    cout << "Selamat datang di Toko Alat Konstruksi!\n";
    menuUtama();
    return 0;
}