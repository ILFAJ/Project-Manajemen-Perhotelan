#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "uii.h"
#include "login.h" 
#include "StructHotel.h"
#include "Kamar.h"
#include "TipeKamar.h"

UserRole activeRole = BELUM_LOGIN;
int JALANKAN_SISTEM = 1;
int total_kamar = 0;
int total_tipe = 0;

void hitungTotalKamar(){
    FILE *source;
    Kamar kamar_hotel;
    int count = 0;
    
    source = fopen("Kamar.txt", "r");
    if (source == NULL) {
        total_kamar = 0;
        return;
    }
    
    // Hitung baris yang valid
    while (fscanf(source, " %d,%19[^,],%f,%d,%19[^,],%19[^,],%19[^,],%19[^\n]", 
        &kamar_hotel.no, kamar_hotel.tipe,&kamar_hotel.Harga, &kamar_hotel.status,
        kamar_hotel.created_by, kamar_hotel.created_date,
        kamar_hotel.modified_by, kamar_hotel.modified_date) == 8){ 
        count++;
    }
    
    fclose(source);
    total_kamar = count;
}

void hitungTotalTipe(){
    FILE *source;
    tipe_kamar jenis;
    int count = 0;
    
    source = fopen("TipeKamar.txt", "r");
    if (source == NULL) {
        total_tipe = 0;
        return;
    }
    
    // Hitung baris yang valid
     while (fscanf(source, " %14[^,],%d,%19[^,],%d,%19[^,],%19[^,],%19[^,],%19[^\n]", 
        jenis.tipe_kamar, &jenis.jumlah_kamar, jenis.ukuran_kasur, jenis.kapasitas_kamar,
        jenis.created_by, jenis.created_date,
        jenis.modified_by, jenis.modified_date) == 8){ 
        count++;
    }
    
    fclose(source);
    total_tipe = count;
}
//dummy
void tampilDashboard(){
    clearContent(); 


    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== dashboard ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}
void tampilBooking(){
    clearContent(); 


    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== booking kamar ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}

void tampilDaftarBooking(){
    clearContent(); 

    setColor(15, 1); 
    
    int startX = 35;
    int startY = 13;
    
    gotoXY(startX, startY - 2);
    printf("== DAFTAR BOOKING KAMAR ==\n");

    // Header Tabel
    gotoXY(startX, startY);
    printf("| %-10s | %-8s | %-20s | %-15s | %-12s | %-12s |", 
           "No Booking", "No Kamar", "Nama Tamu", "No Telp", "Check-In", "Check-Out");
    
    // Garis Pemisah
    gotoXY(startX, startY + 1);
    printf("+------------+----------+----------------------+-----------------+--------------+--------------+");

    // Isi Tabel
    for(int i = 0; i < JML_BOOKING; i++){
        gotoXY(startX, startY + 2 + i);
        printf("| %-10s | %-8s | %-20s | %-15s | %-12s | %-12s |",
               daftarBooking[i].no_booking,
               daftarBooking[i].no_kamar,
               daftarBooking[i].nama_tamu,
               daftarBooking[i].no_telp,
               daftarBooking[i].tgl_checkin,
               daftarBooking[i].tgl_checkout);
    }
    
    gotoXY(35, startY + 2 + JML_BOOKING + 2);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}
void tampilCheckin(){
    clearContent(); 

    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== Check-in ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 

}
void tampilCheckout(){
    clearContent(); 

    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== Check-out ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}


void tampilDaftarSewa(){
    clearContent(); 


    setColor(15, 1); 
    
    int startX = 35;
    int startY = 13;
    
    gotoXY(startX, startY - 2);
    printf("== DAFTAR SEWA VENUE ==\n");

    // Header Tabel
    gotoXY(startX, startY);
    printf("| %-10s | %-25s | %-12s | %-12s |", 
           "ID Sewa", "Nama Venue", "Status Sewa", "Tgl Acara");
    
    // Garis Pemisah
    gotoXY(startX, startY + 1);
    printf("+------------+---------------------------+--------------+--------------+");

    // Isi Tabel
    for(int i = 0; i < JML_SEWA; i++){
         // Ubah warna status (Opsional: Kuning untuk Scheduled, Hijau untuk Done)
        if(strcmp(daftarSewaVenue[i].status_sewa, "Scheduled") == 0){
             setColor(6, 1); // Kuning
        } else if (strcmp(daftarSewaVenue[i].status_sewa, "Done") == 0){
             setColor(10, 1); // Hijau
        } else {
             setColor(4, 1); // Merah/Default
        }

        gotoXY(startX, startY + 2 + i);
        printf("| %-10s | %-25s | %-12s | %-12s |",
               daftarSewaVenue[i].id_sewa,
               daftarSewaVenue[i].nama_venue,
               daftarSewaVenue[i].status_sewa,
               daftarSewaVenue[i].tgl_acara);

        setColor(15, 1); // Kembalikan warna ke default
    }
    
    gotoXY(35, startY + 2 + JML_SEWA + 2);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}
