#include "COTYPE.h"

// Mendefinisikan variabel global
adrKata activeKata = nullptr;
adrBaris activeBaris = nullptr;
Baris Line = {nullptr, nullptr};
adrBaris Clipboard = nullptr;
vector<adrKata> listKata;
Stack undoStack;
Stack redoStack;


void Opening(){
// {Menampilkan halaman pembuka text editor.}
    cout << "+===================================================+" << endl;
    cout << "|             SELAMAT DATANG DI COTYPE--            |" << endl;
    cout << "| Silakan tekan Ctrl + I untuk memulai Text Editor. |" << endl;
    cout << "+===================================================+" << endl;
    cout << "| Creator: Julian Sudiyanto (103052300045)          |" << endl;
    cout << "|          Yohana Lydia (103052330068)              |" << endl;
    cout << "+===================================================+" << endl;
}

void Menu(){
//{Menampilkan List Shortcut yang dapat digunakan di dalam Text Editor.}
    string input;
    cout << "+=======================================+" << endl;
    cout << "|        DAFTAR SHORTCUT COTYPE--       |" << endl;
    cout << "+=======================================+" << endl;
    cout << "| 1. Delete: Backspace                  |" << endl;
    cout << "| 2. Move Cursor: Arrow                 |" << endl;
    cout << "| 3. Select: Ctrl + S                   |" << endl;
    cout << "| 4. Uppercase: Ctrl + U                |" << endl;
    cout << "| 5. Lowercase: Ctrl + L                |" << endl;
    cout << "| 6. Copy: Ctrl + C                     |" << endl;
    cout << "| 7. Cut: Ctrl + X                      |" << endl;
    cout << "| 8. Paste: Ctrl + P                    |" << endl;
    cout << "| 9. Search Word: Ctrl + E              |" << endl;
    cout << "| 10. Replace Word: Ctrl + R            |" << endl;
    cout << "| 11. Undo: Ctrl + Z                    |" << endl;
    cout << "| 12. Redo: Ctrl + Y                    |" << endl;
    cout << "| 13. Show Instruction: Ctrl + I        |" << endl;
    cout << "|                                       |" << endl;
    cout << "| Note:                                 |" << endl;
    cout << "| - Shortcut nomor 4, 5, 6, dan 7 hanya |" << endl;
    cout << "|   dapat digunakan setelah Select.     |" << endl;
    cout << "| - Shortcut nomor 8 hanya dapat        |" << endl;
    cout << "|   digunakan setelah Copy atau Cut.    |" << endl;
    cout << "| - Shortcut nomor 10 hanya dapat       |" << endl;
    cout << "|   digunakan setelah Search.           |" << endl;
    cout << "+=======================================+" << endl;
    cout << "Ketik START untuk memulai: ";
    cin >> input;
    if (input != "START"){
        system("cls");
        Menu();
    }
}

Baris createBaris(){
//{Mengembalikan sebuah baris dengan first dan last diinisialisasi sebagai NIL.}
    Baris P;
    P.first = nullptr;
    P.last = nullptr;

    return P;

}

adrBaris createElemBaris(){
//{Mengembalikan sebuah elemen baris dengan next, prev, firstKata, dan lastKata diinisialisasi sebagai NIL.}
    adrBaris P;
    P = new elmBaris;
    P -> next = nullptr;
    P -> prev = nullptr;
    P -> firstKata = nullptr;
    P -> lastKata = nullptr;

    return P;
}

adrKata createElemKata(){
//{Mengembalikan sebuah elemen kata dengan next, prev, firstHuruf, dan lastHuruf diinisialisasi sebagai NIL.}
    adrKata P;
    P = new elmKata;
    P -> next = nullptr;
    P -> prev = nullptr;
    P -> firstHuruf = nullptr;
    P -> lastHuruf = nullptr;

    return P;
}

adrHuruf createElemHuruf(char x){
//{Mengembalikan sebuah elemen huruf dengan next dan prev diinisialisasi sebagai NIL, serta nilai info sesuai dengan parameter x.}
    adrHuruf P;
    P = new elmHuruf;
    P -> next = nullptr;
    P -> prev = nullptr;
    P -> info = x;

    return P;
}

void deleteCursor(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S elemen kursor keluar dari list tetapi tetap ditunjuk oleh pointer kursor.}
    if (cursor == activeKata->firstHuruf){
        deleteFirstHuruf(cursor);
    }else if (cursor == activeKata->lastHuruf){
        deleteLastHuruf(cursor);
    }else{
        deleteAfterHuruf(cursor, cursor->prev);
    }
}

void moveCursorToRight(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S elemen kursor keluar pindah ke sebelah kanan posisi awal.}
    adrHuruf prec;
    if (cursor == activeKata -> lastHuruf && activeKata->next == nullptr){ // kondisi kursor di akhir kata dan di akhir baris
        if (activeBaris->next != nullptr){
            deleteCursor(cursor);
            activeBaris = activeBaris->next;
            activeKata = activeBaris->firstKata;
            insertFirstHuruf(cursor);
        }
    }else if (cursor == activeKata -> lastHuruf){ // kondisi kursor di akhir kata dan terdapat kata selanjutnya
        deleteCursor(cursor);
        activeKata = activeKata -> next;
        insertAfterHuruf(cursor, activeKata -> firstHuruf);
    }else { // kondisi terdapat huruf setelah kursor
        prec = cursor->next;
        deleteCursor(cursor);
        insertAfterHuruf(cursor, prec);
    }
}

void moveCursorToLeft(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S elemen kursor keluar pindah ke sebelah kiri posisi awal.}
    adrHuruf prec;
    if (cursor == activeKata -> firstHuruf && activeKata->prev== nullptr){ // kondisi kursor di awal kata dan di awal baris
        if (activeBaris->prev != nullptr){
            deleteCursor(cursor);
            activeBaris = activeBaris->prev;
            activeKata = activeBaris->lastKata;
            insertLastHuruf(cursor);
        }
    }else if (cursor -> prev == activeKata -> firstHuruf){ // kondisi kursor berada di setelah huruf pertama
        if (activeKata == activeBaris -> firstKata){ // kondisi active kata merupakan kata pertama pada baris
            deleteCursor(cursor);
            insertFirstHuruf(cursor);
        }else{  // kondisi terdapat kata sebelum active kata
            deleteCursor(cursor);
            activeKata = activeKata -> prev;
            insertLastHuruf(cursor);
        }

    }else{ // kondisi terdapat huruf sebelum kursor
        prec = cursor->prev;
        deleteCursor(cursor);
        insertAfterHuruf(cursor, prec -> prev);
    }
}

