#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>

using namespace std;

const int MAX_PELANGGAN = 50;
const int MAX_PAKET = 50;

struct Pelanggan
{
    string nama;
    int harga;
};

struct Paket
{
    int harga;
};

struct PaketNode {
    Paket data;
    PaketNode* next;
};

struct Customer {
    string nama;
};

struct PackageHistory
{
    int oldHarga;
    int newHarga;
};

Pelanggan pelanggan[MAX_PELANGGAN];
Paket paket[MAX_PAKET];

stack<PackageHistory> historyStack;
queue<string> customerQueue;

int jml_pelanggan = 0;
int jml_paket = 0;
int menu_utama, menu_tambah, menu_ubah, menu_lihat, menu_hapus, menu_sorting, menu_searching, idx;
string keluar = "n";
string nama;
int counter = 3;
PaketNode* headPaket = nullptr;

void tekan_enter()
{
    cout << "Tekan enter untuk melanjutkan.....";
    cin.ignore();
    cin.get();
    system("cls");
}

int cek_number(int pilihan)
{
    while (true)
    {
        cin >> pilihan;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Input tidak valid, silahkan masukkan angka" << endl;
            cout << "Masukkan angka: ";
        }
        else
        {
            break;
        }
    }

    return pilihan;
}

void tampil_paket()
{
    system("cls");
    cout << "Tampilkan paket: \n";
    cout << "----------------\n";
    PaketNode* temp = headPaket;
    int i = 1;
    while (temp != nullptr) {
        cout << i << ". " << temp->data.harga << "/bulan." << endl;
        temp = temp->next;
        i++;
    }
}

void lihat_riwayat()
{
    if (historyStack.empty())
    {
        cout << "Tidak ada riwayat perubahan paket.\n";
    }
    else
    {
        cout << "Riwayat Perubahan Paket:\n";
        cout << "------------------------\n";
        int i = 1;
        stack<PackageHistory> tempStack = historyStack;
        while (!tempStack.empty())
        {
            PackageHistory history = tempStack.top();
            tempStack.pop();
            cout << "Perubahan " << i << ": Harga Lama: " << history.oldHarga << ", Harga Baru: " << history.newHarga << endl;
            i++;
        }
    }
    tekan_enter();
}

void tampil_pelanggan_ptr(Pelanggan *pelangganArr)
{
    system("cls");
    cout << "Tampilkan pelanggan: \n";
    cout << "---------------\n";
    for (int i = 0; i < jml_pelanggan; i++)
    {
        cout << i + 1 << ".\tNama Pelanggan: " << (pelangganArr + i)->nama << endl;
        cout << "\tJenis Paket: " << (pelangganArr + i)->harga << "/bulan." << endl
             << endl;
    }
}

void shellSort_angka_ascending(Pelanggan *arr, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i].harga;
            int j;
            for (j = i; j >= gap && arr[j - gap].harga > temp; j -= gap)
            {
                arr[j].harga = arr[j - gap].harga;
            }
            arr[j].harga = temp;
        }
    }
}

int partition(Pelanggan *arr, int low, int high) {
    int pivot = arr[high].harga;  // Choose the last element as the pivot
    int i = low - 1;  // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If current element is greater than or equal to the pivot (for descending order)
        if (arr[j].harga >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort_angka_descending(Pelanggan *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quicksort_angka_descending(arr, low, pi - 1);
        quicksort_angka_descending(arr, pi + 1, high);
    }
}

string uppercase(string x)
{
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = toupper(x[i]);
    }
    return x;
}

void selectionSort_huruf_descending(Pelanggan *arr, int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (uppercase(arr[j].nama) > uppercase(arr[min_idx].nama))
            {
                min_idx = j;
            }
            Pelanggan swap = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = swap;
        }
    }
}

void selectionSort_huruf_ascending(Pelanggan *arr, int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (uppercase(arr[j].nama) < uppercase(arr[min_idx].nama))
            {
                min_idx = j;
            }
            Pelanggan swap = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = swap;
        }
    }
}

void selectionSort_huruf_ascending(Pelanggan *data, int n);
void selectionSort_huruf_descending(Pelanggan *data, int n);
void tampil_pelanggan_ptr(Pelanggan *data);

