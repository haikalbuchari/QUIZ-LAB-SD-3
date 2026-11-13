#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int SIZE = 20;
enum State { EMPTY, OCCUPIED, DELETED };

struct Slot {
    long long key = 0;
    string value;
    State state = EMPTY;
};

Slot table[SIZE];
int jumlahData = 0;

int hash1(long long key) { return key % 20; }
int hash2(long long key) { return 19 - (key % 19); }
int probe(long long key, int i) { return (hash1(key) + (long long)i * hash2(key)) % SIZE; }

bool insertKey(long long key, const string& val, bool verbose = true) {
    int firstDeleted = -1;
    for (int i = 0; i < SIZE; i++) {
        int idx = probe(key, i);
        if (table[idx].state == OCCUPIED && table[idx].key == key) {
            if (verbose) cout << "Key " << key << " sudah ada (indeks " << idx << "). Insert dibatalkan.\n";
            return false;
        }
        if (table[idx].state == DELETED && firstDeleted == -1) firstDeleted = idx;
        if (table[idx].state == EMPTY) {
            if (firstDeleted != -1) idx = firstDeleted;
            table[idx] = {key, val, OCCUPIED};
            jumlahData++;
            if (verbose) {
                cout << "Insert " << key << " (" << val << ") -> indeks " << idx;
                if (i > 0) cout << "  [COLLISION, probe ke-" << i << "; h1=" << hash1(key) << ", h2=" << hash2(key) << "]";
                cout << "\n";
            }
            return true;
        }
    }
    if (firstDeleted != -1) {
        table[firstDeleted] = {key, val, OCCUPIED};
        jumlahData++;
        if (verbose) cout << "Insert " << key << " (" << val << ") -> indeks " << firstDeleted << " (slot bekas hapus)\n";
        return true;
    }
    if (verbose) cout << "Insert gagal: tidak ada slot yang terjangkau (tabel penuh).\n";
    return false;
}

int searchKey(long long key, int& probes) {
    probes = 0;
    for (int i = 0; i < SIZE; i++) {
        int idx = probe(key, i);
        probes++;
        if (table[idx].state == EMPTY) return -1;
        if (table[idx].state == OCCUPIED && table[idx].key == key) return idx;
    }
    return -1;
}

bool removeKey(long long key) {
    int p;
    int idx = searchKey(key, p);
    if (idx == -1) { cout << "Key " << key << " tidak ditemukan.\n"; return false; }
    table[idx].state = DELETED;
    jumlahData--;
    cout << "Key " << key << " (" << table[idx].value << ") dihapus dari indeks " << idx << ".\n";
    return true;
}

void display() {
    cout << "\nIdx | Status   | NIM (key)  | Nama\n";
    cout << "----+----------+------------+------------\n";
    for (int i = 0; i < SIZE; i++) {
        cout << (i < 10 ? " " : "") << i << "  | ";
        if (table[i].state == OCCUPIED) cout << "TERISI   | " << table[i].key << " | " << table[i].value;
        else if (table[i].state == DELETED) cout << "DIHAPUS  | -          | -";
        else cout << "KOSONG   | -          | -";
        cout << "\n";
    }
    cout << "Jumlah data: " << jumlahData << "/" << SIZE << "\n";
}

void dataUji() {
    struct { long long k; const char* n; } d[] = {
        {2411001, "Andi"},   {2411002, "Budi"},   {2411003, "Citra"},
        {2411004, "Dewi"},   {2411005, "Eka"},    {2411021, "Fajar"},
        {2411041, "Gita"},   {2411022, "Hana"},   {2411010, "Indra"},
        {2411030, "Joko"},   {2411050, "Kirana"}, {2411015, "Lina"},
        {2411035, "Mira"},   {2411060, "Nanda"},  {2411019, "Oka"}
    };
    cout << "--- Memuat 15 data uji ---\n";
    for (auto& x : d) insertKey(x.k, x.n);
}

int main() {
    int pil;
    do {
        cout << "\n===== HASH TABLE MAHASISWA (Double Hashing, size 20) =====\n"
             << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Muat 15 data uji\n0. Keluar\nPilih: ";
        cin >> pil;
        if (pil == 1) {
            long long nim; string nama;
            cout << "NIM  : "; cin >> nim;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nama : "; getline(cin, nama);
            insertKey(nim, nama);
        } else if (pil == 2) {
            long long nim; cout << "NIM dicari: "; cin >> nim;
            int p; int idx = searchKey(nim, p);
            if (idx >= 0) cout << "Ditemukan di indeks " << idx << ": " << table[idx].value << " (" << p << " probe)\n";
            else cout << "NIM " << nim << " tidak ditemukan (" << p << " probe).\n";
        } else if (pil == 3) {
            long long nim; cout << "NIM dihapus: "; cin >> nim;
            removeKey(nim);
        } else if (pil == 4) display();
        else if (pil == 5) dataUji();
        else if (pil != 0) cout << "Pilihan tidak valid.\n";
    } while (pil != 0 && cin);
    return 0;
}