void moveCursorUp(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S elemen kursor pindah ke posisi yang sama di baris atasnya atau posisi terakhir jika jumlah huruf di baris atasnya lebih sedikit.}

    if(activeBaris != Line.first){
        bool found = false;
        int jumlahHuruf = 0;
        adrKata counterKata;
        adrHuruf counterHuruf;

        counterKata = activeBaris -> firstKata;

        while (counterKata != nullptr && !found){
            counterHuruf = counterKata -> firstHuruf;
            while (counterHuruf != nullptr && counterHuruf -> info !='|'){
                jumlahHuruf++;
                counterHuruf = counterHuruf -> next;
            }
            if (counterHuruf == nullptr){
                counterKata = counterKata -> next;
            }else if (counterHuruf->info == '|'){
                found = true;
            }
        }
        deleteCursor(cursor);

        activeBaris = activeBaris -> prev;
        activeKata = activeBaris->firstKata;
        insertFirstHuruf(cursor);

        int i = 1;
        while (i<=jumlahHuruf && cursor != activeBaris->lastKata->lastHuruf){
            moveCursorToRight(cursor);
            i++;
        }
    }
}

void moveCursorDown(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S elemen kursor pindah ke posisi yang sama di baris bawahnya atau posisi terakhir jika jumlah huruf di baris bawahnya lebih sedikit.}
    if (activeBaris != Line.last){
        bool found = false;
        int jumlahHuruf = 0;
        adrKata counterKata;
        adrHuruf counterHuruf;

        counterKata = activeBaris -> firstKata;

        while (counterKata != nullptr && !found){
            counterHuruf = counterKata -> firstHuruf;
            while (counterHuruf != nullptr && counterHuruf -> info !='|'){
                jumlahHuruf++;
                counterHuruf = counterHuruf -> next;
            }
            if (counterHuruf == nullptr){
                counterKata = counterKata -> next;
            }else if (counterHuruf->info == '|'){
                found = true;
            }
        }
        deleteCursor(cursor);

        activeBaris = activeBaris -> next;
        activeKata = activeBaris->firstKata;
        insertFirstHuruf(cursor);

        int i = 1;
        while (i<=jumlahHuruf && cursor != activeBaris->lastKata->lastHuruf){
            moveCursorToRight(cursor);
            i++;
        }
    }
}

void inputHandler(adrHuruf &cursor, char x){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong dan karakter input x
// F.S karakter input ditangani sesuai kondisinya.}
    adrHuruf outHuruf;
    int jumlahSelect;
    string kataCari;

    if (x == 32){ // kondisi karakter yang diinput adalah space
        inputSpace(cursor, x);
    }else if (x == 13){ // kondisi karakter yang diinput adalah enter
        inputEnter(cursor);
    }else if (x == 8) { // kondisi karakter yang diinput adalah backspace
        insertElementStack(undoStack);
        clearStack(redoStack);
        deleteHuruf(cursor, outHuruf);
    }else if (x == 19) { // kondisi karakter yang diinput adalah Ctrl + S
        selectHuruf(cursor, jumlahSelect);
        keteranganText();
        setColor(7,0);

        x = _getch();
        system("cls");
        if (x == 3){ // kondisi karakter yang diinput adalah Ctrl + C
            copyHuruf(cursor, jumlahSelect);
        }else if (x == 12){ // kondisi karakter yang diinput adalah Ctrl + L
            insertElementStack(undoStack);
            clearStack(redoStack);
            characterToLowercase(cursor, jumlahSelect);
        }else if (x == 21){ // kondisi karakter yang diinput adalah Ctrl + U
            insertElementStack(undoStack);
            clearStack(redoStack);
            characterToUppercase(cursor, jumlahSelect);
        }else if (x == 24){ // kondisi karakter yang diinput adalah Ctrl + X
            insertElementStack(undoStack);
            clearStack(redoStack);
            cutHuruf(cursor, jumlahSelect);
        }else{
            inputHandler(cursor, x);
        }
    }else if (x == 16){ // kondisi karakter yang diinput adalah Ctrl + P
        insertElementStack(undoStack);
        clearStack(redoStack);
        pasteHuruf(Clipboard, cursor);
    }else if (x == 0 || x == -32){ // kondisi karakter yang diinput adalah arrow
        x = _getch();
        if (x == 75){ // kondisi karakter yang diinput adalah arrow left
            moveCursorToLeft(cursor);
        }else if (x == 77){ // kondisi karakter yang diinput adalah arrow right
            moveCursorToRight(cursor);
        }else if (x == 72){ // kondisi karakter yang diinput adalah arrow up
            moveCursorUp(cursor);
        }else if (x == 80){ // kondisi karakter yang diinput adalah arrow down
            moveCursorDown(cursor);
        }
    }else if (x == 5){ // kondisi karakter yang diinput adalah Ctrl + E
        string kataReplace;
        searchWord();
        keteranganText();
        setColor(7,0);

        x = _getch();
        if(x == 18){ // kondisi karakter yang diinput adalah Ctrl + R
            insertElementStack(undoStack);
            clearStack(redoStack);
            replaceWord(cursor);
            listKata.clear();
        }else{
            listKata.clear();
            inputHandler(cursor,x);
        }
    }else if (x == 9){ // kondisi karakter yang diinput adalah Ctrl + I
        Menu();
    }else if (x == 25){ // kondisi karakter yang diinput adalah Ctrl + Y
        redo(cursor);
    }else if (x == 26){ // kondisi karakter yang diinput adalah Ctrl + Z
        undo(cursor);
    }else if (x != 3 && x != 12 && x != 21 && x != 18 && x != 24){ // kondisi karakter yang diinput adalah huruf, angka, dan simbol
        inputHuruf(cursor, x);
    }
}

void inputSpace(adrHuruf &cursor, char x){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S karakter input ' ' membuat elemen kata baru dan kursor ditempatkan setelah karakter ' '.}
    adrHuruf inHuruf = createElemHuruf(x);
    if (cursor == activeBaris -> firstKata -> firstHuruf){ // kondisi kursor merupakan elemen pertama dalam kata dan baris
        insertFirstHuruf(inHuruf);
    }else if (cursor->next == nullptr){ // kondisi tidak ada huruf setelah kursor
        deleteCursor(cursor);
        adrKata newSpace;
        newSpace = createElemKata();
        inputKata(newSpace);
        insertFirstHuruf(inHuruf);
        insertAfterHuruf(cursor, activeKata -> firstHuruf);

    }else{ // kondisi terdapat huruf setelah kursor
        adrHuruf tempFirst, tempLast;
        tempLast = activeKata->lastHuruf;
        tempFirst = cursor -> next;
        deleteCursor(cursor);
        activeKata ->lastHuruf = tempFirst->prev;
        activeKata -> lastHuruf -> next = nullptr;
        tempFirst -> prev = nullptr;


        adrKata newSpace;
        newSpace = createElemKata();
        inputKata(newSpace);
        insertFirstHuruf(inHuruf);
        insertAfterHuruf(cursor, activeKata -> firstHuruf);

        adrKata newKata;
        newKata = createElemKata();
        inputKata(newKata);
        activeKata->firstHuruf = tempFirst;
        activeKata->lastHuruf = tempLast;
        activeKata = activeKata -> prev;
    }
}

