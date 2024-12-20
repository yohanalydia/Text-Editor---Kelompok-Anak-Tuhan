#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>

// library conio.h menyediakan fungsi untuk input/output berbasis karakter
#include <conio.h>
// library windows.h menyediakan fungsi untuk berinteraksi dengan sistem operasi windows
#include <windows.h>
// library cstdlib menyediakan fungsi untuk operasi umum seperti eksekusi perintah sistem
#include <cstdlib>

// library untuk fungsi Search
#include <vector>
#include <string>

using namespace std;

// Mendeklarasikan pointer ke struct elmHuruf, elmKata, dan elmBaris
typedef struct elmHuruf * adrHuruf;
typedef struct elmKata * adrKata;
typedef struct elmBaris * adrBaris;

// Membuat struct elmHuruf
struct elmHuruf{
    char info; // Menyimpan karakter ke elmHuruf
    adrHuruf next, prev; // Menyimpan pointer ke huruf berikutnya dan sebelumnya
};

// Membuat struct elmKata
struct elmKata{
    adrKata next, prev; // Menyimpan pointer ke kata berikutnya dan sebelumnya
    adrHuruf firstHuruf, lastHuruf; // Menyimpan pointer yang menunjuk ke huruf pertama dan terakhir dalam elmKata
};

// Membuat struct elmBaris
struct elmBaris{
    adrBaris next, prev; // Menyimpan pointer ke baris berikutnya dan sebelumnya
    adrKata firstKata, lastKata; // Menyimpan pointer yang menunjuk ke kata pertama dan kata terakhir dalam baris
};

// Membuat struct Baris
struct Baris{
    adrBaris first, last; // Menyimpan pointer baris pertama dan terakhir
};

// Membuat struct Stack
struct Stack{
    Baris info[10];
    int top;
};

// Mendeklarasikan fungsi primitives Stack
Stack createStack();
bool isFull(Stack S);
bool isEmpty(Stack S);
void push(Stack &S, Baris B);
void pop(Stack &S, Baris &outBaris);
void clearStack(Stack &S);

// Mendeklarasikan variabel global activeKata
extern adrKata activeKata;
// Mendeklarasikan variabel global activeBaris
extern adrBaris activeBaris;
// Mendeklarasikan variabel global Line
extern Baris Line;
// Mendeklarasikan variabel global Clipboard
extern adrBaris Clipboard;
// Mendeklarasikan variabel global listKata yang merupakan vector (array dinamis)
extern vector<adrKata> listKata;
// Mendeklarasikan variabel global undoStack dan redoStack
extern Stack undoStack;
extern Stack redoStack;

// Mendeklarasikan prosedur untuk menampilkan halaman pembuka pada COTYPE--
void Opening();
// Mendeklarasikan prosedur untuk menampilkan List Shortcut yang dapat digunakan
void Menu();

// Mendeklarasikan primitives create
Baris createBaris();
adrBaris createElemBaris();
adrKata createElemKata();
adrHuruf createElemHuruf(char x);

// Mendeklarasikan prosedur input
void inputHandler(adrHuruf &cursor, char x);
void inputSpace(adrHuruf &cursor, char x);
void inputEnter(adrHuruf &cursor);

// Mendeklarasikan prosedur terkait insert dan delete huruf
void inputHuruf(adrHuruf &cursor, char);
void insertFirstHuruf(adrHuruf inHuruf);
void insertAfterHuruf(adrHuruf inHuruf, adrHuruf prec);
void insertLastHuruf(adrHuruf inHuruf);
void deleteHuruf(adrHuruf &cursor, adrHuruf &outHuruf);
void deleteFirstHuruf(adrHuruf &outHuruf);
void deleteAfterHuruf(adrHuruf &outHuruf, adrHuruf prec);
void deleteLastHuruf(adrHuruf &outHuruf);

// Mendeklarasikan prosedur terkait insert dan delete kata
void inputKata(adrKata inKata);
void insertFirstKata(adrKata inKata);
void insertAfterKata(adrKata inKata, adrKata prec);
void insertLastKata(adrKata inKata);
void deleteKata(adrHuruf &cursor, adrKata &outKata);
void deleteFirstKata(adrKata &outKata);
void deleteAfterKata(adrKata &outKata, adrKata prec);
void deleteLastKata(adrKata &outKata);

// Mendeklarasikan prosedur terkait insert dan delete baris
void inputBaris(adrBaris inBaris);
void insertFirstBaris(adrBaris inBaris);
void insertAfterBaris(adrBaris inBaris, adrBaris prec);
void insertLastBaris(adrBaris inBaris);
void deleteBaris(adrHuruf &cursor, adrBaris &outBaris);
void deleteFirstBaris(adrBaris &outBaris);
void deleteAfterBaris(adrBaris &outBaris, adrBaris prec);
void deleteLastBaris(adrBaris &outBaris);

// Mendeklarasikan prosedur untuk memindahkan kursor
void moveCursorToLeft(adrHuruf &cursor);
void moveCursorToRight(adrHuruf &cursor);
void moveCursorUp(adrHuruf &cursor);
void moveCursorDown(adrHuruf &cursor);

// Mendeklarasikan prosedur untuk mengubah karakter yang telah dipilih menjadi huruf kapital
void characterToUppercase(adrHuruf cursor, int jumlahSelect);
// Mendeklarasikan prosedur untuk mengubah karakter yang telah dipilih menjadi huruf kecil
void characterToLowercase(adrHuruf cursor, int jumlahSelect);

//Mendeklarasikan prosedur untuk menyeleksi karakter pada baris yang aktif
void selectHuruf(adrHuruf cursor, int &jumlahSelect);
// Mendeklarasikan prosedur untuk menyalin karakter yang sudah diseleksi
void copyHuruf(adrHuruf cursor, int jumlahSelect);
// Mendeklarasikan prosedur untuk menempelkan (paste) karakter yang sudah dicopy ke clipboard
void pasteHuruf(adrBaris Clipboard, adrHuruf &cursor);
// Mendeklarasikan prosedur untuk memotong karakter yang sudah diseleksi
void cutHuruf(adrHuruf &cursor, int jumlahSelect);
// Mendeklarasikan prosedur untuk mencari kata yang diinput oleh user
void searchWord();

// Mendeklarasikan prosedur untuk menampilkan keterangan dari keseluruhan teks
void keteranganText();
// Mendeklarasikan prosedur untuk menampilkan keseluruhan teks
void displayKata();
// Mendeklarasikan prosedur untuk mengubah warna teks dan latar belakang teks
void setColor(int textColor, int bgColor);
// Mendeklarasikan prosedur untuk menampilkan sebuah kata pada seluruh teks
void printKata(adrKata inKata);
// Mendeklarasikan prosedur untuk menghitung jumlah huruf pada sebuah kata
int lengthKata(adrKata inKata);
// Mendeklarasikan prosedur untuk mengganti kata setelah di search dengan suatu kata spesifik
void replaceWord(adrHuruf &cursor);

// Mendeklarasikan prosedur untuk membatalkan perubahan yang telah dilakukan sebelumnya
void undo(adrHuruf &cursor);
// Mendeklarasikan prosedur untuk mengembalikan perubahan yang telah dibatalkan oleh prosedur undo
void redo(adrHuruf &cursor);

// Mendeklarasikan prosedur untuk memasukkan elemen ke dalam Stack
void insertElementStack(Stack &S);
#endif // TUBES_H_INCLUDED
