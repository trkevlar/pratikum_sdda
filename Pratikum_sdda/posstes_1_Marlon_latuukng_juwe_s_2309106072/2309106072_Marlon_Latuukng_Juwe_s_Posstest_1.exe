#include <iostream>
using namespace std;

long long segitiga_siku_siku(int bentuk_bilangan) {
    long long perhitungan_setiap_sisi = 1;
    for (int i = 1; i <= bentuk_bilangan; i++) {
        perhitungan_setiap_sisi *= i;
    }
    return perhitungan_setiap_sisi;
}

int main() {
    int string_segitiga;
    cout << "Masukkan berapa angka yang dapat membuat segitiga: ";
    cin >> string_segitiga;

    for (int perjumblahan = 0; perjumblahan < string_segitiga; perjumblahan++) {
        for (int vactor = 0; vactor < string_segitiga - perjumblahan - 1; vactor++) {
            cout << " ";
        }

        for (int vactor = 0; vactor <= perjumblahan; vactor++) {
            cout << segitiga_siku_siku(perjumblahan) / (segitiga_siku_siku(vactor) * segitiga_siku_siku(perjumblahan - vactor)) << " ";
        }
        cout << endl;
    }
    return 0;
}