void inputEnter(adrHuruf &cursor){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong.
// F.S sebuah baris baru dibuat sesuai kondisi kursor.}
    if (cursor == activeBaris -> firstKata -> firstHuruf){ // kondisi kursor merupakan elemen pertama dalam kata dan baris
        adrBaris newBaris = createElemBaris();
        adrKata newKata = createElemKata();
        newBaris->firstKata = newKata;
        newBaris->lastKata = newKata;
        if (Line.first == activeBaris){ // kondisi barisnya merupakan baris pertama
            insertFirstBaris(newBaris);
        }else{ // kondisi baris bukan baris pertama
            insertAfterBaris(newBaris, activeBaris->prev);
        }
    }else if (cursor == activeBaris->lastKata->lastHuruf){ // kondisi kursor merupakan elemen terakhir dalam kata dan baris
        deleteCursor(cursor);
        adrBaris newBaris = createElemBaris();
        adrKata newKata = createElemKata();
        newBaris->firstKata = newKata;
        newBaris->lastKata = newKata;
        inputBaris(newBaris);
        activeKata = newBaris->firstKata;
        insertFirstHuruf(cursor);
    }else{ // kondisi kursor berada di tengah baris
        if (cursor->next != nullptr && cursor->prev != nullptr){ // kondisi kursor berada di tengah kata
            adrHuruf tempFirst, tempLast;
            tempLast = activeKata->lastHuruf;
            tempFirst = cursor -> next;
            deleteCursor(cursor);
            activeKata ->lastHuruf = tempFirst->prev;
            activeKata -> lastHuruf -> next = nullptr;
            tempFirst -> prev = nullptr;

            adrKata newKata;
            newKata = createElemKata();
            inputKata(newKata);
            activeKata->firstHuruf = tempFirst;

            activeKata->lastHuruf = tempLast;
            activeKata = activeKata -> prev;
        }else{ // kondisi kursor tidak berada di tengah kata
            deleteCursor(cursor);
        }
        adrKata tempFirstKata = activeKata -> next;
        adrKata tempLastKata = activeBaris -> lastKata;
        activeKata -> next = nullptr;
        tempFirstKata -> prev = nullptr;
        activeBaris -> lastKata = activeKata;
        adrBaris newBaris = createElemBaris();

        inputBaris(newBaris);

        activeBaris -> firstKata = tempFirstKata;
        activeBaris -> lastKata = tempLastKata;
        activeKata = activeBaris -> firstKata;
        insertFirstHuruf(cursor);
    }
}

void inputHuruf(adrHuruf &cursor, char x) {
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong dan karakter input.
// F.S karakter input masuk ke dalam elemen kata dan posisi kursor ditempatkan setelah karakter input.}
    adrHuruf inHuruf = createElemHuruf(x);

    if (cursor == activeBaris -> firstKata -> firstHuruf){ // kondisi kursor merupakan elemen pertama pada baris dan kata
        insertFirstHuruf(inHuruf);
        if (cursor->next != nullptr){
            if (cursor->next->info == ' '){
                moveCursorToRight(cursor);
                adrHuruf outHuruf;
                deleteHuruf(cursor, outHuruf);
                inputSpace(cursor, 32);
                moveCursorToLeft(cursor);
            }
        }
    }else if(activeKata -> firstHuruf -> info == ' ' && activeKata -> next == nullptr){ // kondisi kursor berada setelah space dan tidak ada kata selanjutnya
        deleteCursor(cursor);
        adrKata newKata;
        newKata = createElemKata();
        inputKata(newKata);
        insertFirstHuruf(cursor);
        insertFirstHuruf(inHuruf);
    }else if (activeKata -> firstHuruf -> info == ' ' && activeKata -> next != nullptr) { // kondisi kursor berada setelah space dan terdapat kata selanjutnya
        if (activeKata -> next -> firstHuruf -> info == ' '){ // kondisi kata selanjutnya adalah ' '
            adrKata newKata;
            newKata = createElemKata();
            deleteCursor(cursor);
            inputKata(newKata);
            insertFirstHuruf(cursor);
            insertFirstHuruf(inHuruf);
        }else{ // kondisi kata selanjutnya bukan ' '
            deleteCursor(cursor);
            activeKata = activeKata -> next;
            insertFirstHuruf(inHuruf);
            insertAfterHuruf(cursor, activeKata -> firstHuruf);
        }
    }else{ // kondisi lainnya
        insertAfterHuruf(inHuruf, cursor->prev);
    }
}

void insertFirstHuruf(adrHuruf inHuruf){
//{I.S terdefinisi sebuah elemen huruf yang mungkin kosong.
// F.S elemen huruf ditempatkan di awal kata dan activeKata->firstHuruf menunjuk ke elemen huruf.}
    if (activeKata -> firstHuruf == nullptr){
        activeKata -> firstHuruf = inHuruf;
        activeKata -> lastHuruf = inHuruf;
    }else{
        inHuruf -> next = activeKata-> firstHuruf;
        activeKata -> firstHuruf -> prev = inHuruf;
        activeKata -> firstHuruf = inHuruf;
    }
}

void insertAfterHuruf(adrHuruf inHuruf, adrHuruf prec){
//{I.S terdefinisi sebuah elemen huruf dan prec yang mungkin kosong.
// F.S elemen huruf ditempatkan setelah elemen prec}
    if (prec != nullptr){
        if (prec -> next == nullptr){
            insertLastHuruf(inHuruf);
        }else{
            inHuruf -> next = prec -> next;
            prec -> next -> prev = inHuruf;
            inHuruf -> prev = prec;
            prec -> next = inHuruf;
        }
    }
}

void insertLastHuruf(adrHuruf inHuruf) {
//{I.S terdefinisi sebuah elemen huruf yang mungkin kosong.
// F.S elemen huruf ditempatkan di akhir kata dan activeKata->lastHuruf menunjuk ke elemen huruf.}
    if (activeKata->firstHuruf == nullptr) {
        activeKata->firstHuruf = inHuruf;
        activeKata->lastHuruf = inHuruf;
    } else {
        activeKata->lastHuruf->next = inHuruf;
        inHuruf->prev = activeKata->lastHuruf;
        activeKata->lastHuruf = inHuruf;
    }
}

