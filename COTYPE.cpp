#include "COTYPE.h"

// Mendefinisikan variabel global
adrKata activeKata = nullptr;
adrBaris activeBaris = nullptr;
Baris Line = {nullptr, nullptr};
adrBaris Clipboard = nullptr;

Baris createBaris(){
//{Mengembalikan sebuah baris dengan first dan last diinisialisasi sebagai NIL}
    Baris P;
    P.first = nullptr;
    P.last = nullptr;

    return P;

}

adrBaris createElemBaris(){
//{Mengembalikan sebuah elemen baris dengan next, prev, firstKata, dan lastKata diinisialisasi sebagai NIL}
    adrBaris P;
    P = new elmBaris;
    P -> next = nullptr;
    P -> prev = nullptr;
    P -> firstKata = nullptr;
    P -> lastKata = nullptr;

    return P;
}
adrKata createElemKata(){
//{Mengembalikan sebuah elemen kata dengan next, prev, firstHuruf, dan lastHuruf diinisialisasi sebagai NIL}
    adrKata P;
    P = new elmKata;
    P -> next = nullptr;
    P -> prev = nullptr;
    P -> firstHuruf = nullptr;
    P -> lastHuruf = nullptr;

    return P;
}
adrHuruf createElemHuruf(char x){
//{Mengembalikan sebuah elemen huruf dengan next dan prev diinisialisasi sebagai NIL, serta nilai info sesuai dengan parameter x}
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
    if (x == 32){ // kondisi karakter yang diinput adalah space
        inputSpace(cursor, x);
    }else if (x == 13){ // kondisi karakter yang diinput adalah enter
        inputEnter(cursor);
    }else if (x == 8) { // kondisi karakter yang diinput adalah backspace
        deleteHuruf(cursor, outHuruf);
    }else if (x == 19) {
        selectHuruf(cursor, jumlahSelect); // kondisi karakter yang diinput adalah CTRL + A
        cout << "--------" <<endl;
        cout << "activeKata firstHuruf: " << activeKata -> firstHuruf -> info << endl;
        cout << "activeKata lastHuruf: " << activeKata -> lastHuruf -> info << endl;
        setColor(7,0);

        x = _getch();
        system("cls");
        if (x == 3){
            //copyHuruf(cursor, jumlahSelect);
        }else if (x == 12){
            characterToLowercase(cursor, jumlahSelect);
        }else if (x == 21){
            characterToUppercase(cursor, jumlahSelect);
        }else{
            inputHandler(cursor, x);
        }
    }else if (x == 0 || x == -32){ // kondisi karakter yang diinput adalah arrow
        x = _getch();
        if (x == 75){ // kondisi karakter yang diinput adalah arrow left
            moveCursorToLeft(cursor);
        }else if (x == 77){
            moveCursorToRight(cursor); // kondisi karakter yang diinput adalah arrow right
        }else if (x == 72){
            moveCursorUp(cursor); // kondisi karakter yang diinput adalah arrow up
        }else if (x == 80){
            moveCursorDown(cursor); // kondisi karakter yang diinput adalah arrow down
        }
    }else if (x != 12 && x != 21){ // kondisi karakter yang diinput adalah huruf, angka, dan simbol
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
        if (activeKata->prev != nullptr){ // kondisi active kata merupakan kata pertama dalam baris
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
        }else if (cursor->next->info == ' '){ // kondisi setelah kursor terdapat ' '
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
        }else{ // kondisi lainnya
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
//{elemen huruf pertama dihapus dari active kata.}
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
//{elemen huruf setelah prec dihapus dari active kata.}
    if (prec != nullptr){
        outHuruf = prec -> next;
        prec -> next = outHuruf -> next;
        prec -> next -> prev = prec;
        outHuruf -> prev = nullptr;
        outHuruf -> next = nullptr;
    }
}

void deleteLastHuruf(adrHuruf &outHuruf){
//{elemen huruf terakhir dihapus dari active kata.}
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
    if(Line.first == nullptr){ // kondisi list line kosong
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
    cout << jumlahSelect;
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
    adrBaris tempBaris;
    adrKata tempKata;

    tempBaris = Line.first;
    while(tempBaris != nullptr){
        tempKata = tempBaris ->firstKata;
        while (tempKata != nullptr){
            if (tempKata -> firstHuruf != nullptr){
                if(tempKata -> firstHuruf -> info != ' '){
                    jumlahKata++;
                }
            }
                tempKata = tempKata -> next;
        }
        jumlahBaris++;
        tempBaris = tempBaris -> next;
    }

    cout << "Keterangan Text Editor" << endl;
    cout << "----------------------------"<< endl;
    cout << "Active baris first huruf: " << activeBaris->firstKata->firstHuruf -> info <<endl;
    cout << "Active baris last huruf: " << activeBaris->lastKata->lastHuruf -> info << endl;
    if (Line.first->firstKata->firstHuruf != nullptr){
        cout << "Active line first kata first huruf: " << Line.first->firstKata->firstHuruf->info << endl;
    }
    if (Line.last->lastKata->lastHuruf != nullptr){
        cout << "Active last kata last huruf: " << Line.last->lastKata->lastHuruf->info << endl;
    }
    cout << "Jumlah kata: "<< jumlahKata << endl;
    cout << "Jumlah baris: " << jumlahBaris << endl;
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
                    if(tempHuruf -> info == '|'){
                    }
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
    int i;

    cout << "Jumlah Huruf yang ingin di Select (Setelah Cursor): ";
    cin >> jumlahSelect;
    system("cls");
    cout << "Teks: " << endl;
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
            cout << endl;
            tempLine = tempLine->next;
        }
    }
    jumlahSelect = i-1;
    setColor(7,0);
    cout << endl;
}

//void copyHuruf(adrHuruf cursor, int jumlahSelect){
//    adrBaris tempActiveBaris = activeBaris;
//    adrKata tempActiveKata = activeKata;
//    adrHuruf tempCursor = Clipboard -> firstKata ->firstHuruf;
//
//    activeBaris = Clipboard;
//    activeKata = Clipboard -> firstKata;
//
//    adrHuruf counterHuruf;
//    int i =0;
//    counterHuruf = cursor;
//    while(i < jumlahSelect && counterHuruf != activeBaris -> lastKata -> lastHuruf){
//        counterHuruf = counterHuruf -> next;
//        inputHuruf(tempCursor, counterHuruf ->info);
//        i++;
//    }
//    if(counterHuruf == tempActiveBaris -> lastKata -> lastHuruf){
//        inputHuruf(tempCursor, counterHuruf ->info);
//    }
//    deleteCursor(tempCursor);
//    activeBaris = tempActiveBaris;
//    activeKata = tempActiveKata;
//}
