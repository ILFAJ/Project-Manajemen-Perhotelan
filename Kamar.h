#ifndef KAMAR_H
#define KAMAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "uii.h"
#include "StructHotel.h"



void simpanDatakeFileKamar(char namaFile[], Kamar arr, int total){
    FILE *Ars = fopen(namaFile, "a");

    if(Ars == NULL){
        printf("gagal membuka file\n");
        return ;
    }  
    
    fprintf(Ars, "%d,%s,%f,%d,%s,%s,%s,%s\n", arr.no, arr.tipe, arr.Harga, arr.status,
            arr.created_by, arr.created_date, arr.modified_by, arr.modified_date);
        //fwrite(&arr[i], sizeof(datakaset), 1, Ars);
    fclose(Ars);
    int startX = 35; // Mulai di area konten
    int startY = 30;
    int currentY = startY;
    gotoXY(startX, startY); printf("Data berhasil disimpan ke file\n");
    gotoXY(startX, startY+1); system("pause");
}

void createKamar(Kamar tambahkamar[], int *total_kamar){
    clearContent();
    setColor(15, 1);

    int startX = 35; // Mulai di area konten
    int startY = 15;
    int currentY = startY;

    gotoXY(startX, currentY++);
    printf("--- Menambah kamar Baru ---");

    gotoXY(startX, currentY++);printf("---------------------------");

    gotoXY(startX, currentY++);printf("Masukkan No Kamar baru (Angka): ");
    gotoXY(startX + 35, currentY - 1); scanf(" %d", &tambahkamar[*total_kamar].no);

    gotoXY(startX, currentY++); printf("Masukkan Tipe Kamar: ");
    gotoXY(startX + 35, currentY - 1); scanf(" %14[^\n]", tambahkamar[*total_kamar].tipe);

    gotoXY(startX, currentY++); printf("Masukkan Harga: Rp");
    gotoXY(startX + 35, currentY - 1); scanf("%f", &tambahkamar[*total_kamar].Harga);

    tambahkamar[*total_kamar].status = 0;

    const char* active_user = getActiveUsername();
    const char* current_dt  = get_current_datetime(); 
    
    // Inisialisasi Created dan Modified fields
    strncpy(tambahkamar[*total_kamar].created_by, active_user, 19);
    strncpy(tambahkamar[*total_kamar].created_date, current_dt, 19);
    strncpy(tambahkamar[*total_kamar].modified_by, "data awal", 19);
    strncpy(tambahkamar[*total_kamar].modified_date, "data awal", 19);
    
    
    simpanDatakeFileKamar("Kamar.txt", tambahkamar[*total_kamar], *total_kamar);
    *total_kamar = *total_kamar +1;
    
    
    clearContent();


}
// Kamar.h
void tampilkankamar(int total_kamar){
    clearContent();

    setColor(15, 1); 
    
    int startX = 35; 
    int startY = 15;


    FILE *source;
    Kamar kamar_hotel;
    source = fopen("Kamar.txt", "r");
    
    gotoXY(startX, startY - 2);printf("==================================================================================================================");
    gotoXY(startX, startY - 1);printf("||                                                DAFTAR KAMAR HOTEL                                            ||");
    gotoXY(startX, startY);    printf("==================================================================================================================");
    gotoXY(startX, startY+1);    
    printf("| %-5s | %-10s | %-15s | %-10s | %-12s | %-12s | %-12s | %-12s |", 
            "No", "Tipe", "Harga (Rp)", "Status", "Created By", "Created Date", "Modified By", "Modified Date");
    gotoXY(startX, startY+2);  printf("------------------------------------------------------------------------------------------------------------------");

    
    if(total_kamar ==0){
        gotoXY(startX, startY+3); printf("kamar masih belum ada\n");
    }
    int i =3;
    
    while (fscanf(source, " %d,%19[^,],%f,%d,%19[^,],%19[^,],%19[^,],%19[^\n]", 
        &kamar_hotel.no, kamar_hotel.tipe,&kamar_hotel.Harga, &kamar_hotel.status,
        kamar_hotel.created_by, kamar_hotel.created_date,
        kamar_hotel.modified_by, kamar_hotel.modified_date) == 8){ 

        gotoXY(startX, startY + i);    
        
        char status_str[20];
        // Tentukan string status
        switch (kamar_hotel.status){
            case 0: strncpy(status_str, "Tersedia", 19); break;
            case 1: strncpy(status_str, "Terisi", 19); break;
            default: strncpy(status_str, "Invalid", 19); break;
        }

       printf("| %-5d | %-10s | Rp %-12.2f | %-10s | %-12s | %-12s | %-12s | %-12s  |", 
                kamar_hotel.no, 
                kamar_hotel.tipe,
                kamar_hotel.Harga,
                status_str,
                kamar_hotel.created_by, 
                kamar_hotel.created_date, 
                kamar_hotel.modified_by, 
                kamar_hotel.modified_date);

        i++;
    }
    fclose(source);
    gotoXY(startX, startY+i);  printf("==================================================================================================================");

    gotoXY(startX, startY+i + 2);

    system("pause");
    clearContent();


}

