#ifndef STRUCTHOTEL_H
#define STRUCTHOTEL_H
#include <stdio.h>

// ================== STRUKTUR DATA DUMMY ==================
typedef enum {
    TAMU,
    KARYAWAN,
    MANAGER,
    BELUM_LOGIN // Digunakan untuk halaman awal
} UserRole;

extern char activeUsername[30];

typedef struct {
    char username[30];
    char password[30];
    UserRole role;
    char nama_lengkap[50];
} User;

// ================== DATA DUMMY (USER) ==================
User daftarUser[] = {
    {"guest1", "guest", TAMU, "Andi Tamu"},
    {"admin", "hotel123", KARYAWAN, "Budi Karyawan"},
    {"manager", "manager123", MANAGER, "Citra Manajer"}
};
#define JML_USER (sizeof(daftarUser) / sizeof(User))

typedef struct {
    int no;
    char tipe[20]; // Single, Double, Deluxe, Suite
    float Harga;
    int status;     // 0= Tersedia, 1 =  Tidak Tersedia
    char created_by[20];
    char created_date[20];
    char modified_by[20];
    char modified_date[20];
} Kamar; 

typedef struct {
    char tipe_kamar[15];
    int jumlah_kamar;
    char ukuran_kasur[20]; 
    int kapasitas_kamar;
    char created_by[20];
    char created_date[20];
    char modified_by[20];
    char modified_date[20];
    
}tipe_kamar;

typedef struct {
    char no_booking[15];
    char no_kamar[10];
    char nama_tamu[50];
    char no_telp[15];
    char tgl_checkin[15];
    char tgl_checkout[15];
} Booking;

typedef struct {
    char id_sewa[15];
    char nama_venue[30];
    char status_sewa[15]; // Scheduled, Done, Cancelled
    char tgl_acara[15];
} SewaVenue;

typedef struct {
    char nama_venue[30];
    char tipe_venue[20]; // Meeting Room, Ball Room, Garden
    char status[15];     // Available, Unavailable
} Venue;

// ================== DATA DUMMY ==================

// Data Kamar

// Data Booking
Booking daftarBooking[] = {
    {"BKG001", "A102", "Budi Santoso", "081234567890", "2025-12-01", "2025-12-03"},
    {"BKG002", "C301", "Ani Kurnia", "085555444333", "2025-12-05", "2025-12-07"}
};
#define JML_BOOKING (sizeof(daftarBooking) / sizeof(Booking))

//data venue
Venue daftarVenue[] = {
    {"Ruang Anggrek", "Meeting Room", "Available"},
    {"Diamond Hall", "Ball Room", "Unavailable"},
    {"Sky Garden", "Garden", "Available"}
};
#define JML_VENUE (sizeof(daftarVenue) / sizeof(Venue))

// Data Sewa Venue
SewaVenue daftarSewaVenue[] = {
    {"32001", "Diamond Hall", "Terjadwal", "2026-01-15"},
    {"32002", "Ruang Anggrek", "Done", "2025-11-20"},
    {"003", "Sky Garden", "Ongoing", "2026-03-01"}
};
#define JML_SEWA (sizeof(daftarSewaVenue) / sizeof(SewaVenue))

#endif