void deleteHuruf(adrHuruf &cursor, adrHuruf &outHuruf){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong
// F.S menghapus karakter sesuai dengan kondisi kursor.}
    if (cursor->prev == activeKata->firstHuruf && cursor == activeKata->lastHuruf){ // kondisi elemen sebelum kursor adalah elemen pertama dan kursor merupakan elemen terakhir dalam kata
        deleteFirstHuruf(outHuruf);
        if (activeKata->prev != nullptr){ // kondisi active kata bukan merupakan kata pertama dalam baris
            deleteCursor(cursor);
            adrKata outKata;
            if (activeKata -> next == nullptr){ // kondisi active kata merupakan kata terakhir dalam baris
                deleteLastKata(outKata);
                insertLastHuruf(cursor);
            }else{ // kondisi terdapat kata setelah active kata
                if (outHuruf->info == ' ' && activeKata->next->firstHuruf->info != ' '){ // kondisi huruf yang dihapus adalah ' ' dan setelahnya terdapat kata ' '
                    activeKata = activeKata->prev;
                    insertLastHuruf(cursor);
                    adrKata outKata;
                    deleteAfterKata(outKata, activeKata);

                    adrKata nextKata;
                    nextKata = activeKata->next;
                    activeKata->lastHuruf->next = nextKata->firstHuruf;
                    nextKata->firstHuruf->prev = activeKata->lastHuruf;
                    activeKata->lastHuruf = nextKata->lastHuruf;

                    if (nextKata->next == nullptr){ // kondisi nextKata merupakan kata terakhir
                        activeKata->next = nullptr;
                        activeBaris->lastKata = activeKata;
                    }else{ // kondisi nextKata bukan kata terakhir
                        activeKata->next = nextKata->next;
                        nextKata->next->prev = activeKata;
                    }
                    nextKata->firstHuruf = nullptr;
                    nextKata->lastHuruf = nullptr;
                    nextKata->prev = nullptr;
                    nextKata->next = nullptr;
                    delete(nextKata);
                }else{ // kondisi lainnya
                    activeKata = activeKata->prev;
                    insertLastHuruf(cursor);
                    adrKata outKata;
                    deleteAfterKata(outKata, activeKata);
                }
            }
        }else{ // kondisi active kata merupakan kata pertama dalam baris
            if (activeKata->next != nullptr){
                adrKata outKata;
                deleteCursor(cursor);
                deleteFirstKata(outKata);
                insertFirstHuruf(cursor);
            }
        }
    }else if (cursor->prev == activeKata->firstHuruf){ // kondisi huruf sebelum kursor adalah huruf pertama dalam kata
        deleteFirstHuruf(outHuruf);
        if (activeKata->prev != nullptr){
            deleteCursor(cursor);
            activeKata = activeKata->prev;
            insertLastHuruf(cursor);
        }
    }else if (cursor == activeKata->firstHuruf && activeKata == activeBaris->firstKata){ // kondisi kursor sebagai elemen pertama kata dan activeKata adalah kata pertama dalam baris
        if (cursor == activeKata->lastHuruf){ // kondisi dalam baris hanya terdapat kursor
            if (activeBaris->prev != nullptr){
                adrBaris outBaris;
                deleteCursor(cursor);
                activeBaris = activeBaris->prev;
                activeKata = activeBaris->lastKata;
                insertLastHuruf(cursor);
                activeBaris = activeBaris->next;
                if (activeBaris == Line.last){ // kondisi baris merupakan baris terakhir dalam list line
                    deleteLastBaris(outBaris);
                }else{
                    activeBaris = activeBaris->prev;
                    deleteAfterBaris(outBaris, activeBaris);
                }
            }
        }else if (cursor->next->info == ' ' && activeBaris != Line.first){ // kondisi setelah kursor terdapat ' '
            adrBaris outBaris;
            deleteCursor(cursor);
            adrKata tempFirstKata, tempLastKata;
            tempFirstKata = activeKata;
            tempLastKata = activeBaris->lastKata;
            activeBaris = activeBaris->prev;
            activeKata = activeBaris->lastKata;
            insertLastHuruf(cursor);
            activeKata->next = tempFirstKata;
            tempFirstKata->prev = activeKata;
            activeBaris->lastKata = tempLastKata;
            activeBaris = activeBaris->next;
            if (activeBaris == Line.last){ // kondisi baris merupakan baris terakhir dalam list line
                deleteLastBaris(outBaris);
            }else{
                activeBaris = activeBaris->prev;
                deleteAfterBaris(outBaris, activeBaris);
            }
        }else if (activeBaris != Line.first){ // kondisi lainnya
            adrBaris outBaris;
            deleteCursor(cursor);
            adrKata tempFirstKata, tempLastKata;
            tempFirstKata = activeKata;
            tempLastKata = activeBaris->lastKata;
            activeBaris = activeBaris->prev;
            activeKata = activeBaris->lastKata;
            insertLastHuruf(cursor);

            activeKata->lastHuruf->next = tempFirstKata->firstHuruf;
            tempFirstKata->firstHuruf->prev = activeKata->lastHuruf;

            activeKata->lastHuruf = tempFirstKata->lastHuruf;
            activeKata->next = tempFirstKata->next;
            tempFirstKata = tempFirstKata->next;
            if(tempFirstKata != nullptr){
                tempFirstKata->prev = activeKata;
                activeBaris->lastKata = tempLastKata;
            }
            activeBaris = activeBaris->next;
            if (activeBaris == Line.last){ // kondisi baris merupakan baris terakhir dalam list line
                deleteLastBaris(outBaris);
            }else{
                activeBaris = activeBaris->prev;
                deleteAfterBaris(outBaris, activeBaris);
            }
        }
    }else{ // kondisi lainnya
        adrHuruf prec;
        prec = cursor->prev;
        deleteAfterHuruf(outHuruf, prec->prev);
    }
}

void deleteFirstHuruf(adrHuruf &outHuruf){
//{menghapus elemen huruf pertama dari active kata.}
    if (activeKata->firstHuruf != nullptr){
        outHuruf = activeKata -> firstHuruf;
        if (activeKata -> firstHuruf == activeKata -> lastHuruf){
            activeKata -> firstHuruf = nullptr;
            activeKata -> lastHuruf = nullptr;
        }else{
            activeKata -> firstHuruf = activeKata -> firstHuruf -> next;
            outHuruf -> next = nullptr;
            activeKata -> firstHuruf -> prev = nullptr;
        }
    }
}

void deleteAfterHuruf(adrHuruf &outHuruf, adrHuruf prec){
//{menghapus elemen huruf setelah prec dari active kata.}
    if (prec != nullptr){
        outHuruf = prec -> next;
        prec -> next = outHuruf -> next;
        prec -> next -> prev = prec;
        outHuruf -> prev = nullptr;
        outHuruf -> next = nullptr;
    }
}

void deleteLastHuruf(adrHuruf &outHuruf){
//{menghapus elemen huruf terakhir dari active kata.}
    if (activeKata->firstHuruf != nullptr){
        outHuruf = activeKata -> lastHuruf;
        if (activeKata->firstHuruf == activeKata->lastHuruf){
            activeKata->firstHuruf = nullptr;
            activeKata->lastHuruf = nullptr;
        }else{
            activeKata -> lastHuruf = activeKata-> lastHuruf -> prev;
            activeKata -> lastHuruf -> next = nullptr;
            outHuruf -> prev = nullptr;
        }
    }
}

