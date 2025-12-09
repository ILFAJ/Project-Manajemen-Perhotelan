#ifndef UII_H
#define UII_H
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "StructHotel.h"

// ================== GLOBAL WIDTH / HEIGHT ==================
int WIDTH = 120;
int HEIGHT = 40;

// ================== UTIL ==================
void updateConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    WIDTH  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
    HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void gotoXY(int x, int y){
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setColor(int fg, int bg){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg + bg * 16);
}

void clearScreen(){
    system("cls");
}

// ================== FULLSCREEN ==================
void makeFullscreen(){
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
    Sleep(80);
    updateConsoleSize();
}

// ================== BACKGROUND BIRU ==================
void drawBackground(){
    setColor(15, 1);
    for(int y = 0; y < HEIGHT; y++){
        gotoXY(0, y);
        for(int x = 0; x < WIDTH; x++){
            printf(" ");
        }
    }
}

// ================== SIDEBAR (FIXED) ==================
void drawSidebar(){
    setColor(15, 1);

    for(int y = 0; y < HEIGHT; y++){
        gotoXY(0, y); printf("|");
        gotoXY(1, y); printf("|");
    }
}

// ================== SEPARATOR ==================
void drawSeparators(){
    setColor(15, 1);

    // Kolom batas setelah sidebar
    int sepX = 30;

    for(int y = 0; y < HEIGHT; y++){
        gotoXY(sepX, y);
        printf("|");
    }

    // Garis horizontal bawah judul
    gotoXY(0, 10);
    for(int x = 0; x < WIDTH; x++)
        printf("=");
}

// ================== TITLE ASCII ==================
void drawTitle(){
    setColor(15, 1);
    
    int centerX = (WIDTH / 2) - 25;

    gotoXY(centerX, 1); printf(" _______        _______ _______ _______ _______     ___ ___ _______ _______ _______ ___ \n");
    gotoXY(centerX, 2); printf("|   _   |______|   _   |       |   _   |   _   \\   |   Y   |   _   |       |   _   |   |\n");
    gotoXY(centerX, 3); printf("|.  1   |______|   1___|.|   | |.  1   |.  l   /   |.  1   |.  |   |.|   | |.  1___|.  |\n");
    gotoXY(centerX, 4); printf("|.  _   |      |____   `-|.  |-|.  _   |.  _   1   |.  _   |.  |   `-|.  |-|.  __)_|.  |___\n");
    gotoXY(centerX, 5); printf("|:  |   |      |:  1   | |:  | |:  |   |:  |   |   |:  |   |:  1   | |:  | |:  1   |:  1   |\n");
    gotoXY(centerX, 6); printf("|::.|:. |      |::.. . | |::.| |::.|:. |::.|:. |   |::.|:. |::.. . | |::.| |::.. . |::.. . |\n");
    gotoXY(centerX, 7); printf("`--- ---'      `-------' `---' `--- ---`--- ---'   `--- ---`-------' `---' `-------`-------'\n");
   
}

// ================== MENU BARU (9 Opsi - REVISI) ==================
const char *menuKaryawan[] = {
    "Dashboard",
    "Booking Kamar",
    "Daftar Booking",
    "Check-In",
    "Chek-Out",
    "Kamar",
    "Sewa Venue",
    "Daftar Sewa",      
    "Venue",     
    "Inventaris",
    "Exit"
};
#define MENU_KARYAWAN_COUNT 11

// Menu Tamu
const char *menuTamu[] = {
    "Dashboard",
    "Booking Kamar",
    "Info Kamar & Venue",
    "Fasilitas Hotel",
    "Keluar"
};
#define MENU_TAMU_COUNT 5

// Menu Manajer (Karyawan + Laporan)
const char *menuManajer[] = {
    "Dashboard",
    "Daftar Booking",
    "Daftar Kamar",
    "Daftar Sewa",
    "Daftar Venue",
    "Inventaris",
    "Laporan Transaksi",
    "Keluar",
};
#define MENU_MANAGER_COUNT 8

const char *subMenuKamar[] = {
    
    "Daftar Kamar",
    "Tambah Kamar",
    "Ubah Kamar",
    "Hapus Kamar",
    "Tipe Kamar",
    "<- Kembali",
};
#define SUB_MENU_KAMAR_COUNT 6

const char *subMenuTipeKamar[] = {
    
    "Daftar Tipe",
    "Tambah Tipe",
    "Ubah Tipe",
    "Hapus tipe",
    "<- Kembali",
};
#define SUB_MENU_TIPE_COUNT 5

void drawMenu(const char *menuList[], int menuCount, int highlight){
    int startX = 4; 
    int startY = 14;

    for(int i = 0; i < menuCount; i++){
        gotoXY(startX, startY + i);

        if(i == highlight){
            setColor(0, 15);
            printf("> %-16s ", menuList[i]);  
        } else {
            setColor(15, 1);
            printf("  %-16s ", menuList[i]); 
        }
    }
}
int menuNavigation(const char *menuList[], int menuCount, int *currentPilih){
    int tombol;
    
    drawMenu(menuList, menuCount, *currentPilih); // Tampilkan menu awal

    while(1){
        tombol = getch();

        if (tombol == 224 || tombol == 0) { 
            tombol = getch(); 
            if(tombol == 72) {      // UP
                *currentPilih = (*currentPilih - 1 + menuCount) % menuCount;
                drawMenu(menuList, menuCount, *currentPilih); 
            }
            else if(tombol == 80) { // DOWN
                *currentPilih = (*currentPilih + 1) % menuCount;
                drawMenu(menuList, menuCount, *currentPilih); 
            }
        }
        else if(tombol == 13) { return *currentPilih; }
        else if(tombol == 27) { return -1; }
    }
}

/*void tampiluser(){
    gotoXY(9,5); printf("=Admin Hotel=");
}*/

// ================== CLEAR CONTENT AREA (FIXED) ==================
void clearContent(){
    int startX = 32; // Kolom awal (di kanan garis kolom 30)
    int startY = 11; // Baris awal (DI BAWAH garis horizontal di baris 10)
    setColor(15, 1);
    
    // Hapus area konten dari baris 11 hingga HEIGHT
    for(int y = startY; y < HEIGHT; y++){ 
        gotoXY(startX, y);
        // Cetak spasi hingga akhir layar (WIDTH)
        for(int x = startX; x < WIDTH; x++){
            printf(" ");
        }
    }
}
void clearMenuArea(){
    int startX = 4;  // Posisi X tempat menu dimulai
    int startY = 14; // Posisi Y tempat menu dimulai (di bawah separator)
    int endY = HEIGHT - 2; // Hingga mendekati bagian bawah layar
    setColor(15, 1); // Warna latar belakang sidebar (Putih pada Biru)
    
    // Hapus area menu dari baris 14 hingga akhir
    for(int y = startY; y < endY; y++){ 
        gotoXY(startX, y);
        for(int x = 0; x < 16; x++){
            printf(" ");
        }
    }
}
extern UserRole activeRole; 

const char* getActiveUsername() {
    return activeUsername;
}


const char* get_current_datetime() {
    static char date_str[11];
    time_t now;
    struct tm *tm_info;

    time(&now);
    tm_info = localtime(&now);

    strftime(date_str, sizeof(date_str), "%Y-%m-%d", tm_info);

    return date_str;
}




#endif