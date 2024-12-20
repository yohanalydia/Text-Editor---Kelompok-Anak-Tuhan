#include "COTYPE.h"

int main(){
    adrKata kataPertama;
    adrBaris B;
    adrHuruf cursor = nullptr;

    Line = createBaris();
    B = createElemBaris();
    Line.first = B;
    Line.last = B;
    kataPertama = createElemKata();
    B->firstKata = kataPertama;
    B->lastKata = kataPertama;

    cursor = createElemHuruf('|');
    kataPertama->firstHuruf = cursor;
    kataPertama->lastHuruf = cursor;
    activeBaris = Line.first;
    activeKata = kataPertama;

    Clipboard = createElemBaris();
    adrKata tempKata = createElemKata();
    Clipboard->firstKata = tempKata;
    Clipboard->lastKata = tempKata;

    undoStack = createStack();
    redoStack = createStack();
    insertElementStack(undoStack);
    Opening();
    char ch;
    while (1) {
        if (_kbhit()) {  // memeriksa apakah tombol sudah ditekan
            ch = _getch();  // membaca karakter tanpa menunggu Enter

            if (ch == 27) {  // kondisi jika ESC ditekan
                break;  // keluar dari loop jika ESC ditekan
            } else {
                if (ch == 19 || ch == 9){
                    system("cls");
                }
                if (ch == 32 || ch == 13){
                    insertElementStack(undoStack);
                    clearStack(redoStack);
                }
                inputHandler(cursor, ch);  // menangani input selain ESC
            }
            // clear layar dan menampilkan teks yang diperbarui
            system("cls");
            cout << "+===================================================+" << endl;
            cout << "|                TEXT EDITOR COTYPE--               |" << endl;
            cout << "+===================================================+" << endl;
            displayKata();

            keteranganText();
            setColor(7,0);
        }
    }
    system("cls");
    cout << "+===================================================+" << endl;
    cout << "|           TERIMA KASIH TELAH MENGGUNAKAN          |" << endl;
    cout << "|                TEXT EDITOR COTYPE--               |" << endl;
    cout << "|                        ^^                         |" << endl;
    cout << "+===================================================+" << endl;

    return 0;
}