int fibonacci_search_ascending(Pelanggan *data, int n, const string &nama)
{
    int fibMMm2 = 0;              // (m-2)'th Fibonacci number
    int fibMMm1 = 1;              // (m-1)'th Fibonacci number
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci number

    // Find the smallest Fibonacci number greater than or equal to n
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        if (data[i].nama < nama)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (data[i].nama > nama)
        {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            return i;
        }
    }

    if (fibMMm1 && data[offset + 1].nama == nama)
        return offset + 1;

    return -1;
}

int fibonacci_search_descending(Pelanggan *data, int n, const string &nama)
{
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        if (data[i].nama > nama)
        { // Reverse the comparison for descending order
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (data[i].nama < nama)
        { // Reverse the comparison for descending order
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            return i;
        }
    }

    if (fibMMm1 && data[offset + 1].nama == nama)
        return offset + 1;

    return -1;
}

void fibonacciSearch_huruf_ascending(Pelanggan *data, string nama)
{
    selectionSort_huruf_ascending(data, jml_pelanggan);
    tampil_pelanggan_ptr(data);
    cout << "Masukkan nama yang dicari: ";
    cin.ignore();
    getline(cin, nama);

    int index = fibonacci_search_ascending(data, jml_pelanggan, nama);

    if (index != -1)
    {
        cout << "Nama ditemukan di index ke-" << index << endl;
    }
    else
    {
        cout << "Nama tidak ditemukan.\n";
    }
}

void fibonacciSearch_huruf_descending(Pelanggan *data, string nama)
{
    selectionSort_huruf_descending(data, jml_pelanggan);
    tampil_pelanggan_ptr(data);
    cout << "Masukkan nama yang dicari: ";
    cin.ignore();
    getline(cin, nama);

    int index = fibonacci_search_descending(data, jml_pelanggan, nama);

    if (index != -1)
    {
        cout << "Nama ditemukan di index ke-" << index << endl;
    }
    else
    {
        cout << "Nama tidak ditemukan.\n";
    }
}

int jumpSearch(Pelanggan *arr, int n, int x)
{
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1].harga < x)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (arr[prev].harga < x)
    {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (arr[prev].harga == x)
        return prev;

    return -1;
}

void jumpSearch_harga(Pelanggan *data)
{
    int harga;
    shellSort_angka_ascending(data, jml_pelanggan);
    tampil_pelanggan_ptr(data);
    cout << "Masukkan harga yang dicari: ";
    cin >> harga;

    int index = jumpSearch(data, jml_pelanggan, harga);

    if (index != -1)
    {
        cout << "Harga " << harga << " ditemukan pada pelanggan: " << data[index].nama << endl;
    }
    else
    {
        cout << "Harga tidak ditemukan.\n";
    }
}

#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void boyerMoore_nama(Pelanggan *data)
{
    string pat;
    cout << "Masukkan nama yang dicari: ";
    cin.ignore();
    getline(cin, pat);

    bool found = false;
    for (int k = 0; k < jml_pelanggan; k++)
    {
        string txt = data[k].nama;
        int m = pat.size();
        int n = txt.size();

        int badchar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badchar);

        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;

            while (j >= 0 && pat[j] == txt[s + j])
                j--;

            if (j < 0)
            {
                cout << "Nama " << pat << " ditemukan pada index ke-" << k << endl;
                found = true;
                break;
            }
            else
            {
                s += max(1, j - badchar[txt[s + j]]);
            }
        }
    }

    if (!found)
    {
        cout << "Nama tidak ditemukan.\n";
    }
}

bool isCustomerExist(const string& namaPelanggan) {
    for (int i = 0; i < jml_pelanggan; i++) {
        if (pelanggan[i].nama == namaPelanggan) {
            return true;
        }
    }
    return false;
}

void enqueueCustomer(string namaPelanggan) {
    if (customerQueue.size() < MAX_PELANGGAN) {
        customerQueue.push(namaPelanggan);
        cout << "Pelanggan " << namaPelanggan << " telah ditambahkan ke queue.\n";
    } else {
        cout << "Queue penuh, tidak dapat menambah pelanggan.\n";
    }
}

void dequeueCustomer() {
    if (!customerQueue.empty()) {
        string servedCustomer = customerQueue.front();
        customerQueue.pop();
        cout << "Serving customer " << servedCustomer << ".\n";
    } else {
        cout << "Tidak ada pelanggan di Queue.\n";
    }
}

void viewCustomerQueue() {
    if (customerQueue.empty()) {
        cout << "Tidak ada pelanggan didalam queue.\n";
    } else {
        cout << "Pelanggan dalam queue:\n";
        queue<string> tempQueue = customerQueue;  // Temporary queue for display
        int i = 1;
        while (!tempQueue.empty()) {
            string cust = tempQueue.front();
            tempQueue.pop();
            cout << i << ". " << cust << "\n";
            i++;
        }
    }
    tekan_enter();
}

