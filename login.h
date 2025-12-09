#ifndef LOGIN_H
#define LOGIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "StructHotel.h"
#include "uii.h" 

// --- VARIABEL GLOBAL ---
char activeUsername[30] = "";
extern UserRole activeRole; 
extern int JALANKAN_SISTEM; 

// --- KONFIGURASI WARNA ---
#define BG_BLUE 16 
#define COLOR_DEFAULT (15 + BG_BLUE) 
#define COLOR_GOLD    (14 + BG_BLUE) 
#define COLOR_GREEN   (10 + BG_BLUE) 
#define COLOR_RED     (12 + BG_BLUE) 
#define COLOR_CYAN    (11 + BG_BLUE) 
#define COLOR_GRAY    (8 + BG_BLUE)

// Ukuran Kotak Login
#define BOX_W 42
#define BOX_H 12 // Sedikit diperbesar untuk menu

// --- POSISI LAYAR ---
static int screenW = 0;
static int screenH = 0;
static int centerX = 0;
static int centerY = 0;

#define BG_LOGIN (BG_BLUE / 16)
#define SET_LOGIN_COLOR(c) setColor((c) % 16, BG_LOGIN) 

// --- FUNGSI UPDATE LAYOUT ---
static void updateLoginLayout() {
    updateConsoleSize(); 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    screenW = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    screenH = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    centerX = (screenW - BOX_W) / 2;
    centerY = (screenH - BOX_H) / 2;
}

// --- GAMBAR DEKORASI ---
static void drawDecorations() {
    // 1. Gambar Gedung Hotel (Kiri Bawah)
    int yLeft = screenH - 9; 
    int xLeft = 4; 

    SET_LOGIN_COLOR(COLOR_DEFAULT);
    gotoXY(xLeft, yLeft++); printf("    _________   "); 
    gotoXY(xLeft, yLeft++); printf("   |    _    |   ");
    gotoXY(xLeft, yLeft++); printf("   |   | |   |   ");
    SET_LOGIN_COLOR(COLOR_GOLD);
    gotoXY(xLeft, yLeft++); printf("   |A-S T A R|   "); 
    SET_LOGIN_COLOR(COLOR_DEFAULT);
    gotoXY(xLeft, yLeft++); printf("   |_________|   ");
    gotoXY(xLeft, yLeft++); printf("  /___________\\  ");
    gotoXY(xLeft, yLeft++); printf(" |     _|_     |  ");
    gotoXY(xLeft, yLeft++); printf("_|_____________|__");

    // 2. Gambar Pohon Palem (Kanan Bawah)
    int yRight = screenH - 10;
    int xRight = screenW - 20; 
    SET_LOGIN_COLOR(COLOR_GREEN); 
    gotoXY(xRight, yRight++); printf("        /\\/\\       ");
    gotoXY(xRight, yRight++); printf("     \\/  ()  \\/    ");
    gotoXY(xRight, yRight++); printf("   /\\ /\\/  \\/\\ /\\  ");
    gotoXY(xRight, yRight++); printf("  /  \\/ \\/\\/ \\/  \\ ");
    SET_LOGIN_COLOR(COLOR_GOLD); 
    gotoXY(xRight, yRight++); printf("         ||        ");
    gotoXY(xRight, yRight++); printf("         ||        ");
    gotoXY(xRight, yRight++); printf("         ||        ");
    SET_LOGIN_COLOR(COLOR_DEFAULT);
    gotoXY(xRight, yRight++); printf("      _\\_||_/_    ");
}

static void drawLoginBox() {
    SET_LOGIN_COLOR(COLOR_GOLD);
    gotoXY(centerX, centerY); printf("%c", 201); 
    for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 187); 

    for(int i=1; i<=BOX_H; i++) {
        gotoXY(centerX, centerY+i); printf("%c", 186);
        gotoXY(centerX+BOX_W+1, centerY+i); printf("%c", 186);
    }
    gotoXY(centerX, centerY+BOX_H+1); printf("%c", 200);
    for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 188); 
    SET_LOGIN_COLOR(COLOR_DEFAULT);
}

static void showHeader() {
    int headerW = 37;
    int headerX = (screenW - headerW) / 2;
    int headerY = centerY - 7; 
    if(headerY < 0) headerY = 0;

    SET_LOGIN_COLOR(COLOR_GOLD);
    gotoXY(headerX, headerY-2); printf(" ___      _______  _______  ___  ______  \n");
    gotoXY(headerX, headerY-1); printf("|   |    |   _   ||   _   ||   ||   _  \\ \n");
    gotoXY(headerX, headerY);   printf("|.  |    |.  |   ||.  |___||.  ||.  |   |\n");
    gotoXY(headerX, headerY+1); printf("|.  |___ |.  |   ||.  |   ||.  ||.  |   |\n");
    gotoXY(headerX, headerY+2); printf("|:  1   ||:  1   ||:  1   ||:  ||:  |   |\n");
    gotoXY(headerX, headerY+3); printf("|::.. . ||::.. . ||::.. . ||::.||::.|   |\n");
    gotoXY(headerX, headerY+4); printf("`-------'`-------'`-------'`---'`--- ---'\n");
    gotoXY(headerX, headerY+6); printf("       HOTEL MANAGEMENT SYSTEM v1.0     ");
    SET_LOGIN_COLOR(COLOR_DEFAULT); 
}

