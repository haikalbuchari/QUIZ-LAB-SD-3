# QUIZ-LAB-SD-3

NAMA : DZAKI HAIKAL BUCHARI
NIM : 251401050
LAB : STRUKTUR DATA 3

LINK VIDEO PENJELASAN : https://youtu.be/yve3u_IaqeI

Deskripsi Program
Soal 1: Sistem Pengelolaan Nilai Mahasiswa (soal1_nilai_mahasiswa.cpp)

Program untuk mengelola data mahasiswa (NIM, nama, nilai).

Single Linked List menyimpan data mahasiswa.
Dynamic Array menyimpan kumpulan nilai. Kapasitasnya digandakan otomatis saat penuh.
Insertion Sort mengurutkan nilai dari yang terkecil hingga terbesar.
Linear Search mencari mahasiswa berdasarkan NIM.
Binary Search mencari nilai tertentu setelah data diurutkan.
Menampilkan data mahasiswa, hasil pengurutan, dan hasil pencarian.

Soal 2: Sistem Antrean dan Pengelolaan Buku Perpustakaan (soal2_antrean_perpustakaan.cpp)

Program sederhana untuk membantu peminjaman dan pengembalian buku.

Queue (FIFO) mengatur antrean mahasiswa yang ingin meminjam buku.
Stack (LIFO) menyimpan riwayat pengembalian buku.
Binary Search Tree menyimpan ID buku, dengan fitur pencarian ID serta traversal Pre-Order, In-Order, dan Post-Order.
Menampilkan proses antrean, riwayat pengembalian, dan isi BST.

Soal 3: Sistem Pencarian Rute di Lingkungan Kampus (soal3_rute_kampus.cpp)

Program pencarian rute antarlokasi dengan graf berbobot tak berarah yang memiliki enam vertex (A, B, C, D, E, F).

Adjacency Matrix merepresentasikan hubungan antarlokasi beserta bobot jaraknya.
BFS dan DFS menelusuri graf dari vertex awal pilihan pengguna.
Dijkstra mencari jarak terpendek, lalu menampilkan rute yang dilalui dan total jaraknya.
Pengguna dapat menentukan vertex awal dan vertex tujuan.

Soal 4: Sistem Pengelolaan Data Mahasiswa Menggunakan Hash Table (soal4_hash_table.cpp)

Program untuk menyimpan data mahasiswa dengan NIM sebagai key dan nama sebagai value.

Hash table berukuran 20 dengan penanganan collision Double Hashing.
Hash1(key) = key % 20
Hash2(key) = 19 - (key % 19)
Fitur Insert, Search, Remove, dan Display.
Menu "Muat 15 data uji" memasukkan 15 data mahasiswa yang mencakup kondisi collision. Proses penghapusan dapat diuji lewat menu Remove.
Penghapusan memakai penanda DELETED agar jalur pencarian data lain tidak terputus.
