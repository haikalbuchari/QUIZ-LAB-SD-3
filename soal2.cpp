#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct QNode { string nim, nama; QNode* next; };
struct Queue {
    QNode *front = nullptr, *rear = nullptr;
    int count = 0;
    void enqueue(const string& nim, const string& nama) {
        QNode* n = new QNode{nim, nama, nullptr};
        if (!rear) front = rear = n;
        else { rear->next = n; rear = n; }
        count++;
    }
    bool dequeue(string& nim, string& nama) {
        if (!front) return false;
        QNode* t = front;
        nim = t->nim; nama = t->nama;
        front = front->next;
        if (!front) rear = nullptr;
        delete t; count--;
        return true;
    }
    void display() const {
        if (!front) { cout << "  (antrean kosong)\n"; return; }
        int i = 1;
        cout << "  DEPAN -> ";
        for (QNode* p = front; p; p = p->next) cout << "[" << i++ << ". " << p->nim << " " << p->nama << "] ";
        cout << "<- BELAKANG\n";
    }
};

struct SNode { string info; SNode* next; };
struct Stack {
    SNode* top = nullptr;
    void push(const string& s) { top = new SNode{s, top}; }
    bool pop(string& s) {
        if (!top) return false;
        SNode* t = top; s = t->info; top = top->next; delete t; return true;
    }
    void display() const {
        if (!top) { cout << "  (riwayat kosong)\n"; return; }
        int i = 1;
        cout << "  TOP (terbaru) ke bawah:\n";
        for (SNode* p = top; p; p = p->next) cout << "   " << i++ << ". " << p->info << "\n";
    }
};

struct BNode { int id; BNode *left, *right; };

BNode* insertBST(BNode* r, int id, bool& ok) {
    if (!r) { ok = true; return new BNode{id, nullptr, nullptr}; }
    if (id < r->id) r->left = insertBST(r->left, id, ok);
    else if (id > r->id) r->right = insertBST(r->right, id, ok);
    else ok = false;
    return r;
}
bool searchBST(BNode* r, int id) {
    while (r) {
        if (id == r->id) return true;
        r = (id < r->id) ? r->left : r->right;
    }
    return false;
}
void preOrder(BNode* r)  { if (r) { cout << r->id << " "; preOrder(r->left); preOrder(r->right); } }
void inOrder(BNode* r)   { if (r) { inOrder(r->left); cout << r->id << " "; inOrder(r->right); } }
void postOrder(BNode* r) { if (r) { postOrder(r->left); postOrder(r->right); cout << r->id << " "; } }
void printTree(BNode* r, int depth = 0) {
    if (!r) return;
    printTree(r->right, depth + 1);
    cout << string(depth * 6, ' ') << r->id << "\n";
    printTree(r->left, depth + 1);
}
void freeTree(BNode* r) { if (r) { freeTree(r->left); freeTree(r->right); delete r; } }

Queue antrean;
Stack riwayat;
BNode* root = nullptr;

void tambahBuku() {
    int id; cout << "ID buku: "; cin >> id;
    bool ok = false;
    root = insertBST(root, id, ok);
    cout << (ok ? "Buku ditambahkan ke BST.\n" : "ID buku sudah ada.\n");
}

void tambahAntrean() {
    string nim, nama;
    cout << "NIM  : "; cin >> nim;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama : "; getline(cin, nama);
    antrean.enqueue(nim, nama);
    cout << nama << " masuk antrean.\n";
}

void prosesPinjam() {
    string nim, nama;
    if (!antrean.front) { cout << "Antrean kosong.\n"; return; }
    int id; cout << "ID buku yang dipinjam: "; cin >> id;
    if (!searchBST(root, id)) { cout << "Buku ID " << id << " tidak ada di BST. Peminjaman dibatalkan.\n"; return; }
    antrean.dequeue(nim, nama);
    cout << "Peminjaman diproses (FIFO): " << nama << " (" << nim << ") meminjam buku ID " << id << ".\n";
}

void kembalikan() {
    string nim; int id;
    cout << "NIM pengembali: "; cin >> nim;
    cout << "ID buku        : "; cin >> id;
    riwayat.push("NIM " + nim + " mengembalikan buku ID " + to_string(id));
    cout << "Pengembalian dicatat di stack riwayat.\n";
}

void tampilSemua() {
    cout << "\n=== ANTREAN PEMINJAMAN (Queue/FIFO) ===\n"; antrean.display();
    cout << "\n=== RIWAYAT PENGEMBALIAN (Stack/LIFO) ===\n"; riwayat.display();
    cout << "\n=== ISI BST (ID BUKU) ===\n";
    if (!root) cout << "  (kosong)\n"; else printTree(root);
}

void dataContoh() {
    int ids[] = {50, 30, 70, 20, 40, 60, 80};
    bool ok;
    for (int id : ids) root = insertBST(root, id, ok);
    antrean.enqueue("2411001", "Andi");
    antrean.enqueue("2411002", "Budi");
    antrean.enqueue("2411003", "Citra");
    cout << "Data contoh dimuat (7 buku, 3 antrean).\n";
}

int main() {
    int pil;
    do {
        cout << "\n===== PERPUSTAKAAN =====\n"
             << "1. Tambah buku (BST)\n2. Cari ID buku\n3. Traversal Pre/In/Post-Order\n"
             << "4. Tambah antrean peminjam\n5. Proses peminjaman (dequeue)\n"
             << "6. Catat pengembalian buku (push)\n7. Tampilkan antrean, riwayat & BST\n"
             << "8. Muat data contoh\n0. Keluar\nPilih: ";
        cin >> pil;
        switch (pil) {
            case 1: tambahBuku(); break;
            case 2: { int id; cout << "ID dicari: "; cin >> id;
                      cout << "Buku ID " << id << (searchBST(root, id) ? " DITEMUKAN.\n" : " tidak ditemukan.\n"); break; }
            case 3: cout << "Pre-Order : "; preOrder(root);
                    cout << "\nIn-Order  : "; inOrder(root);
                    cout << "\nPost-Order: "; postOrder(root); cout << "\n"; break;
            case 4: tambahAntrean(); break;
            case 5: prosesPinjam(); break;
            case 6: kembalikan(); break;
            case 7: tampilSemua(); break;
            case 8: dataContoh(); break;
            case 0: cout << "Selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pil != 0 && cin);
    freeTree(root);
    return 0;
}