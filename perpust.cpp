#include <iostream>
#include <string>
#include <cstdlib> // library untuk malloc dan free
#include <fstream> // library untuk mengatur file external
#include <iomanip> // library untuk membuat output lebih rapi seperti tabel
using namespace std;

// fungsi login admin menggunakan fungsi rerturn, jika user input benar maka return true, jika salah return false
bool loginAdmin(string user, string pass) {
    if (user == "Rosyid" && pass == "101") {
        return true;
    } else {
        return false;
    }
}

// fungsi login user dari dari file user.txt menggunakan library fstream dan fungsi return
bool loginUser(string user, string pass) { 
    ifstream userdanpassword("user.txt"); // buka file user.txt
    string sementara;// sementara adalah variabel untuk menyimpan satu baris dari file secara sementara

   
    while (getline(userdanpassword, sementara)) {  // loop untuk membaca setiap baris dalam file dan disimpan pada variable sementara
        string data[2]; //  menyimpan username dan password yang dipisahkan oleh '|'
        int x = 0; 

        for (int i = 0; i < sementara.length(); i++) { // length adalah fungsi menghitung panjang string dari libray iostream
            if (sementara[i] == '|') {
                x++; 
            } else {
                data[x] += sementara[i];
            }
        }

        string fileUserName = data[0];
        string filePassword = data[1];

        if (user == fileUserName && pass == filePassword) {
            userdanpassword.close(); // close diperlukan untuk menghindari crash karena kita akan membuka file yang lain
            return true;
        }
    }

    userdanpassword.close();
    return false;
}

void reg(string nama, string password){
    ofstream file("user.txt", ios::app); // tambahkan ke file, bukan rewrite
    file <<nama << "|" << password << "\n";
    file.close();

    cout << "Register berhasil! Akun telah ditambahkan.\n";
}


const int maxbuku = 100; //c++ mengharuskan nilai constan pada array, jika tidak maka akan terjadi error

//alokasi dinamis
int *tahun;
int *statusPinjam;

//tipe data string tidak dapat dialokasi dinamis menggunakan malloc
//jika memaksa kana terjadi error
string judul[maxbuku];
string penulis[maxbuku];
string tanggalPinjam[maxbuku];
string tanggalJatuhTempo[maxbuku];
string namaPeminjam[maxbuku];

int jumlahBuku = 0;

// fungsi untuk menyimpan data buku ke file eksternal
void simpanFile() {
    ofstream fileku("databuku.txt"); // buka file databuku.txt, jika tidak ada maka akan dibuat baru

    for (int i = 0; i < jumlahBuku; i++) {
        fileku  << judul[i] << "|"
                << penulis[i] << "|"
                << tahun[i] << "|"
                << statusPinjam[i] << "|"
                << tanggalPinjam[i] << "|"
                << tanggalJatuhTempo[i] << "|"
                << namaPeminjam[i] << "\n";
    }

    fileku.close();
}

//fungsi untuk memuat data buku dari file eksternal ke array
void loadFile() {
    ifstream fileku("databuku.txt");

    string sementara;
    jumlahBuku = 0;

    while (getline(fileku, sementara)) { //ambil satu baris file taruh ke variable
        string data[7];
        int x = 0;

        for (int i = 0; i < sementara.length(); i++) { // fixing sementara menjadi data array
            char huruf = sementara[i];

            if (huruf == '|') {
                x++; // pindah ke kolom berikutnya
            } else {
                data[x] += huruf; // tambahkan huruf ke array
            }
        }

        judul[jumlahBuku] = data[0];
        penulis[jumlahBuku] = data[1];
        tahun[jumlahBuku] = stoi(data[2]);
        statusPinjam[jumlahBuku] = stoi(data[3]);
        tanggalPinjam[jumlahBuku] = data[4];
        tanggalJatuhTempo[jumlahBuku] = data[5];
        namaPeminjam[jumlahBuku] = data[6];

        jumlahBuku++;
    }

    fileku.close();
}

// fungsi untuk menampilkan daftar buku dalam format tabel
void tampilBuku() {
    cout << "\n======================================= DAFTAR BUKU ========================================\n";

    if (jumlahBuku == 0) {
        cout << "Maaf daftar buku masih kosong :<\n";
        return;
    }

    cout << left // rata kiri normalnya rata kanan
        << setw(4)  << "No" //set agar kolom punya 4 character, jirka yang dimasukkan kurang dari 4 character akan langsung diisi dengan spasi
        << setw(15) << "Judul"
        << setw(12) << "Penulis"
        << setw(8)  << "Tahun"
        << setw(12) << "Status"
        << setw(15) << "Peminjam"
        << setw(15) << "Pinjam"
        << setw(15) << "Jatuh Tempo" << endl;

    cout << "--------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahBuku; i++) {
        cout << left
            << setw(4)  << i + 1
            << setw(15) << judul[i]
            << setw(12) << penulis[i]
            << setw(8)  << tahun[i]
            << setw(12) << (statusPinjam[i] ? "Dipinjam" : "Tersedia")
            << setw(15) << namaPeminjam[i]
            << setw(15) << tanggalPinjam[i]
            << setw(15) << tanggalJatuhTempo[i] << endl;
    }
    cout << "============================================================================================\n";
}

