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
    while (temp != nullptr) {
        cout << "ID: " << temp->id_barang << " | Produk: " << temp->nama_produk << " | Harga: $" << temp->harga << endl;
        temp = temp->next;
    }
    cout << "===================================" << endl;
}


void merge(toko_alat_konstruksi* left, toko_alat_konstruksi* right, toko_alat_konstruksi*& result) {
    toko_alat_konstruksi dummy;
    toko_alat_konstruksi* tail = &dummy;
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


void split(toko_alat_konstruksi* source, toko_alat_konstruksi*& left, toko_alat_konstruksi*& right) {
    toko_alat_konstruksi* slow = source;
    toko_alat_konstruksi* fast = source->next;

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


void mergeSort(toko_alat_konstruksi*& headRef) {
    if (headRef == nullptr || headRef->next == nullptr) {
        return;
    }

    toko_alat_konstruksi* left;
    toko_alat_konstruksi* right;

    split(headRef, left, right);
    mergeSort(left);
    mergeSort(right);

    merge(left, right, headRef);
}


toko_alat_konstruksi* partition(toko_alat_konstruksi* low, toko_alat_konstruksi* high) {
    double pivot = high->harga;
    toko_alat_konstruksi* i = low->next;
    toko_alat_konstruksi* j = low;

    while (j != high) {
        if (j->harga < pivot) {
            swap(i->harga, j->harga);
            swap(i->id_barang, j->id_barang);
            swap(i->nama_produk, j->nama_produk);
            i = i->next;
        }
        j = j->next;
    }
    swap(i->harga, high->harga);
    swap(i->id_barang, high->id_barang);
    swap(i->nama_produk, high->nama_produk);

    return i;
}


void quickSort(toko_alat_konstruksi* low, toko_alat_konstruksi* high) {
    if (low != nullptr && low != high && low != high->next) {
        toko_alat_konstruksi* partitionIndex = partition(low, high);
        quickSort(low, partitionIndex->next);
        quickSort(partitionIndex->next->next, high);
    }
}


void quickSortDescending(toko_alat_konstruksi* head) {
    if (head == nullptr) {
        return;
    }

    toko_alat_konstruksi* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }

    quickSort(head, last);
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


void sortProdukAsc() {
    cout << "\nSorting produk secara ascending berdasarkan harga menggunakan Merge Sort..." << endl;
    mergeSort(head);
    displayProduk();
}


void sortProdukDesc() {
    cout << "\nSorting produk secara descending berdasarkan harga menggunakan Quick Sort..." << endl;
    quickSortDescending(head);
    displayProduk();
}


void sortingOptions() {
    int pilihan;
    do {
        cout << "\n========== Opsi Sorting ==========\n";
        cout << "1. Sorting produk secara Ascending (Merge Sort)\n";
        cout << "2. Sorting produk secara Descending (Quick Sort)\n";
        cout << "0. Keluar dari sorting\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                sortProdukAsc();
                break;
            case 2:
                sortProdukDesc();
                break;
            case 0:
                cout << "Keluar dari opsi sorting.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Mohon coba lagi.\n";
        }
    } while (pilihan != 0);
}


int main() {
    tambahProduk(1, "Excavator", 25000.0);
    tambahProduk(2, "Crane", 35000.0);
    tambahProduk(3, "Hard Hats", 150.0);
    tambahProduk(4, "Reflective Vest", 100.0);
    tambahProduk(5, "Safety Boots", 100.0);
    displayProduk();
    sortingOptions();
    shopping();
    while (keranjangQueue.front != nullptr) {
        dequeueQueue();
    }

    return 0;
}