string tambah_paket()
{
    system("cls");
    cout << "Tambah Jenis Paket\n";
    cout << "Masukkan harga paket: ";
    cin.ignore();
    int harga;
    harga = cek_number(harga);
    
    PaketNode* newNode = new PaketNode;
    newNode->data.harga = harga;
    newNode->next = nullptr;
    
    if (headPaket == nullptr) {
        headPaket = newNode;
    } else {
        PaketNode* temp = headPaket;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    jml_paket++;
    return "Berhasil menambah paket.\n";
}

string tambah_pelanggan_ptr(Pelanggan *pelangganPtr)
{
    int pilih_paket;
    while (true)
    {
        system("cls");
        cout << "Masukkan nama pelanggan: ";
        cin.ignore();
        getline(cin, pelangganPtr->nama);
        system("cls");
        cout << "Nama Pelanggan: " << pelangganPtr->nama << endl;
        cout << "Menu Jenis Paket: \n";
        tampil_paket();
        cout << "\nMasukkan pilihan: ";
        pilih_paket = cek_number(pilih_paket);
        if (pilih_paket <= jml_paket)
        {
            pelangganPtr->harga = paket[pilih_paket - 1].harga;
            jml_pelanggan++;
            break;
        }
        else
        {
            system("cls");
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
    return "Berhasil menambah pelanggan.\n";
}

string ubah_paket()
{
    while (true)
    {
        system("cls");
        cout << "Ubah Jenis Paket\n";
        tampil_paket();
        cout << jml_paket + 1 << ". Kembali\n";
        cout << "Masukkan urutan jenis paket yang ingin diubah: ";
        idx = cek_number(idx);
        if (idx >= 1 && idx <= jml_paket)
        {
            PaketNode* temp = headPaket;
            for (int i = 1; i < idx; i++) {
                temp = temp->next;
            }
            int oldHarga = temp->data.harga;
            cout << "Masukkan harga paket baru: ";
            cin.ignore();
            temp->data.harga = cek_number(temp->data.harga);
            int newHarga = temp->data.harga;

            PackageHistory history;
            history.oldHarga = oldHarga;
            history.newHarga = newHarga;
            historyStack.push(history);
        }
        else if (idx == jml_paket + 1)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
    return "Berhasil mengubah harga paket yang dipilih.\n";
}

string ubah_paket_pelanggan()
{
    while (true)
    {
        system("cls");
        cout << "Ubah Paket Pelanggan\n";
        tampil_pelanggan_ptr(pelanggan);
        cout << jml_pelanggan + 1 << "\tKembali\n";
        cout << "Masukkan urutan pelanggan yang ingin diubah: ";
        idx = cek_number(idx);
        if (idx >= 1 && idx <= jml_pelanggan)
        {
            int pilih_paket;
            system("cls");
            cout << "Nama Pelanggan: " << pelanggan[idx - 1].nama << endl;
            cout << "Menu Jenis Paket: \n";
            tampil_paket();
            cout << jml_paket + 1 << ". Kembali\n";
            cout << "Masukkan pilihan: ";
            pilih_paket = cek_number(pilih_paket);
            if (pilih_paket <= jml_paket)
            {
                pelanggan[idx - 1].harga = paket[pilih_paket - 1].harga;
            }
            else if (pilih_paket == jml_paket + 1)
            {
                continue;
            }
            else
            {
                system("cls");
                cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                tekan_enter();
            }
        }
        else if (idx == jml_pelanggan + 1)
        {
            break;
        }

        else
        {
            system("cls");
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
    return "Berhasil mengubah paket pelanggan yang telah dipilih.";
}

string hapus_paket()
{
    while (true)
    {
        system("cls");
        cout << "Menu Hapus Paket\n";
        tampil_paket();
        cout << jml_paket + 1 << ". Kembali\n";
        cout << "Masukkan urutan yang ingin di hapus: ";
        idx = cek_number(idx);
        if (idx >= 1 && idx <= jml_paket)
        {
            if (idx == 1) {
                PaketNode* temp = headPaket;
                headPaket = headPaket->next;
                delete temp;
            } else {
                PaketNode* temp = headPaket;
                for (int i = 1; i < idx - 1; i++) {
                    temp = temp->next;
                }
                PaketNode* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
            }
            jml_paket--;
            break;
        }
        else if (idx == jml_paket + 1)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
    return "Selesai menghapus jenis paket yang telah dipilih.";
}

string hapus_paket_pelanggan()
{
    while (true)
    {
        system("cls");
        cout << "Menu Hapus Pelanggan\n";
        tampil_pelanggan_ptr(pelanggan);
        cout << jml_pelanggan + 1 << ".\tKembali.\n";
        cout << "Masukkan urutan yang ingin dihapus: ";
        idx = cek_number(idx);
        if (idx >= 1 && idx <= jml_pelanggan)
        {
            for (int i = (idx - 1); i < jml_pelanggan - 1; i++)
            {
                pelanggan[i].nama = pelanggan[i + 2].nama;
                pelanggan[i].harga = pelanggan[i + 2].harga;
            }
            jml_pelanggan--;
            break;
        }
        else if (idx == jml_pelanggan + 1)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
    return "Selesai menghapus paket pelanggan yang telah dipilih.";
}

void login(int counter)
{
    string username;
    string password;
    if (counter == 0)
    {
        system("cls");
        cout << "Maaf, Kesempatan login anda telah habis.";
    }
    else if (counter > 0)
    {
        cout << "HALAMAN LOGIN" << endl;
        cout << "Masukkan username: ";
        getline(cin, username);
        cout << "Masukkan password: ";
        getline(cin, password);
        if (username == "admin" && password == "admin")
        {
            while (true)
            {
                system("cls");
                cout << "Menu Utama:\n"
                     << "------------\n"
                     << "1. Tambah Data\n"
                     << "2. Ubah Data\n"
                     << "3. Lihat Data\n"
                     << "4. Hapus Data\n"
                     << "5. Search Data\n"
                     << "6. Lihat Riwayat Perubahan\n"
                     << "7. Queue Instruktur\n"
                     << "8. Keluar\n"
                     << "Masukkan pilihan: ";
                menu_utama = cek_number(menu_utama);
                if (menu_utama == 1)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "Menu Tambah Data:\n"
                             << "-----------------\n"
                             << "1. Tambah Jenis Paket\n"
                             << "2. Tambah Pelanggan\n"
                             << "3. Kembali\n"
                             << "Masukkan pilihan: ";
                        menu_tambah = cek_number(menu_tambah);
                        if (menu_tambah == 1)
                        {
                            cout << tambah_paket();
                            tekan_enter();
                        }
                        else if (menu_tambah == 2)
                        {
                            cout << tambah_pelanggan_ptr(&pelanggan[jml_pelanggan]);
                            tekan_enter();
                        }
                        else if (menu_tambah == 3)
                        {
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_utama == 2)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "Menu Ubah Data:\n"
                             << "---------------\n"
                             << "1. Ubah Jenis Paket\n"
                             << "2. Ubah Paket Pelanggan\n"
                             << "3. Kembali\n"
                             << "Masukkan pilihan: ";
                        menu_ubah = cek_number(menu_ubah);
                        if (menu_ubah == 1)
                        {
                            cout << ubah_paket();
                        }
                        else if (menu_ubah == 2)
                        {
                            cout << ubah_paket_pelanggan();
                        }
                        else if (menu_ubah == 3)
                        {
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_utama == 3)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "Menu Lihat Data:\n"
                             << "----------------\n"
                             << "1. Lihat Jenis Paket\n"
                             << "2. Lihat Paket Pelanggan\n"
                             << "3. Kembali\n"
                             << "Masukkan pilihan: ";
                        menu_lihat = cek_number(menu_lihat);
                        if (menu_lihat == 1)
                        {
                            tampil_paket();
                            tekan_enter();
                        }
                        else if (menu_lihat == 2)
                        {
                            while (true)
                            {
                                system("cls");
                                cout << "Menu Lihat Data Pelanggan:\n"
                                     << "----------------\n"
                                     << "1. Lihat berdasarkan huruf (Ascending)\n"
                                     << "2. Lihat berdasarkan huruf (Descending)\n"
                                     << "3. Lihat berdasarkan angka (Ascending)\n"
                                     << "4. Lihat berdasarkan angka (Descending)\n"
                                     << "5. Kembali\n"
                                     << "Masukkan pilihan: ";
                                menu_sorting = cek_number(menu_sorting);
                                if (menu_sorting == 1)
                                {
                                    selectionSort_huruf_ascending(pelanggan, jml_pelanggan);
                                    tampil_pelanggan_ptr(pelanggan);
                                    tekan_enter();
                                }
                                else if (menu_sorting == 2)
                                {
                                    selectionSort_huruf_descending(pelanggan, jml_pelanggan);
                                    tampil_pelanggan_ptr(pelanggan);
                                    tekan_enter();
                                }
                                else if (menu_sorting == 3)
                                {
                                    shellSort_angka_ascending(pelanggan, jml_pelanggan);
                                    tampil_pelanggan_ptr(pelanggan);
                                    tekan_enter();
                                }
                                else if (menu_sorting == 4)
                                {
                                    quicksort_angka_descending(pelanggan, 0, jml_pelanggan - 1);
                                    tekan_enter();
                                }
                                else if (menu_sorting == 5)
                                {
                                    break;
                                }
                                else
                                {
                                    system("cls");
                                    cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                                    tekan_enter();
                                }
                            }
                        }
                        else if (menu_lihat == 3)
                        {
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_utama == 4)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "Menu Hapus Data:\n"
                             << "----------------\n"
                             << "1. Hapus Jenis Paket\n"
                             << "2. Hapus Pelanggan\n"
                             << "3. Kembali\n"
                             << "Masukkan pilihan: ";
                        menu_hapus = cek_number(menu_hapus);
                        if (menu_hapus == 1)
                        {
                            cout << hapus_paket();
                        }
                        else if (menu_hapus == 2)
                        {
                            cout << hapus_paket_pelanggan();
                        }
                        else if (menu_hapus == 3)
                        {
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_utama == 5)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "Menu Searching Data:\n"
                             << "----------------\n"
                             << "1. Fibonacci Seacrh huruf ascending\n"
                             << "2. Jump Search berdasarkan harga\n"
                             << "3. Boyer Moore berdasarkan nama\n"
                             << "4. Kembali\n"
                             << "Masukkan pilihan: ";
                        menu_searching = cek_number(menu_searching);
                        if (menu_searching == 1)
                        {
                            fibonacciSearch_huruf_ascending(pelanggan, nama);
                            tekan_enter();
                        }
                        else if (menu_searching == 2)
                        {
                            jumpSearch_harga(pelanggan);
                            tekan_enter();
                        }
                        else if (menu_searching == 3)
                        {
                            boyerMoore_nama(pelanggan);
                            tekan_enter();
                        }
                        else if (menu_searching == 4)
                        {
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }

                else if (menu_utama == 6)
                {
                    lihat_riwayat();
                }

                else if (menu_utama == 7) 
                {
                    while (true) {
                        system("cls");
                        cout << "Menu Queue Instruktur:\n"
                            << "---------------\n"
                            << "1. Enqueue pelanggan\n"
                            << "2. Dequeue Pelanggan\n"
                            << "3. Lihat queue pelanggan\n"
                            << "4. Kembali\n"
                            << "Masukkan pilihan: ";
                        menu_ubah = cek_number(menu_ubah);

                        if (menu_ubah == 1) 
                        {
                            cout << "Enter customer name: ";
                            cin.ignore();
                            string namaPelanggan;
                            getline(cin, namaPelanggan);
                            enqueueCustomer(namaPelanggan);
                            break;
                        } 
                        else if (menu_ubah == 2) 
                        {
                            dequeueCustomer();
                        } 
                        else if (menu_ubah == 3) 
                        {
                            viewCustomerQueue();
                        } 
                        else if (menu_ubah == 4) 
                        {
                            break;
                        } 
                        else {
                            system("cls");
                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                            tekan_enter();
                        }
                    }
                }


                else if (menu_utama == 8)
                {
                    system("cls");
                    cout << "Apakah anda ingin keluar? (y/n): ";
                    cin >> keluar;
                    if (keluar != "n")
                    {
                        system("cls");
                        cout << "PROGRAM BERHENTI";
                        return;
                    }
                }
                else
                {
                    system("cls");
                    cout << "Maaf pilihan anda salah! Silakan coba lagi." << endl;
                    tekan_enter();
                }
            }
        }
        else if (username == "admin" && password != "admin")
        {
            system("cls");
            cout << "Password salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
        else if (username != "admin" && password == "admin")
        {
            system("cls");
            cout << "Username salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
        else
        {
            system("cls");
            cout << "Username dan Password salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
    }
    else
    {
        system("cls");
        cout << "Program Berhenti";
    }
}

int main()
{
    login(counter);
    return 0;
}