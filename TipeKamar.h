#ifndef TIPEKAMAR_H
#define TIPEKAMAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "uii.h"
#include "StructHotel.h"

// Fungsi Helper untuk membersihkan buffer (pengganti fflush(stdin) yang tidak standar)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void simpanDatakeFileTipeKamar(char namaFile[], tipe_kamar arr, int total){
    FILE *Ars = fopen(namaFile, "a");

    if(Ars == NULL){
        printf("gagal membuka file\n");
        return ;
    }  
    
    // Pastikan tidak ada karakter aneh sebelum menyimpan
    fprintf(Ars, "%s,%d,%s,%d,%s,%s,%s,%s\n", 
            arr.tipe_kamar, arr.jumlah_kamar, arr.ukuran_kasur, arr.kapasitas_kamar,
            arr.created_by, arr.created_date, arr.modified_by, arr.modified_date);
    fclose(Ars);
    
    int startX = 35; 
    int startY = 30;
    gotoXY(startX, startY); printf("Data berhasil disimpan ke file\n");
    gotoXY(startX, startY+1); system("pause");
}

void createtipeKamar(tipe_kamar tipebaru[], int *total_tipe){
    clearContent();
    setColor(15, 1);

    int startX = 35; 
    int startY = 15;
    int currentY = startY;

    // Bersihkan buffer di awal untuk jaga-jaga
    // clearInputBuffer(); 

    gotoXY(startX, currentY++); printf("--- Menambah Tipe Kamar Baru ---");
    gotoXY(startX, currentY++); printf("---------------------------");

    // INPUT TIPE KAMAR
    gotoXY(startX, currentY++); printf("Masukkan Tipe Kamar : ");
    gotoXY(startX + 35, currentY - 1); 
    scanf(" %19[^\n]", tipebaru[*total_tipe].tipe_kamar);
    clearInputBuffer(); // PENTING: Bersihkan buffer setelah input string

    // INPUT UKURAN KASUR
    gotoXY(startX, currentY++); printf("Masukkan Ukuran Kasur : ");
    gotoXY(startX + 35, currentY - 1); 
    scanf(" %19[^\n]", tipebaru[*total_tipe].ukuran_kasur);
    clearInputBuffer();

    // INPUT KAPASITAS
    gotoXY(startX, currentY++); printf("Masukkan Kapasitas Kamar : ");
    gotoXY(startX + 35, currentY - 1); 
    scanf("%d", &tipebaru[*total_tipe].kapasitas_kamar);
    clearInputBuffer(); // PENTING: Bersihkan buffer setelah input angka

    tipebaru[*total_tipe].jumlah_kamar = 0;

    const char* active_user = getActiveUsername();
    const char* current_dt  = get_current_datetime(); 
    
    strncpy(tipebaru[*total_tipe].created_by, active_user, 19);
    strncpy(tipebaru[*total_tipe].created_date, current_dt, 19);
    strncpy(tipebaru[*total_tipe].modified_by, "-", 19); // Gunakan dash jika belum diedit
    strncpy(tipebaru[*total_tipe].modified_date, "-", 19);  
    
    simpanDatakeFileTipeKamar("TipeKamar.txt", tipebaru[*total_tipe], *total_tipe);
    *total_tipe = *total_tipe + 1;
    
    clearContent();
}

void tampilkantipekamar(int total_tipe){
    clearContent();
    setColor(15, 1); 
    
    int startX = 5; // Geser sedikit ke kiri agar muat
    int startY = 15;

    FILE *source;
    tipe_kamar jenis;
    source = fopen("TipeKamar.txt", "r");
    
    if (source == NULL) {
        gotoXY(startX, startY); printf("File TipeKamar.txt belum ada atau gagal dibuka.");
        gotoXY(startX, startY+2); system("pause");
        return;
    }

    gotoXY(startX, startY - 2);printf("=================================================================================================================================");
    gotoXY(startX, startY - 1);printf("||                                                       TIPE KAMAR HOTEL                                                      ||");
    gotoXY(startX, startY);    printf("=================================================================================================================================");
    gotoXY(startX, startY+1);    
    printf("| %-19s | %-12s | %-20s | %-15s | %-12s | %-19s | %-12s | %-19s |",
            "Tipe Kamar", "Jml Kamar", "Ukuran Kasur", "Kapasitas", "Created By", "Created Date", "Modified By", "Modif Date");
    gotoXY(startX, startY+2);  printf("---------------------------------------------------------------------------------------------------------------------------------");
    
    int i = 3;
    
    // PERBAIKAN DI SINI:
    // Format specifier harus sesuai dengan struct (misal %19[^,]) dan pastikan spasi di awal format string
    // Format: String(19), Int, String(19), Int, String(19), String(19), String(19), String(19)
    while (fscanf(source, " %19[^,],%d,%19[^,],%d,%19[^,],%19[^,],%19[^,],%19[^\n]", 
        jenis.tipe_kamar, 
        &jenis.jumlah_kamar, 
        jenis.ukuran_kasur, 
        &jenis.kapasitas_kamar, // Pakai & karena integer
        jenis.created_by, 
        jenis.created_date,
        jenis.modified_by, 
        jenis.modified_date) == 8){ 

        gotoXY(startX, startY + i);    
        
       printf("| %-19s | %-12d | %-20s | %-15d | %-12s | %-19s | %-12s | %-19s |", 
                jenis.tipe_kamar, 
                jenis.jumlah_kamar,
                jenis.ukuran_kasur,
                jenis.kapasitas_kamar,
                jenis.created_by, 
                jenis.created_date, 
                jenis.modified_by, 
                jenis.modified_date);
        i++;
    }
    
    fclose(source);
    gotoXY(startX, startY+i);  printf("=================================================================================================================================");

    gotoXY(startX, startY+i + 2);
    system("pause");
    clearContent();
}

#endif

// ... (Sisa fungsi ubah dan hapus sama, tapi perbaiki fscanf-nya juga seperti di atas)
// Pada ubahTipeKamar dan hapustipeKamar, ganti %14[^,] menjadi %19[^,]