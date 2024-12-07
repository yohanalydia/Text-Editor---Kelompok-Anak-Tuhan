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
    B -> firstKata = kataPertama;
    B -> lastKata = kataPertama;

    cursor = createElemHuruf('|');
    kataPertama->firstHuruf = cursor;
    kataPertama->lastHuruf = cursor;
    activeBaris = Line.first;
    activeKata = kataPertama;

    char ch;
    while (1) {
        if (_kbhit()) {  // memeriksa apakah tombol sudah ditekan
            ch = _getch();  // membaca karakter tanpa menunggu Enter

            if (ch == 27) {  // kondisi jika ESC ditekan
                break;  // keluar dari loop jika ESC ditekan
            } else {
                inputHandler(cursor, ch);  // menangani input selain ESC
            }

            // clear layar dan menampilkan teks yang diperbarui
            system("cls");
            cout << "Teks: " << endl;
            displayKata();
            cout << "--------" <<endl;
            cout << "activeKata firstHuruf: " << activeKata -> firstHuruf -> info << endl;
            cout << "activeKata lastHuruf: " << activeKata -> lastHuruf -> info << endl;
        }
    }
    keteranganText();
}
