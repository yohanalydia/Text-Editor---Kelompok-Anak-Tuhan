#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <conio.h>
// library conio.h digunakan untuk manipulasi terminal
#include <windows.h>
#include <cstdlib>
#include <iostream>

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

// Mendeklarasikan variabel global activeKata
extern adrKata activeKata;
// Mendeklarasikan variabel global activeBaris
extern adrBaris activeBaris;
// Mendeklarasikan variabel global Line
extern Baris Line;

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
void inputHuruf(adrHuruf &cursor, char x);
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

// Mendeklarasikan prosedur untuk menampilkan keterangan dari keseluruhan teks
void keteranganText();
// Mendeklarasikan prosedur untuk menampilkan keseluruhan teks
void displayKata();
void setColor(int textColor, int bgColor);



#endif // TUBES_H_INCLUDED