void inputKata(adrKata inKata){
//{I.S terdefinisi sebuah elemen kata yang tidak kosong
// F.S membuat elemen kata baru sesuai dengan kondisi.}
    if (activeBaris -> firstKata == nullptr){ // kondisi tidak terdapat kata dalam baris
        insertFirstKata(inKata);
        activeKata = activeBaris -> firstKata;
    }else if (activeKata -> next == nullptr){ // kondisi kata sekarang adalah kata terakhir dalam baris
        insertLastKata(inKata);
        activeKata = activeKata -> next;
    }else{
        insertAfterKata(inKata, activeKata);
        activeKata = activeKata -> next;
    }
}

void insertFirstKata(adrKata inKata){
//{I.S terdefinisi sebuah elemen kata yang tidak kosong
// F.S membuat elemen kata baru sebagai kata pertama pada active baris.}
    if (activeBaris -> firstKata == nullptr){
        activeBaris -> firstKata = inKata;
        activeBaris -> lastKata = inKata;
    }else{
        inKata -> next = activeBaris -> firstKata;
        activeBaris -> firstKata -> prev = inKata;
        activeBaris -> firstKata = inKata;
    }
}

void insertAfterKata(adrKata inKata, adrKata prec){
//{I.S terdefinisi sebuah elemen kata yang tidak kosong
// F.S membuat elemen kata baru setelah prec pada active baris.}
    if (prec != nullptr){
        inKata -> next = prec -> next;
        prec -> next -> prev = inKata;
        inKata -> prev = prec;
        prec -> next = inKata;
    }
}

void insertLastKata(adrKata inKata){
//{I.S terdefinisi sebuah elemen kata yang tidak kosong
// F.S membuat elemen kata baru sebagai kata terakhir pada active baris.}
    if (activeBaris -> firstKata == nullptr){
        activeBaris -> firstKata = inKata;
        activeBaris -> lastKata = inKata;
    }else{
        activeBaris -> lastKata -> next = inKata;
        inKata -> prev = activeBaris -> lastKata;
        activeBaris -> lastKata = inKata;
    }
}

void deleteKata(adrHuruf &cursor, adrKata &outKata){
//{I.S terdefinisi sebuah pointer kursor yang tidak kosong
// F.S menghapus kata sesuai dengan kondisi active kata.}
    deleteCursor(cursor);
    if (activeKata == activeBaris->firstKata){ // kondisi active kata adalah kata pertama dalam baris
        if (activeKata -> next == nullptr){
            deleteFirstKata(outKata);
            activeBaris = activeBaris->prev;
            activeKata = activeBaris->lastKata;
            insertLastHuruf(cursor);
        }else{
            deleteFirstKata(outKata);
            insertFirstHuruf(cursor);
        }
    }else if (activeKata == activeBaris ->lastKata){ // kondisi active kata adalah kata terakhir dalam baris
        deleteLastKata(outKata);
        insertLastHuruf(cursor);
    }else{
        deleteAfterKata(outKata, activeKata->prev);
        insertLastHuruf(cursor);
    }
}

void deleteFirstKata(adrKata &outKata){
//{menghapus kata pertama pada active baris.}
    if (activeKata != nullptr){
        outKata = activeKata;
        if (activeKata -> next == nullptr){
            activeBaris->firstKata = nullptr;
            activeBaris->lastKata = nullptr;
        }else{
            activeKata = activeKata->next;
            activeBaris->firstKata = activeKata;
            activeKata->prev = nullptr;
            outKata->next = nullptr;
        }
    }
}

void deleteAfterKata(adrKata &outKata, adrKata prec){
//{menghapus kata setelah prec pada active baris.}
    if (prec != nullptr){
        outKata = prec->next;
        prec->next = outKata->next;
        outKata->next->prev = prec;
        outKata->next = nullptr;
        outKata->prev = nullptr;
    }
}

void deleteLastKata(adrKata &outKata){
//{menghapus kata terakhir pada active baris.}
    if (activeKata != nullptr){
        outKata = activeKata;
        if (activeKata->prev == nullptr){
            activeBaris->firstKata = nullptr;
            activeBaris->lastKata = nullptr;
        }else{
            activeKata = activeKata->prev;
            activeKata->next = nullptr;
            outKata->prev = nullptr;
            activeBaris->lastKata = activeKata;
        }
    }
}

void inputBaris(adrBaris inBaris){
//{I.S terdefinisi sebuah elemen baris.
// F.S elemen baris dimasukkan ke List Line sesuai dengan kondisi dan active baris berpindah sesuai kondisi.}
    if (Line.first == nullptr){ // kondisi list line kosong
        insertFirstBaris(inBaris);
        activeBaris = Line.first;
    }else if (activeBaris -> next == nullptr){ // kondisi active baris merupakan elemen terakhir list line
        insertLastBaris(inBaris);
        activeBaris = activeBaris -> next;
    }else{
        insertAfterBaris(inBaris, activeBaris);
        activeBaris = activeBaris -> next;
    }
}

void insertFirstBaris(adrBaris inBaris){
//{I.S terdefinisi sebuah elemen baris.
// F.S elemen baris dimasukkan sebagai elemen pertama ke List Line.}
    if (Line.first == nullptr){
        Line.first = inBaris;
        Line.last = inBaris;
    }else{
        inBaris -> next = Line.first;
        Line.first -> prev = inBaris;
        Line.first = inBaris;
    }
}

void insertAfterBaris(adrBaris inBaris, adrBaris prec){
//{I.S terdefinisi sebuah elemen baris.
// F.S elemen baris dimasukkan setelah prec ke List Line.}
    if (prec != nullptr){
        if (prec == Line.last){
            insertLastBaris(inBaris);
        }else{
            inBaris -> next = prec -> next;
            prec -> next -> prev = inBaris;
            inBaris -> prev = prec;
            prec -> next = inBaris;
        }
    }

}

void insertLastBaris(adrBaris inBaris){
//{I.S terdefinisi sebuah elemen baris.
// F.S elemen baris dimasukkan sebagai elemen terakhir ke List Line.}
    if (Line.first == nullptr){
        Line.first = inBaris;
        Line.last = inBaris;
    }else{
        Line.last -> next = inBaris;
        inBaris -> prev = Line.last;
        Line.last = inBaris;
    }
}