void ubahKamar(int *total_kamar){
    Kamar kamar_hotel;
    clearContent();
    setColor(15, 1);

    int startX = 35; // Mulai di area konten
    int startY = 15;
    int currentY = startY;

    gotoXY(startX, currentY++);
    printf("--- Mengubah Data Kamar ---");
    gotoXY(startX, currentY++);
    printf("---------------------------");

    FILE *source, *temp;
    int idTarget;
    bool jalan = false;
    bool found = false;
    
    // Periksa apakah ada kamar
    if(*total_kamar ==0){
        gotoXY(startX, currentY++);
        printf("Daftar kamar Masih Kosong. Tidak ada yang bisa diubah.\n");
        gotoXY(startX, currentY++);
        system("pause");
        clearContent();
        return; // Keluar dari fungsi jika tidak ada kamar
    }
    
    jalan = true;
    
    // UI untuk input nomor kamar
    gotoXY(startX, currentY++);
    printf("Masukkan nomor kamar yang ingin diubah: ");
    gotoXY(startX + 40, currentY - 1);
    scanf("%d", &idTarget);
    
    
    while(idTarget < 0){
        gotoXY(startX, currentY++);
        printf("\nNomor dimasukkan tidak Valid\n");
        gotoXY(startX, currentY++);
        printf("Masukkan ulang nomor: ");
        gotoXY(startX + 25, currentY - 1);
        scanf("%d", &idTarget);
    }
    currentY++; // Spasi
    
    source = fopen("Kamar.txt", "r");
    temp   = fopen("temp.txt", "w");

    if(!source || !temp){
        gotoXY(startX, currentY++);
        printf("Gagal membuka file!\n");
        gotoXY(startX, currentY++);
        system("pause");
        clearContent();
        return;
    }

    // cari data
    while (fscanf(source, " %d,%19[^,],%f,%d,%19[^,],%19[^,],%19[^,],%19[^\n]",
        &kamar_hotel.no, kamar_hotel.tipe,&kamar_hotel.Harga, &kamar_hotel.status,
        kamar_hotel.created_by, kamar_hotel.created_date,
        kamar_hotel.modified_by, kamar_hotel.modified_date) == 8){
    
        if( kamar_hotel.no == idTarget){
            // UI untuk input tipe kamar baru
            gotoXY(startX, currentY++); printf("Nomor Kamar %d ditemukan",kamar_hotel.no);

            gotoXY(startX, currentY++); printf("Masukkan tipe kamar baru: ", kamar_hotel.no);
            gotoXY(startX + 30, currentY - 1); scanf(" %19[^\n]",kamar_hotel.tipe);

            gotoXY(startX, currentY++); printf("Masukkan Harga baru: Rp ");
            gotoXY(startX + 30, currentY - 1); scanf("%f", &kamar_hotel.Harga);

            const char* active_user = getActiveUsername();
            const char* current_dt  = get_current_datetime();
            
            strncpy(kamar_hotel.modified_by, active_user, 19);
            strncpy(kamar_hotel.modified_date, current_dt, 19);
        
            found = true;
            fprintf(temp, "%d,%s,%f,%d,%s,%s,%s,%s\n", kamar_hotel.no, kamar_hotel.tipe, kamar_hotel.Harga, kamar_hotel.status,
                    kamar_hotel.created_by, kamar_hotel.created_date, kamar_hotel.modified_by, kamar_hotel.modified_date);
            
            gotoXY(startX, currentY++);
            printf("Data kamar berhasil diubah.\n");

        } else {
            fprintf(temp, "%d,%s,%f,%d,%s,%s,%s,%s\n", kamar_hotel.no, kamar_hotel.tipe, kamar_hotel.Harga, kamar_hotel.status,
                    kamar_hotel.created_by, kamar_hotel.created_date, kamar_hotel.modified_by, kamar_hotel.modified_date);
            }
    }
    
    if(!found){
        gotoXY(startX, currentY++);
        printf("Nomor kamar %d tidak ditemukan.\n", idTarget);
    }


    fclose(source);
    fclose(temp);

    remove("kamar.txt");
    rename("temp.txt", "Kamar.txt");


    gotoXY(startX, currentY++);
    system("pause");
    clearContent();
}
//belum ui
void hapusKamar(int *total_kamar){
    clearContent();
    setColor(15, 1);
    
    int startX = 35; // Mulai di area konten
    int startY = 15;
    int currentY = startY;

    gotoXY(startX, currentY++);
    printf("--- Menghapus Data Kamar ---");
    gotoXY(startX, currentY++);
    printf("----------------------------");


    Kamar kamar_hotel;

    FILE *source, *temp;
    int idTarget;
    bool jalan = false;
    bool found = false;

    // Periksa apakah ada kamar
    if(*total_kamar ==0){
        gotoXY(startX, currentY++);
        printf("Daftar kamar Masih Kosong. Tidak ada yang bisa dihapus.\n");
        gotoXY(startX, currentY++);
        system("pause");
        clearContent();
        return; // Keluar dari fungsi jika tidak ada kamar
    }
    
    jalan = true;
    
    // UI untuk input nomor kamar
    gotoXY(startX, currentY++);
    printf("Masukkan nomor kamar yang ingin dihapus: ");
    gotoXY(startX + 40, currentY - 1);
    scanf("%d", &idTarget);
    

    while(idTarget < 0){
        gotoXY(startX, currentY++);
        printf("\nNomor dimasukkan tidak Valid\n");
        gotoXY(startX, currentY++);
        printf("Masukkan ulang nomor: ");
        gotoXY(startX + 25, currentY - 1);
        scanf("%d", &idTarget);
    }
    
    currentY++; // Spasi


    source = fopen("Kamar.txt", "r");
    temp   = fopen("temp.txt", "w");

    if(!source || !temp){
        gotoXY(startX, currentY++);
        printf("Gagal membuka file!\n");
        gotoXY(startX, currentY++);
        system("pause");
        clearContent();
        return;
    }

    // cari data
    while (fscanf(source, " %d,%19[^,],%f,%d,%19[^,],%19[^,],%19[^,],%19[^\n]",
        &kamar_hotel.no, kamar_hotel.tipe,&kamar_hotel.Harga, &kamar_hotel.status,
        kamar_hotel.created_by, kamar_hotel.created_date,
        kamar_hotel.modified_by, kamar_hotel.modified_date) == 8){
    
    
        if( kamar_hotel.no == idTarget){
           
            found = true;
            *total_kamar = *total_kamar -1;
            gotoXY(startX, currentY++);
            printf("Kamar nomor %d berhasil dihapus.\n", idTarget);

        } else {
            fprintf(temp, "%d,%s,%f,%d,%s,%s,%s,%s\n", kamar_hotel.no, kamar_hotel.tipe, kamar_hotel.Harga, kamar_hotel.status,
                    kamar_hotel.created_by, kamar_hotel.created_date, kamar_hotel.modified_by, kamar_hotel.modified_date);
        }
    }
    
    if(!found){
        gotoXY(startX, currentY++);
        printf("Nomor kamar %d tidak ditemukan.\n", idTarget);
    }


    fclose(source);
    fclose(temp);
    
    remove("kamar.txt");
    rename("temp.txt", "Kamar.txt");


    gotoXY(startX, currentY++);
    system("pause");
    clearContent();
}

#endif