static void getPassword(char *buffer) {
    char ch;
    int i = 0;
    while(1) {
        ch = getch();
        if(ch == 13) { buffer[i] = '\0'; break; } // Enter
        else if(ch == 8) { // Backspace
            if(i > 0) { i--; printf("\b \b"); }
        } else if (i < 29 && ch >= 32 && ch <= 126) {
            buffer[i] = ch; i++; printf("*");
        }
    }
}

static void clearLoginArea() {
    for(int i=1; i<=BOX_H; i++) {
        gotoXY(centerX+1, centerY+i);
        for(int j=0; j<BOX_W; j++) printf(" ");
    }
}

// --- FITUR REGISTRASI ---
static void processRegister() {
    clearLoginArea();
    int inputX = centerX + 18; 
    int labelX = centerX + 3;

    gotoXY(centerX + 14, centerY + 1); SET_LOGIN_COLOR(COLOR_GOLD); printf("REGISTRASI AKUN"); SET_LOGIN_COLOR(COLOR_DEFAULT);
    
    // Garis pemisah
    gotoXY(centerX, centerY + 2);
    printf("%c", 204); for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 185);

    char new_user[30], new_pass[30], new_name[50];
    
    gotoXY(labelX, centerY + 4); printf("Nama Lengkap :");
    gotoXY(labelX, centerY + 6); printf("Username     :");
    gotoXY(labelX, centerY + 8); printf("Password     :");

    SET_LOGIN_COLOR(COLOR_CYAN);
    gotoXY(inputX, centerY + 4); 
    // Menggunakan scanf sederhana (perlu diperhatikan spasi)
    // Agar lebih aman sebaiknya custom input, tapi scanf cukup untuk contoh
    fflush(stdin);
    gets(new_name); 

    gotoXY(inputX, centerY + 6); scanf("%s", new_user);
    gotoXY(inputX, centerY + 8); getPassword(new_pass);
    SET_LOGIN_COLOR(COLOR_DEFAULT);

    // Simpan ke array struct (Pastikan JML_USER bertambah)
    if (JML_USER < 100) { // Asumsi max 100 user
        strcpy(daftarUser[JML_USER].username, new_user);
        strcpy(daftarUser[JML_USER].password, new_pass);
        strcpy(daftarUser[JML_USER].nama, new_name);
        daftarUser[JML_USER].role = TAMU; // Default Role
        JML_USER++;
        
        gotoXY(centerX + 4, centerY + 10); SET_LOGIN_COLOR(COLOR_GREEN);
        printf("Registrasi Berhasil! Tekan Enter.");
    } else {
        gotoXY(centerX + 4, centerY + 10); SET_LOGIN_COLOR(COLOR_RED);
        printf("Database Penuh! Hubungi Admin.");
    }
    
    SET_LOGIN_COLOR(COLOR_DEFAULT);
    getch();
}

// --- FITUR LUPA PASSWORD ---
static void processForgotPassword() {
    clearLoginArea();
    int inputX = centerX + 18;
    int labelX = centerX + 3;

    gotoXY(centerX + 15, centerY + 1); SET_LOGIN_COLOR(COLOR_GOLD); printf("LUPA PASSWORD"); SET_LOGIN_COLOR(COLOR_DEFAULT);
    
    gotoXY(centerX, centerY + 2);
    printf("%c", 204); for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 185);

    char search_user[30];
    char new_pass[30];
    int foundIndex = -1;

    gotoXY(labelX, centerY + 4); printf("Username Lama:");
    SET_LOGIN_COLOR(COLOR_CYAN);
    gotoXY(inputX, centerY + 4); scanf("%s", search_user);
    SET_LOGIN_COLOR(COLOR_DEFAULT);

    // Cari Username
    for(int i=0; i<JML_USER; i++) {
        if(strcmp(daftarUser[i].username, search_user) == 0) {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex != -1) {
        gotoXY(labelX, centerY + 6); printf("Password Baru:");
        SET_LOGIN_COLOR(COLOR_CYAN);
        gotoXY(inputX, centerY + 6); getPassword(new_pass);
        SET_LOGIN_COLOR(COLOR_DEFAULT);

        // Update Password
        strcpy(daftarUser[foundIndex].password, new_pass);
        
        gotoXY(centerX + 5, centerY + 9); SET_LOGIN_COLOR(COLOR_GREEN);
        printf("Password Berhasil Diubah!");
    } else {
        gotoXY(centerX + 8, centerY + 7); SET_LOGIN_COLOR(COLOR_RED);
        printf("Username tidak ditemukan!");
    }

    SET_LOGIN_COLOR(COLOR_DEFAULT);
    gotoXY(centerX + 8, centerY + 11); printf("[Tekan tombol apapun]");
    getch();
}