void deleteBaris(adrHuruf &cursor, adrBaris &outBaris){
//{I.S terdefinisi sebuah pointer kursor.
// F.S elemen baris dihapus sesuai kondisi active baris.}
    if (Line.first != nullptr){ // kondisi list line tidak kosong
        if (activeBaris == Line.first){ // kondisi active baris adalah baris pertama dalam list line
            deleteCursor(cursor);
            deleteFirstBaris(outBaris);
            activeKata = activeBaris -> firstKata;
            insertFirstHuruf(cursor);
        }else if(activeBaris == Line.last){ // kondisi active baris adalah baris terakhir dalam list line
            deleteCursor(cursor);
            deleteLastBaris(outBaris);
            activeKata = activeBaris -> lastKata;
            insertLastHuruf(cursor);
        }else{
            deleteCursor(cursor);
            deleteAfterBaris(outBaris, activeBaris -> prev);
            activeKata = activeBaris -> lastKata;
            insertLastHuruf(cursor);
        }
    }
}

void deleteFirstBaris(adrBaris &outBaris){
//{Baris pertama pada list Line dihapus.}
    if (Line.first != Line.last){
        outBaris = Line.first;
        Line.first = Line.first->next;
        outBaris->next = nullptr;
        Line.first->prev = nullptr;
        activeBaris = Line.first;
    }
}

void deleteAfterBaris(adrBaris &outBaris, adrBaris prec){
//{Baris setelah prec pada list Line dihapus.}
    if(Line.first != nullptr && prec != nullptr){
        outBaris = prec -> next;
        prec -> next = outBaris -> next;
        outBaris -> next -> prev = prec;
        outBaris -> next = nullptr;
        outBaris -> prev = nullptr;
    }
}

void deleteLastBaris(adrBaris &outBaris){
//{Baris terakhir pada list Line dihapus.}
    if (Line.first != Line.last){
        outBaris = Line.last;
        activeBaris = activeBaris -> prev;
        activeBaris -> next = nullptr;
        outBaris -> prev = nullptr;
        Line.last = activeBaris;
    }
}

void characterToUppercase(adrHuruf cursor, int jumlahSelect){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong dan jumlah karakter yang diseleksi setelah kursor
// F.S mengubah karakter lowercase menjadi uppercase sesuai dengan jumlah karakter yang telah diseleksi.}
    adrKata counterKata;
    adrHuruf counterHuruf;
    int i = 0;
    counterKata = activeKata;
    counterHuruf = cursor->next;
    while (counterKata != nullptr && i<jumlahSelect){
        if (counterKata != activeKata){
            counterHuruf = counterKata->firstHuruf;
        }
        while (counterHuruf != nullptr && i<jumlahSelect){
            if (counterHuruf->info >= 'a' && counterHuruf->info <= 'z'){
                counterHuruf->info = counterHuruf->info - 32;
            }
            i++;
            counterHuruf = counterHuruf->next;
        }
        counterKata = counterKata->next;
    }
}

void characterToLowercase(adrHuruf cursor, int jumlahSelect){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong dan jumlah karakter yang diseleksi setelah kursor
// F.S mengubah karakter uppercase menjadi lowercase sesuai dengan jumlah karakter yang telah diseleksi.}
    adrKata counterKata;
    adrHuruf counterHuruf;
    int i = 0;

    counterKata = activeKata;
    counterHuruf = cursor->next;
    while (counterKata != nullptr && i<jumlahSelect){
        if (counterKata != activeKata){
            counterHuruf = counterKata->firstHuruf;
        }
        while (counterHuruf != nullptr && i<jumlahSelect){
            if (counterHuruf->info >= 'A' && counterHuruf->info <= 'Z'){
                counterHuruf->info = counterHuruf->info + 32;
            }
            i++;
            counterHuruf = counterHuruf->next;
        }
        counterKata = counterKata->next;
    }
}

void keteranganText(){
//{Menampilkan keseluruhan teks editor.}
    int jumlahKata = 0;
    int jumlahBaris = 0;
    int jumlahKarakter = 0;
    adrBaris tempBaris;
    adrKata tempKata;
    adrHuruf tempHuruf;

    tempBaris = Line.first;
    while(tempBaris != nullptr){
        tempKata = tempBaris ->firstKata;
        while (tempKata != nullptr){
            if (tempKata -> firstHuruf != nullptr){
                if(tempKata -> firstHuruf -> info != ' '){
                    jumlahKata++;
                }
            }
            tempHuruf = tempKata->firstHuruf;
            while (tempHuruf != nullptr){
                if (tempHuruf->info != '|'){
                    jumlahKarakter++;
                }
                tempHuruf = tempHuruf->next;
            }
            tempKata = tempKata -> next;
        }
        jumlahBaris++;
        tempBaris = tempBaris -> next;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "----------------------------"<< endl;
    cout << "Keterangan Text Editor" << endl;
    cout << "----------------------------"<< endl;
    cout << "Jumlah kata: "<< jumlahKata << endl;
    cout << "Jumlah baris: " << jumlahBaris << endl;
    cout << "Jumlah karakter: " << jumlahKarakter << endl;
}

void displayKata() {
//{Menampilkan keseluruhan isi teks editor.}
    if (Line.first == nullptr) {
        cout << "Tidak ada kata." << endl;
    }else{
        adrBaris tempLine;
        adrKata tempKata;
        adrHuruf tempHuruf;
        tempLine = Line.first;
        while (tempLine != nullptr){
            tempKata = tempLine->firstKata;
            while (tempKata != nullptr){
                tempHuruf = tempKata->firstHuruf;
                while (tempHuruf != nullptr){
                    cout << tempHuruf->info;
                    tempHuruf = tempHuruf->next;
                }
                tempKata = tempKata->next;
            }
            cout << endl;
            tempLine = tempLine->next;
        }
    }
}

void setColor(int textColor, int bgColor){
// {Mengubah warna teks dan latar belakang teks sesuai parameter.}
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,
                            (bgColor << 4) | textColor);
    // setColor(15,6) -> highlight kuning.
    // setColor(7,0) -> reset ke biasa.
}

void selectHuruf(adrHuruf cursor, int &jumlahSelect){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong
// F.S menyeleksi beberapa karakter pada baris sesuai input dari user.}
    bool start = false;
    int i = 0;

    cout << "Jumlah karakter yang ingin di Select (Setelah Cursor): ";
    cin >> jumlahSelect;
    system("cls");
    cout << "+===================================================+" << endl;
    cout << "|                TEXT EDITOR COTYPE--               |" << endl;
    cout << "+===================================================+" << endl;
    if (Line.first == nullptr) {
        cout << "Tidak ada kata." << endl;
    }else{
        adrBaris tempLine;
        adrKata tempKata;
        adrHuruf tempHuruf;
        tempLine = Line.first;
        while (tempLine != nullptr){
            tempKata = tempLine->firstKata;
            while (tempKata != nullptr){
                tempHuruf = tempKata->firstHuruf;
                while (tempHuruf != nullptr){
                    if (tempLine != activeBaris){
                        start = false;
                    }
                    if (tempHuruf -> info == '|'){
                        start = true;
                        i = 0;
                    }
                    if (i<=jumlahSelect && start){
                        if (i == 0){
                            setColor(7,0);
                        }else{
                            setColor(15,6);
                        }
                        i = i + 1;
                    }else{
                        setColor(7,0);
                    }
                    cout << tempHuruf->info;
                    tempHuruf = tempHuruf->next;
                }
                tempKata = tempKata->next;
            }
            tempLine = tempLine->next;
            if (tempLine != nullptr){
                cout << endl;
            }
        }
    }
    jumlahSelect = i-1;
    setColor(7,0);
    cout << endl;
}