//fungsi untuk menambah buku baru
void tambahBuku() {
    if (jumlahBuku >= maxbuku) {
        cout << "Kapasitas penuh!\n"; //maksimal buku 100
        return;
    }

    cin.ignore(); //bersihkan buffer input
    cout << "Judul   : ";
    getline(cin, judul[jumlahBuku]); //agar bisa input spasi

    cout << "Penulis : ";
    getline(cin, penulis[jumlahBuku]);

    cout << "Tahun   : ";
    cin >> tahun[jumlahBuku];

    statusPinjam[jumlahBuku] = 0; //default input
    tanggalPinjam[jumlahBuku] = "-";
    tanggalJatuhTempo[jumlahBuku] = "-";
    namaPeminjam[jumlahBuku] = "-";

    jumlahBuku++;
    simpanFile();

    cout << "Buku berhasil ditambahkan!\n";
}
//fungsi untuk mengedit data buku
void editBuku() {
    tampilBuku(); // tampilkan daftar buku terlebih dahulu

    int edit;
    cout << "Nomor buku: ";
    cin >> edit;
    edit = edit -1; //array mulai dari 0

    if (edit < 0 || edit >= jumlahBuku) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    cin.ignore();
    cout << "Judul baru   : ";
    getline(cin, judul[edit]);

    cout << "Penulis baru : ";
    getline(cin, penulis[edit]);

    cout << "Tahun baru   : ";
    cin >> tahun[edit];

    simpanFile();
    cout << "Buku berhasil diedit!\n";
}

//fungsi untuk menghapus data buku
void hapusBuku() {
    tampilBuku();

    int hapus;
    cout << "Nomor buku yang dihapus: ";
    cin >> hapus;
    hapus = hapus -1;

    if (hapus < 0 || hapus >= jumlahBuku) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    // mengganti data array dengan array berikutnya
    for (int i = hapus; i < jumlahBuku; i++) {
        cout << "hapus loop ke-" << i << endl;
        judul[i] = judul[i + 1];
        penulis[i] = penulis[i + 1];
        tahun[i] = tahun[i + 1];
        statusPinjam[i] = statusPinjam[i + 1];
        tanggalPinjam[i] = tanggalPinjam[i + 1];
        tanggalJatuhTempo[i] = tanggalJatuhTempo[i + 1];
        namaPeminjam[i] = namaPeminjam[i + 1];
    }

    jumlahBuku--;
    simpanFile();
    cout << "Buku berhasil dihapus!\n";
}

//Funsi untuk meminjam buku
void pinjamBuku() {
    tampilBuku();

    int pinjam;
    cout << "Nomor buku: ";
    cin >> pinjam;
    pinjam = pinjam -1;

    if (pinjam < 0 || pinjam >= jumlahBuku) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    if (statusPinjam[pinjam] == 1) {
        cout << "Buku sudah dipinjam!\n";
        return;
    }

    cin.ignore(); //bersihkan buffer input
    cout << "Nama Peminjam: ";
    getline(cin, namaPeminjam[pinjam]);

    cout << "Tanggal pinjam (DD-MM-YYYY): ";
    getline(cin, tanggalPinjam[pinjam]); //getline untuk string dengan spasi

    cout << "Tanggal jatuh tempo (DD-MM-YYYY): ";
    getline(cin, tanggalJatuhTempo[pinjam]);

    statusPinjam[pinjam] = 1;

    simpanFile();
    cout << "Buku berhasil dipinjam!\n";
}

// fungsi kembalikanBuku
void kembalikanBuku() {
    tampilBuku();

    int kembali;
    cout << "Nomor buku: ";
    cin >> kembali;
    kembali = kembali -1;

    if (kembali < 0 || kembali >= jumlahBuku) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    if (statusPinjam[kembali] == 0) {
        cout << "Buku ini belum dipinjam!\n";
        return;
    }

    statusPinjam[kembali] = 0;
    tanggalPinjam[kembali] = "-";
    tanggalJatuhTempo[kembali] = "-";
    namaPeminjam[kembali] = "-";

    simpanFile();
    cout << "Buku berhasil dikembalikan!\n";
}

