#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Mahasiswa {
    string nim, nama;
    int nilai;
    Mahasiswa* next;
};

struct DynamicArray {
    int* data = nullptr;
    int size = 0, capacity = 0;

    void push(int v) {
        if (size == capacity) {
            int newCap = (capacity == 0) ? 2 : capacity * 2;
            int* tmp = new int[newCap];
            for (int i = 0; i < size; i++) tmp[i] = data[i];
            delete[] data;
            data = tmp;
            capacity = newCap;
        }
        data[size++] = v;
    }
    ~DynamicArray() { delete[] data; }
};

Mahasiswa* head = nullptr;
Mahasiswa* tail = nullptr;
DynamicArray nilaiArr;
bool sudahUrut = false;

void tambah(const string& nim, const string& nama, int nilai) {
    Mahasiswa* m = new Mahasiswa{nim, nama, nilai, nullptr};
    if (!head) head = tail = m;
    else { tail->next = m; tail = m; }
    nilaiArr.push(nilai);
    sudahUrut = false;
}

void insertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

void insertionSortMhs(Mahasiswa** a, int n) {
    for (int i = 1; i < n; i++) {
        Mahasiswa* key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j]->nilai > key->nilai) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

Mahasiswa* linearSearch(const string& nim, int& langkah) {
    langkah = 0;
    for (Mahasiswa* p = head; p; p = p->next) {
        langkah++;
        if (p->nim == nim) return p;
    }
    return nullptr;
}

int binarySearch(int* a, int n, int target, int& langkah) {
    int lo = 0, hi = n - 1;
    langkah = 0;
    while (lo <= hi) {
        langkah++;
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int jumlah() { return nilaiArr.size; }

void tampilData() {
    if (!head) { cout << "Belum ada data.\n"; return; }
    cout << "\n--- Data Mahasiswa (urutan input) ---\n";
    int no = 1;
    for (Mahasiswa* p = head; p; p = p->next)
        cout << no++ << ". NIM: " << p->nim << " | Nama: " << p->nama << " | Nilai: " << p->nilai << "\n";
    cout << "Array nilai (kapasitas " << nilaiArr.capacity << "): [ ";
    for (int i = 0; i < nilaiArr.size; i++) cout << nilaiArr.data[i] << " ";
    cout << "]\n";
}

void urutkan() {
    int n = jumlah();
    if (n == 0) { cout << "Belum ada data.\n"; return; }
    insertionSort(nilaiArr.data, n);
    sudahUrut = true;

    Mahasiswa** arr = new Mahasiswa*[n];
    int i = 0;
    for (Mahasiswa* p = head; p; p = p->next) arr[i++] = p;
    insertionSortMhs(arr, n);

    cout << "\n--- Hasil Pengurutan (nilai terkecil -> terbesar) ---\n";
    cout << "Array nilai terurut: [ ";
    for (int k = 0; k < n; k++) cout << nilaiArr.data[k] << " ";
    cout << "]\n";
    for (int k = 0; k < n; k++)
        cout << k + 1 << ". NIM: " << arr[k]->nim << " | Nama: " << arr[k]->nama
             << " | Nilai: " << arr[k]->nilai << "\n";
    delete[] arr;
}

void cariNIM() {
    string nim;
    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;
    int langkah;
    Mahasiswa* m = linearSearch(nim, langkah);
    if (m) cout << "Ditemukan (" << langkah << " langkah): " << m->nim << " | " << m->nama << " | " << m->nilai << "\n";
    else cout << "NIM " << nim << " tidak ditemukan (" << langkah << " langkah).\n";
}

void cariNilai() {
    if (!sudahUrut) {
        cout << "Data belum diurutkan. Urutkan dulu (menu 3) sebelum Binary Search.\n";
        return;
    }
    int target;
    cout << "Masukkan nilai yang dicari: ";
    cin >> target;
    int langkah;
    int idx = binarySearch(nilaiArr.data, jumlah(), target, langkah);
    if (idx == -1) { cout << "Nilai " << target << " tidak ditemukan (" << langkah << " langkah).\n"; return; }
    cout << "Nilai " << target << " ditemukan pada indeks " << idx << " (" << langkah << " langkah).\n";
    cout << "Mahasiswa dengan nilai tersebut:\n";
    for (Mahasiswa* p = head; p; p = p->next)
        if (p->nilai == target) cout << "  - " << p->nim << " | " << p->nama << "\n";
}

void inputMahasiswa() {
    string nim, nama;
    int nilai;
    cout << "NIM   : "; cin >> nim;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama  : "; getline(cin, nama);
    cout << "Nilai : "; cin >> nilai;
    tambah(nim, nama, nilai);
    cout << "Data berhasil ditambahkan.\n";
}

void dataContoh() {
    tambah("2411001", "Andi", 78);
    tambah("2411002", "Budi", 85);
    tambah("2411003", "Citra", 62);
    tambah("2411004", "Dewi", 91);
    tambah("2411005", "Eka", 70);
    tambah("2411006", "Fajar", 85);
    cout << "6 data contoh dimuat.\n";
}

int main() {
    int pil;
    do {
        cout << "\n===== SISTEM NILAI MAHASISWA =====\n"
             << "1. Tambah mahasiswa\n2. Tampilkan data\n3. Urutkan nilai (Insertion Sort)\n"
             << "4. Cari mahasiswa by NIM (Linear Search)\n5. Cari nilai (Binary Search)\n"
             << "6. Muat data contoh\n0. Keluar\nPilih: ";
        cin >> pil;
        switch (pil) {
            case 1: inputMahasiswa(); break;
            case 2: tampilData(); break;
            case 3: urutkan(); break;
            case 4: cariNIM(); break;
            case 5: cariNilai(); break;
            case 6: dataContoh(); break;
            case 0: cout << "Selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pil != 0 && cin);

    while (head) { Mahasiswa* t = head; head = head->next; delete t; }
    return 0;
}