void copyHuruf(adrHuruf cursor, int jumlahSelect){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong dan jumlah huruf yang di select oleh user.
// F.S menyalin beberapa karakter pada baris sesuai input dari user ke Clipboard.}
    if (jumlahSelect > 0){
        adrBaris tempActiveBaris = activeBaris;
        adrKata tempActiveKata = activeKata;
        adrKata counterKata;

        adrHuruf counterHuruf;
        int i =0;
        if (cursor->next != nullptr){
            counterHuruf = cursor -> next;
            counterKata = tempActiveKata;
        }else{
            counterHuruf = activeKata->next->firstHuruf;
            counterKata = tempActiveKata->next;
        }

        activeBaris = Clipboard;
        activeKata = Clipboard -> lastKata;

        adrHuruf tempCursor = createElemHuruf('|');
        if (Clipboard ->firstKata->firstHuruf != nullptr){
            Clipboard ->lastKata->lastHuruf -> next = tempCursor;
            tempCursor -> prev = Clipboard ->lastKata->lastHuruf;
            Clipboard ->lastKata->lastHuruf = tempCursor;
            adrHuruf outHuruf;
            while (Clipboard->firstKata->firstHuruf != tempCursor){
                deleteHuruf(tempCursor, outHuruf);
            }
        }else{
            Clipboard->firstKata->firstHuruf = tempCursor;
            Clipboard->firstKata->lastHuruf = tempCursor;
        }


        while(i < jumlahSelect){
            if (counterHuruf == nullptr){
                counterKata = counterKata -> next;
                counterHuruf = counterKata ->firstHuruf;
            }
            inputHandler(tempCursor, counterHuruf -> info);
            i++;
            counterHuruf = counterHuruf -> next;
        }

        deleteCursor(tempCursor);
        activeBaris = tempActiveBaris;
        activeKata = tempActiveKata;

    }
}

void pasteHuruf(adrBaris Clipboard, adrHuruf &cursor){
//{I.S terdefinisi sebuah elemen baris Clipboard yang bisa kosong.
// F.S menempel beberapa karakter pada baris dengan posisi cursor.}
    adrKata tempKata;
    adrHuruf tempHuruf;

    tempKata = Clipboard->firstKata;
    while (tempKata != nullptr){
        tempHuruf = tempKata->firstHuruf;
        while (tempHuruf != nullptr){
            inputHandler(cursor, tempHuruf->info);
            tempHuruf = tempHuruf->next;
        }
        tempKata = tempKata->next;
    }
}

void cutHuruf(adrHuruf &cursor, int jumlahSelect){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong dan jumlah huruf yang di select oleh user.
// F.S memotong beberapa karakter pada baris sesuai input dari user dan menyimpannya ke Clipboard.}
    copyHuruf(cursor, jumlahSelect);
    int i = 0;
    while (i<jumlahSelect){
        moveCursorToRight(cursor);
        i++;
    }
    i = 0;
    while (i<jumlahSelect){
        adrHuruf outHuruf;
        deleteHuruf(cursor, outHuruf);
        i++;
    }
}

void printKata(adrKata inKata){
    adrHuruf counterHuruf;

    counterHuruf = inKata ->firstHuruf;
    while(counterHuruf != nullptr){
        cout << counterHuruf ->info;
        counterHuruf = counterHuruf -> next;
    }
}

void searchWord(){
//{I.S terdefinisi sebuah kursor yang tidak kosong.
// F.S mengubah latar belakang setiap kata yang dicari pada text editor, dan memasukkan pointer katanya ke vector listKata.}
    string kataCari;
    int jumlahKataCari;
    bool cekKata = false;

    system("cls");
    cout << "Masukkan kata yang ingin dicari: ";
    cin >> kataCari;
    jumlahKataCari = kataCari.length();

    system("cls");
    cout << "+===================================================+" << endl;
    cout << "|                TEXT EDITOR COTYPE--               |" << endl;
    cout << "+===================================================+" << endl;
    adrBaris tempActiveBaris = Line.first;
    adrKata tempActiveKata;
    adrHuruf tempHuruf;

    while(tempActiveBaris != nullptr){
        tempActiveKata = tempActiveBaris->firstKata;
        while(tempActiveKata != nullptr){
            tempHuruf = tempActiveKata->firstHuruf;
            int i = 0;

            if(lengthKata(tempActiveKata) == jumlahKataCari){
                while(tempHuruf != nullptr && i < jumlahKataCari){
                    if(tempHuruf -> info != '|'){
                        if(tempHuruf ->info == kataCari[i]){
                            cekKata = true;
                        }else{
                            cekKata = false;
                            break;
                        }
                        i++;
                    }
                    tempHuruf = tempHuruf -> next;
                }
            }else{
                cekKata = false;
            }

            if(cekKata){
                listKata.push_back(tempActiveKata);
            }
            tempActiveKata = tempActiveKata -> next;
        }
        tempActiveBaris = tempActiveBaris -> next;
    }

    bool found = false;
    adrBaris tempLine;
    adrKata tempKata;
    tempLine = Line.first;
    while (tempLine != nullptr){
        tempKata = tempLine->firstKata;
        while (tempKata != nullptr){
            for(adrKata searchKey : listKata){
                if (searchKey == tempKata){
                    found = true;
                }
            }
            tempHuruf = tempKata->firstHuruf;
            if(found){
                while(tempHuruf != nullptr){
                    if(tempHuruf -> info != '|'){
                        setColor(15,6);
                    }else{
                        setColor(7,0);
                    }
                    cout << tempHuruf->info;
                    tempHuruf = tempHuruf->next;
                }
            }else{
                while(tempHuruf != nullptr){
                    setColor(7,0);
                    cout << tempHuruf->info;
                    tempHuruf = tempHuruf->next;
                }
            }
            found = false;
            tempKata = tempKata->next;
        }
        tempLine = tempLine->next;
        if (tempLine != nullptr){
            cout << endl;
        }
    }
    setColor(7,0);

}

int lengthKata(adrKata inKata){
//{I.S terdefinisi sebuah pointer kata.
// F.S menghitung banyaknya karakter pada pointer kata yang dimasukkan.}
    int jumlah = 0;
    adrHuruf tempHuruf;
    tempHuruf = inKata ->firstHuruf;
    while(tempHuruf != nullptr){
        if(tempHuruf ->info != '|'){
            jumlah++;
        }
        tempHuruf = tempHuruf -> next;
    }

    return jumlah;

}