//fungsi data statistik perpustakaan
void statistik() {
    int tersedia = 0;
    int dipinjam = 0;

    for (int i = 0; i < jumlahBuku; i++) {
        if (statusPinjam[i] == 0) {
            tersedia++;
        } else {
            dipinjam++;
        }
    }

    cout << "Total Buku     : " << jumlahBuku << endl;
    cout << "Buku Tersedia  : " << tersedia << endl;
    cout << "Buku Dipinjam  : " << dipinjam << endl;
}

int main(){
    // alokasi memori array dinamis
    tahun = (int*) malloc( maxbuku* sizeof(int));
    statusPinjam = (int*) malloc( maxbuku* sizeof(int));
    // judul = (string*) malloc( maxbuku* sizeof(string));
    // penulis = (string*) malloc( maxbuku* sizeof(string));
    // tanggalPinjam = (string*) malloc( maxbuku* sizeof(string));
    // tanggalJatuhTempo = (string*) malloc( maxbuku* sizeof(string));
    // namaPeminjam = (string*) malloc( maxbuku* sizeof(string));
    
    cout << "===========================================================================\n";
    cout << "\n";
    cout << "  ######   #######  #######  ######   ##   ##  #######  ########       \n";
    cout << "  ##   ##  ##       ##   ##  ##   ##  ##   ##  ##           ##         \n";
    cout << "  ######   #####    #######  ######   ##   ##  #######      ##         \n";
    cout << "  ##       ##       ##  ##   ##       ##   ##       ##      ##         \n";
    cout << "  ##       #######  ##   ##  ##       #######  #######      ##         \n";
    cout << "\n";
    cout << "                           U I N  S U K A                        \n";
    cout << "===========================================================================\n";
    cout << "============= SELAMAT DATANG DI SISTEM APLIKASI PERPUST ==================\n";
    cout << "===========================================================================\n";
    
    cout << "\n===== SIAPA ANDA? =====\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "3. Register as User\n";    
    cout << "Pilih: ";

    int role;
    cin >> role;

    string user, pass;
    bool benarSalah = false;

    switch (role) {
        case 1 :
            while (benarSalah == false) {
                cout << "\n===== LOGIN =====\n";
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pass;

                benarSalah = (loginAdmin(user, pass));

                if (benarSalah == false)
                {
                    cout << "Salah Username atau Password!\n";
                }
            }
            break;
        case 2 :
            while (benarSalah == false) {
                cout << "\n===== LOGIN =====\n";
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pass;

                benarSalah = (loginUser(user, pass));

                if (benarSalah == false)
                {
                    cout << "Salah Username atau Password!\n";
                }
            }
            break;
        case 3 :
            // string user, pass;
            cout << "\n===== REGISTER =====\n";
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;

            reg(user, pass);
            return 0;

        default:
            cout << "Pilihan tidak valid!\n";
            return 0;
    }

    loadFile();

    if (role == 1 && benarSalah == true) {
        // MENU ADMIN
        while (true) {
            cout << "\n===== MENU ADMIN =====\n";
            cout << "1. Tambah Buku\n";
            cout << "2. Edit Buku\n";
            cout << "3. Hapus Buku\n";
            cout << "4. Tampilkan Buku\n";
            cout << "5. Statistik Perpustakaan\n";
            cout << "0. Keluar\n";
            cout << "Pilih: ";

            int pilih;
            cin >> pilih;

            switch (pilih) {
            case 1:
                tambahBuku();
                break;
            case 2:
                editBuku();
                break;
            case 3:
                hapusBuku();
                break;
            case 4:
                tampilBuku();
                break;
            case 5:
                statistik();
                break;
            case 0:
                return 0;
            default:
                cout << "Pilihan tidak valid!\n";
            }
        }
    }

    else if (role == 2 && benarSalah == true) {
        // MENU USER
        while (true) {
            cout << "\n===== MENU USER =====\n";
            cout << "1. Tampilkan Buku\n";
            cout << "2. Pinjam Buku\n";
            cout << "3. Kembalikan Buku\n";
            cout << "4. Statistik Perpustakaan\n";
            cout << "0. Keluar\n";
            cout << "Pilih: ";

            int pilih;
            cin >> pilih;

            switch (pilih) {
            case 1:
                tampilBuku();
                break;
            case 2:
                pinjamBuku();
                break;
            case 3:
                kembalikanBuku();
                break;
            case 4:
                statistik();
                break;
            case 0:
                return 0;
            default:
                cout << "Pilihan tidak valid!\n";
            }
        }

    //free alokasi memori tahun dan statusPinjam    
    free(tahun);
    free(statusPinjam);
    return 0;
    }
}