// --- LOGIC LOGIN ---
static int attemptLogin() {
    clearLoginArea();
    char user[30], pass[30];
    int attempts = 0;
    int inputX = centerX + 18;
    int labelX = centerX + 3;

    gotoXY(centerX + 16, centerY + 1); SET_LOGIN_COLOR(COLOR_GOLD); printf("LOGIN SYSTEM"); SET_LOGIN_COLOR(COLOR_DEFAULT);
    gotoXY(centerX, centerY + 2);
    printf("%c", 204); for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 185);

    while(attempts < 3) {
        // Reset field
        gotoXY(inputX, centerY + 4); printf("                    ");
        gotoXY(inputX, centerY + 6); printf("                    ");
        gotoXY(centerX + 2, centerY + 9); printf("                                     ");

        gotoXY(labelX, centerY + 4); printf("Username    :");
        gotoXY(labelX, centerY + 6); printf("Password    :");

        SET_LOGIN_COLOR(COLOR_CYAN);
        gotoXY(inputX, centerY + 4); scanf("%s", user);
        gotoXY(inputX, centerY + 6); getPassword(pass);
        SET_LOGIN_COLOR(COLOR_DEFAULT);

        // Cek database
        for (int i = 0; i < JML_USER; i++) {
            if (strcmp(user, daftarUser[i].username) == 0 && strcmp(pass, daftarUser[i].password) == 0) {
                activeRole = daftarUser[i].role;
                strncpy(activeUsername, daftarUser[i].username, 29);
                
                // Efek Login Sukses
                clearLoginArea();
                gotoXY(centerX + 10, centerY + 5); printf("Verifikasi Data...");
                gotoXY(centerX + 5, centerY + 7); 
                SET_LOGIN_COLOR(COLOR_GREEN);
                for(int k=0; k<32; k++) { printf("%c", 219); Sleep(15); }
                SET_LOGIN_COLOR(COLOR_DEFAULT);
                return 1; // Sukses
            }
        }

        attempts++;
        gotoXY(centerX + 5, centerY + 9); SET_LOGIN_COLOR(COLOR_RED);
        printf("Gagal! Sisa percobaan: %d", 3 - attempts);
        SET_LOGIN_COLOR(COLOR_DEFAULT);
        getch();
    }
    return 0; // Gagal 3x
}

// --- MAIN MENU CONTROL ---
static int processLogin() {
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_SHOWMAXIMIZED);
    Sleep(100); 
    system("color 1F");
    
    int loopMenu = 1;
    
    while(loopMenu) {
        system("cls");
        updateLoginLayout();
        drawDecorations();
        showHeader();
        drawLoginBox();

        // Tampilkan Menu Pilihan
        gotoXY(centerX + 14, centerY + 1); SET_LOGIN_COLOR(COLOR_GOLD); printf("MENU UTAMA"); SET_LOGIN_COLOR(COLOR_DEFAULT);
        gotoXY(centerX, centerY + 2);
        printf("%c", 204); for(int i=0; i<BOX_W; i++) printf("%c", 205); printf("%c", 185);

        int menuX = centerX + 10;
        int menuY = centerY + 4;
        
        gotoXY(menuX, menuY);     printf("[1] Login Masuk");
        gotoXY(menuX, menuY + 2); printf("[2] Registrasi Akun");
        gotoXY(menuX, menuY + 4); printf("[3] Lupa Password");
        gotoXY(menuX, menuY + 6); printf("[4] Keluar Sistem");
        
        gotoXY(centerX + 2, centerY + 10); SET_LOGIN_COLOR(COLOR_GRAY); printf("Pilih menu [1-4]: "); SET_LOGIN_COLOR(COLOR_DEFAULT);
        
        char choice = getch();

        switch(choice) {
            case '1': // Login
                if (attemptLogin()) {
                    // Jika sukses login, tampilkan pesan selamat datang
                    system("cls");
                    drawDecorations();
                    showHeader();
                    int dashX = (screenW - 60) / 2;
                    gotoXY(dashX + 18, centerY + 1); SET_LOGIN_COLOR(COLOR_GREEN);
                    printf("SELAMAT DATANG DI HOTEL A-STAR");
                    SET_LOGIN_COLOR(COLOR_DEFAULT);
                    getch();
                    return 1; // Masuk ke sistem utama
                }
                break;
            
            case '2': // Registrasi
                processRegister();
                break;
            
            case '3': // Lupa Password
                processForgotPassword();
                break;
            
            case '4': // Keluar
                system("cls");
                gotoXY(centerX + 10, centerY); printf("Terima Kasih.");
                Sleep(1000);
                JALANKAN_SISTEM = 0; // Set flag berhenti
                return 0;
            
            default:
                break;
        }
    }
    return 0;
}

#endif