void replaceWord(adrHuruf &cursor){
//{I.S terdefinisi sebuah elemen kursor yang tidak kosong.
// F.S mengganti kata yang sudah dicari sebelumnya dengan kata baru sesuai input dari user.}
    string kataReplace;
    adrBaris tempActiveBaris = activeBaris;
    adrKata tempActiveKata = activeKata;
    int jumlahHurufReplace;
    bool found = false;
    bool active = false;
    bool first = false;
    bool last = false;

    first = activeKata == activeBaris->firstKata;
    last = activeKata == activeBaris->lastKata;

    cout << "Ganti kata dengan: ";
    cin >> kataReplace;
    jumlahHurufReplace = kataReplace.length();
    deleteCursor(cursor);
    activeBaris = Line.first;

    while (activeBaris != nullptr){
        activeKata = activeBaris->firstKata;
        while (activeKata != nullptr){
            found = false;
            insertLastHuruf(cursor);
            for (adrKata searchKey : listKata){
                found = found || searchKey == activeKata;
                if (found){
                    active = activeKata == tempActiveKata;
                }
            }
            if (found){
                int panjang = lengthKata(activeKata);
                int i = 0;
                while(i < panjang){
                    adrHuruf outHuruf;
                    deleteHuruf(cursor, outHuruf);
                    i++;
                }
                i = 0;
                while (i<jumlahHurufReplace){
                    inputHandler(cursor, kataReplace[i]);
                    i++;
                }
                if (active){
                    tempActiveKata = activeKata;
                    active = false;
                }
            }
            deleteCursor(cursor);
            found = false;
            activeKata = activeKata -> next;
        }
        activeBaris = activeBaris -> next;
    }
    printKata(tempActiveKata);
    activeBaris = tempActiveBaris;
    activeKata = tempActiveKata;
    insertLastHuruf(cursor);
    printKata(tempActiveKata);
    if (first){
        activeBaris->firstKata = tempActiveKata;
    }
    if (last){
        activeBaris->lastKata = tempActiveKata;
    }
}

Stack createStack(){
// {Membuat sebuah Stack dengan inisialisasi topnya adalah -1.}
    Stack S;

    S.top = -1;
    return S;
}

bool isFull(Stack S){
// {Mengembalikan nilai yang menyatakan Stack penuh atau tidak.}
    return S.top == 10-1;
}

bool isEmpty(Stack S){
// {Mengembalikan nilai yang menyatakan Stack kosong atau tidak.}
    return S.top == -1;
}

void push(Stack &S, Baris B){
//{I.S terdefinisi sebuah Stack yang mungkin penuh
// F.S memasukkan list Baris sebagai elemen paling atas dalam Stack.}
    Stack tempS;
    Baris outBaris;
    tempS = createStack();
    if (isFull(S)){
        while (!isEmpty(S)){
            pop(S, outBaris);
            push(tempS, outBaris);
        }
        pop(tempS, outBaris);
        while (!isEmpty(tempS)){
            pop(tempS, outBaris);
            push(S, outBaris);
        }
    }

    if (!isFull(S)){
        S.top = S.top+1;
        S.info[S.top] = B;
    }
}

void pop(Stack &S, Baris &outBaris){
//{I.S terdefinisi sebuah Stack yang mungkin kosong.
// F.S mengeluarkan elemen teratas dari Stack.}
    if (!isEmpty(S)){
        outBaris = S.info[S.top];
        S.top = S.top-1;
    }
}

void insertElementStack(Stack &S){
//{I.S terdefinisi sebuah Stack yang mungkin kosong.
// F.S memasukan salinan dari list Baris yang sedang aktif ke dalam Stack.}
    Baris tempLine, newLine;
    adrBaris pointerLine, tempActiveBaris;
    adrKata pointerKata, tempActiveKata;
    adrHuruf pointerHuruf, tempCursor;

    tempLine = createBaris();
    tempActiveBaris = activeBaris;
    tempActiveKata = activeKata;

    pointerLine = Line.first;
    tempLine = Line;

    adrKata kataPertama;
    adrBaris B;

    newLine = createBaris();
    B = createElemBaris();
    newLine.first = B;
    newLine.last = B;
    kataPertama = createElemKata();
    B->firstKata = kataPertama;
    B->lastKata = kataPertama;
    tempCursor = createElemHuruf('|');
    kataPertama->firstHuruf = tempCursor;
    kataPertama->lastHuruf = tempCursor;
    activeBaris = newLine.first;
    activeKata = kataPertama;
    Line = newLine;

    while (pointerLine != nullptr){
        pointerKata = pointerLine->firstKata;
        while (pointerKata != nullptr){
            pointerHuruf = pointerKata->firstHuruf;
            while (pointerHuruf != nullptr){
                if(pointerHuruf -> info != '|'){
                    inputHandler(tempCursor, pointerHuruf->info);
                }
                pointerHuruf = pointerHuruf->next;
            }
            pointerKata = pointerKata->next;
        }
        if (pointerLine->next != nullptr){
            inputEnter(tempCursor);
        }
        pointerLine = pointerLine->next;
    }
    deleteCursor(tempCursor);
    push(S, Line);
    Line = tempLine;
    activeBaris = tempActiveBaris;
    activeKata = tempActiveKata;

}

void undo(adrHuruf &cursor){
//{I.S terdefinisi sebuah elemen kursor.
// F.S menyimpan keseluruhan list di dalam redoStack dan mengembalikan perubahan yang telah dilakukan dengan mengeluarkan list Baris dari undoStack.}
    if (!isEmpty(undoStack)){
        Baris tempLine;
        insertElementStack(redoStack);

        pop(undoStack, tempLine);
        deleteCursor(cursor);
        Line = tempLine;
        activeBaris = Line.last;
        activeKata = activeBaris->lastKata;

        insertLastHuruf(cursor);
    }
}

void redo(adrHuruf &cursor){
//{I.S terdefinisi sebuah elemen kursor.
// F.S menyimpan keseluruhan list di dalam undoStack dan membatalkan pengembalian perubahan yang telah dilakukan dengan mengeluarkan list Baris dari redoStack.}
    if (!isEmpty(redoStack)){
        Baris tempLine;
        deleteCursor(cursor);
        insertElementStack(undoStack);
        pop(redoStack, tempLine);
        Line = tempLine;
        activeBaris = Line.last;
        activeKata = activeBaris->lastKata;

        insertLastHuruf(cursor);
    }
}

void clearStack(Stack &S){
//{I.S terdefinisi sebuah Stack yang mungkin kosong.
// F.S semua elemen Stack dikeluarkan dari Stack.}
    Baris outBaris;
    while (!isEmpty(S)){
        pop(S, outBaris);
    }
}