void tampilSewa(){
    clearContent(); 


    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== Sewa Venue ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}

void tampilDaftarVenue(){
    clearContent(); 


    setColor(15, 1); 
    
    int startX = 35;
    int startY = 13;
    
    gotoXY(startX, startY - 2);
    printf("== DAFTAR VENUE HOTEL ==\n");

    // Header Tabel
    gotoXY(startX, startY);
    printf("| %-25s | %-15s | %-12s |", 
           "Nama Venue", "Tipe Venue", "Status");
    
    // Garis Pemisah
    gotoXY(startX, startY + 1);
    printf("+---------------------------+-----------------+--------------+");

    // Isi Tabel
    for(int i = 0; i < JML_VENUE; i++){
         // Ubah warna status (Opsional)
        if(strcmp(daftarVenue[i].status, "Unavailable") == 0){
             setColor(4, 1); 
        } else {
             setColor(10, 1);
        }

        gotoXY(startX, startY + 2 + i);
        printf("| %-25s | %-15s | %-12s |",
               daftarVenue[i].nama_venue,
               daftarVenue[i].tipe_venue,
               daftarVenue[i].status);

        setColor(15, 1); // Kembalikan warna ke default
    }
    
    gotoXY(35, startY + 2 + JML_VENUE + 2);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}

void tampilDaftarInventaris(){
     clearContent(); 


    setColor(15, 1); 
    
    gotoXY(35, 15);
    printf("== inventaris ==\n");

    gotoXY(35, 17);
    printf("Tekan apa saja untuk kembali...");
    getch();
    
    clearContent(); 
}
void tampilLaporanKeuangan() {
    clearContent(); 
    setColor(15, 1); 
    gotoXY(35, 15); printf("== Laporan Keuangan Manajer ==\n");
    getch(); clearContent(); 
}
void tampilInfoHotel() {
    clearContent(); 
    setColor(15, 1); 
    gotoXY(35, 15); printf("== Info Kamar & Venue (Tamu) ==\n");
    getch(); clearContent(); 
}
void tampilSubMenuTipe(){
    tipe_kamar tipe[100];
    int subsubpil =0;
    clearMenuArea();
    while(1){
        int subHasil = menuNavigation(subMenuTipeKamar, SUB_MENU_TIPE_COUNT, &subsubpil);
                        
        if(subHasil == 4 || subHasil == -1) { // Kembali atau ESC
            break; 
            }
                        
        if(subHasil == 0) { // 0: Daftar tipe
            tampilkantipekamar(total_tipe); 
        } else if (subHasil == 1) { // 1: Tambah tipe
            createtipeKamar(tipe, &total_tipe); 
            hitungTotalTipe();
        } else if (subHasil == 2) { // 2: Ubah tipe
            ubahTipeKamar(&total_tipe);
            hitungTotalTipe();
        } else if (subHasil == 3) { // 3: Hapus tipe
            hapustipeKamar(&total_tipe);
            hitungTotalTipe();
        }
    }
}

//real
void tampilSubMenuKamar(){
    Kamar kamarhotel[100];
    int subpilihan = 0;
    clearContent();
    clearMenuArea();
    hitungTotalKamar();
    while(1){
        int subHasil = menuNavigation(subMenuKamar, SUB_MENU_KAMAR_COUNT, &subpilihan);
                        
        if(subHasil == 5 || subHasil == -1) { // Kembali atau ESC
            break; 
            }
                        
        if(subHasil == 0) { // 0: Daftar Kamar
            tampilkankamar(total_kamar); 
        } else if (subHasil == 1) { // 1: Tambah Kamar
            createKamar(kamarhotel, &total_kamar); 
            hitungTotalKamar();
        } else if (subHasil == 2) { // 2: Ubah Kamar
            ubahKamar(&total_kamar);
            hitungTotalKamar();
        } else if (subHasil == 3) { // 3: Hapus Kamar
            hapusKamar(&total_kamar);
            hitungTotalKamar();
        }else if (subHasil == 4) { // 4. tipe kamar
            tampilSubMenuTipe();
        }
    clearContent();
    }
}

