# 🛵 Go-SimpyV2 — Sistem Pemesanan Ojek Online Sederhana

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=c%2B%2B" alt="C++17">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey?style=flat" alt="Cross-platform">
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License">
  <img src="https://img.shields.io/badge/Status-Final%20Project-brightgreen" alt="Status">
</p>

> **Go-SimpyV2** adalah program console berbasis C++ yang mensimulasikan layanan ojek online dengan tiga peran pengguna: **Admin**, **Customer**, dan **Driver**.  
> Proyek ini merupakan tugas akhir mata kuliah Algoritma Pemrograman Lanjut, mengimplementasikan berbagai konsep seperti struct, array of struct, sorting & searching, file I/O, dan autentikasi multi‑role.

---

## ✨ Fitur Utama

- 🔐 **Autentikasi multi‑role** (Admin, Customer, Driver) dengan batas percobaan login.
- 👥 **Manajemen akun** (CRUD) – Admin dapat membuat, mengedit, dan menghapus akun pengguna lain.
- 📦 **Pemesanan ojek** – Customer dapat memesan berdasarkan jarak langsung atau memilih pasangan lokasi dari database CSV.
- 💰 **Pendapatan driver** – Driver melihat riwayat dan total pendapatan.
- 📜 **Histori pemesanan** – Customer melihat daftar pesanan yang pernah dilakukan.
- 🧠 **Sorting & Searching** – Admin dapat mengurutkan akun (Asc/Desc) dan mencari pengguna dengan algoritma linear & binary search.
- 💾 **Penyimpanan persisten** – Data transaksi dan lokasi disimpan dalam file CSV.
- 🎨 **Antarmuka berwarna** dengan efek loading (cross‑platform: Windows & Linux).

---

## 🖥️ Demo (Tampilan Menu)
```text
+-----------------------------------------+
| GO-SIMPY ~ Ojek Sederhana |
+-----------------------------------------+
| MENU ADMIN |
+-----------------------------------------+

1. Edit Profil Saya
2. Tambah Akun
3. Edit Akun Lain
4. Hapus Akun Lain
5. Lihat Semua Akun
6. Lihat Semua Transaksi
7. Cari User (Linear Search)
8. Cari User (Binary Search)
9. Urutkan User A-Z (Ascending)
10. Urutkan User Z-A (Descending)
11. Logout
12. Keluar
```
> *Tampilan serupa tersedia untuk Customer dan Driver.*

---

## 🗂️ Struktur File Proyek
```text
Go-SimpyV2/
├── akun.h # Struktur User, Lokasi, dan deklarasi variabel global
├── functions.h # Deklarasi semua fungsi (manajemen akun, autentikasi, pemesanan)
├── functions.cpp # Implementasi manajemen akun & autentikasi
├── transaksi.cpp # Implementasi pemesanan, histori, pendapatan, & manajemen lokasi
├── validasi.cpp # Fungsi validasi input (username, password, email, dll)
├── tampilan.h/.cpp # UI berbasis warna, loading, input menu, header
├── sortingsearch.h/.cpp # Sorting (asc/desc) dan searching (linear & binary)
├── utils.h/.cpp # Cross‑platform clearScreen(), inputAman(), variabel global
├── main.cpp # Menu utama dan alur program
├── transaksi.csv # Database transaksi (otomatis dibuat jika belum ada)
├── lokasi.csv # Database jarak antar lokasi (bisa ditambah manual)
└── README.md # Dokumentasi ini
```

---

## 🛠️ Cara Kompilasi & Menjalankan

### Persyaratan
- Compiler C++ yang mendukung C++17 (g++, MinGW, clang++)
- Sistem operasi Windows atau Linux

### Langkah‑langkah

1. **Clone repositori**  
   ```bash
   git clone https://github.com/username/Go-SimpyV2.git
   cd Go-SimpyV2
   ```
2. **Kompilasi**
    - Linux/macOS
    ```bash
    g++ -o gosimpy *.cpp
    ```
    - Windows
    ```bash
    g++ -o gosimpy.exe *.cpp
    ```
3. **Jalankan Program**
    - **Linux/macOS**
    ```bash
    ./gosimpy
    ```
    - **Windows**
    ```bash
    & .\gosimpy.exe
    ```

4. **Login default**  
   - **Admin** → username: `admin`, password: `admin`  
   - **Customer** → username: `customer`, password: `customer`  
   - **Driver** → username: `driver`, password: `driver`

---

## 🧪 Contoh Alur Penggunaan

1. **Registrasi akun baru** (Customer/Driver) melalui menu login.
2. **Login** sebagai Customer, pilih "Pesan Ojek":
   - Mode jarak langsung: masukkan angka km.
   - Mode lokasi: pilih asal & tujuan dari daftar yang tersedia (database `lokasi.csv`).
3. Sistem akan memilih driver secara acak, menghitung harga (Rp7.000/km), dan menyimpan transaksi.
4. **Driver** dapat login dan melihat pendapatan beserta rincian per transaksi.
5. **Admin** dapat mengelola akun, melihat semua transaksi, serta menggunakan fitur sorting & searching.

---

## 📊 Format File CSV

### `transaksi.csv`
| Waktu | Customer | Driver | Jarak | Harga |
|-------|----------|--------|-------|-------|
| Tanggal: 10-05-2026 Jam: 03:13:55 | nugrah | driver | 44 | 308000 |

### `lokasi.csv` (pasangan asal–tujuan + jarak)
```
lokasi_asal,lokasi_tujuan,jarak_km
Fakultas Teknik UNMUL,Big Mall Samarinda,7.4
Big Mall Samarinda,Fakultas Teknik UNMUL,7.4
...
```
> Anda dapat menambahkan baris baru secara manual untuk memperluas database lokasi.

---

## 🧠 Algoritma yang Digunakan

| Kategori       | Algoritma                     |
|----------------|-------------------------------|
| **Sorting**    | Bubble Sort (Ascending & Descending) |
| **Searching**  | Linear Search, Binary Search (wajib array terurut) |
| **Struktur data** | Array of Struct (User, Lokasi) |
| **File I/O**   | CSV (baca/tulis dengan fstream) |
| **Cross‑platform** | Preprocessor directives (`_WIN32`) |

---

## 🤝 Kontribusi

Proyek ini dikembangkan untuk keperluan akademik. Saran dan masukan sangat diterima melalui *issue* atau *pull request*.

---

## 📜 Lisensi

Distribusikan di bawah lisensi MIT. Lihat file `LICENSE` untuk informasi lebih lanjut.

---

## 🙏 Ucapan Terima Kasih

- Dosen pengampu mata kuliah Algoritma Pemrograman Lanjut
- Rekan tim yang telah berkontribusi dalam pengujian dan debugging
- Seluruh pihak yang telah memberikan masukan berharga

<p align="center">
  <i>Dibuat untuk keperluan Proyek Akhir Algoritma Pemrograman Lanjut</i><br>
  <b>Go-Simpy – Simple, Fast, Reliable 🛵</b>
</p>