void tampiluser() {
    gotoXY(8, 5); 
    setColor(14, 1); // Warna emas/kuning
    switch(activeRole){
        case TAMU: printf("= Tamu Hotel ="); break;
        case KARYAWAN: printf("= Karyawan Hotel ="); break;
        case MANAGER: printf("= Manajer Hotel ="); break;
        default: printf("= Pengunjung ="); break;
    }
    setColor(15, 1);
}
void menuLoopTamu(const char **menuActive, int menuCount){
    
}
void menuLoopKaryawan(const char **menuActive, int menuCount){
    int pilihanmenu = 0;
    while(JALANKAN_SISTEM){
        int hasilNavigasi = menuNavigation(menuActive, menuCount, &pilihanmenu); 

        if(hasilNavigasi == -1 || hasilNavigasi == menuCount - 1){ // ESC atau menu 'Exit'
            JALANKAN_SISTEM = 0;
            break;
        }

        clearContent();
        switch(hasilNavigasi){
            case 0: tampilDashboard(); break;
            case 1: tampilBooking(); break;
            case 2: tampilDaftarBooking(); break;
            case 3: break; //check in
            case 4: break; //check out
            case 5: tampilSubMenuKamar(); break;
            case 6: tampilSewa();break;
            case 7: tampilDaftarSewa(); break;
            case 8: tampilDaftarVenue();break;
            case 9: tampilDaftarInventaris();break;
            // case 8 adalah Exit
        }
        
        if (JALANKAN_SISTEM) {
             tampiluser(); 
             drawSeparators();
             pilihanmenu = 0;
        }
    }
}

void menuLoopManager(const char **menuActive, int menuCount){
    int pilihanmenu = 0;

    while(JALANKAN_SISTEM){
        int hasilNavigasi = menuNavigation(menuActive, menuCount, &pilihanmenu); 

        if(hasilNavigasi == -1 || hasilNavigasi == menuCount - 1){ // ESC atau menu 'Exit'
            JALANKAN_SISTEM = 0;
            break;
        }

        clearContent();
        switch(hasilNavigasi){
            case 0: tampilDashboard(); break;
            case 1: tampilDaftarBooking(); break; 
            case 2: tampilSubMenuKamar(); break;
            case 3: tampilDaftarSewa(); break;
            case 4: tampilDaftarVenue(); break;
            case 5: tampilDaftarInventaris(); break; 
            case 6: tampilLaporanKeuangan(); break;
            case 7: tampilLaporanKeuangan(); break; // Laporan Operasional (Dummy)
            // case 8 adalah Exit
        }
        
        if (JALANKAN_SISTEM) {
             tampiluser(); 
             drawSeparators();
             pilihanmenu = 0;
        }
    }
}
void menuUtamaLoop(){
    
    // --- DRAWING UI STATIS ---
    clearScreen();
    updateConsoleSize(); 
    drawBackground(); 
    drawSidebar();
    drawSeparators();
    drawTitle();
    
    int pilihanmenu = 0;
    const char **menuActive = NULL;
    int menuCount = 0;
    
    // Tentukan menu berdasarkan peran
    switch(activeRole){
        case TAMU: menuActive = menuTamu; menuCount = MENU_TAMU_COUNT; break;
        case KARYAWAN: menuActive = menuKaryawan; menuCount = MENU_KARYAWAN_COUNT; break;
        case MANAGER: menuActive = menuManajer; menuCount = MENU_MANAGER_COUNT; break;
        default: return; // Harusnya tidak terjadi
    }
    
    tampiluser(); // Tampilkan peran
    switch(activeRole){
        case TAMU: menuLoopTamu(menuActive, menuCount); break;
        case KARYAWAN: menuLoopKaryawan(menuActive, menuCount); break;
        case MANAGER: menuLoopManager(menuActive, menuCount); break;
        default: break;
    }
    
}
int main(){
    // 1. Tampilkan dan proses halaman login.
    if(!processLogin()){
        return 1; // Keluar jika gagal login
    }
    
    // 2. Jika login berhasil, jalankan loop menu berdasarkan peran
    menuUtamaLoop(); 

    // Keluar Program
    clearScreen();
    printf("Keluar program...\n");
    return 0;
}