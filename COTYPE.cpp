#include "COTYPE.h"

adrLine activeLine = nullptr;


// Primitive addLine
void insertFirstLine(Line &L, adrLine PL){
    if (L.first == nullptr){
        L.first = PL;
        L.last = PL;
    }else{
        PL->next = L.first;
        L.first->prev = PL;
        L.first = PL;
    }
}

void insertLastLine(Line &L, adrLine PL){
    if (L.first == nullptr){
        L.first = PL;
        L.last = PL;
    }else{
        L.last->next = PL;
        PL->prev = L.last;
        L.last = PL;
    }
}

void insertAfterLine(Line &L, adrLine prec, adrLine PL){
    //Line tidak kosong dan terdapat minimal 1 elemen setelah prec
    PL->next = prec->next;
    prec->next->prev = PL;
    prec->next = PL;
    PL->prev = prec;
}

void insertBeforeLine(Line &L, adrLine succ, adrLine PL){
    //Line tidak kosong dan terdapat minimal 1 elemen sebelum prec
    PL->prev = succ->prev;
    PL->next = succ;
    succ->prev->next = PL;
    succ->prev = PL;
}

void deleteFirstLine(Line &L, adrLine &PL){
    if (L.first != nullptr){
        PL = L.first;
        if (L.first == L.last){
            L.first = nullptr;
            L.last = nullptr;
        }else{
            L.first = PL->next;
            PL->next = nullptr;
            L.first->prev = nullptr;
        }
    }
}

void deleteLastLine(Line &L, adrLine &PL){
    if (L.first != nullptr){
        PL = L.last;
        if (L.first == L.last){
            L.first = nullptr;
            L.last = nullptr;
        }else{
            L.last = PL->prev;
            L.last->next = nullptr;
            PL->prev = nullptr;
        }
    }
}
void deleteAfterLine(Line &L, adrLine prec, adrLine &PL){
    //Line tidak kosong dan terdapat minimal 2 elemen setelah prec
    PL = prec->next;
    prec->next = PL->next;
    PL->next->prev = prec;
    PL->next = nullptr;
    PL->prev = nullptr;
}

// Line
void createLine(Line &L){
    L.first = nullptr;
    L.last = nullptr;
}

void createElemenLine(adrLine &PL){
    PL->firstLetter = nullptr;
    PL->lastLetter = nullptr;
    PL->next = nullptr;
    PL->prev = nullptr;
}

void addLine(Line &L, adrLetter &cursor){
    adrLine PL;

    createElemenLine(PL);
    if (cursor == activeLine->firstLetter){
        if (activeLine->prev == nullptr){
            insertFirstLine(L, PL);
        }else{
            insertBeforeLine(L, activeLine, PL);
        }
    }else if (cursor == activeLine->lastLetter){
        if (activeLine->next == nullptr){
            insertLastLine(L, PL);
        }else{
            insertAfterLine(L, activeLine, PL);
        }
        cursor = activeLine->next->firstLetter;
        activeLine = activeLine->next;
    }
}

void deleteLine(Line &L, adrLetter &cursor, adrLine &PL){
    adrLetter temp;

    PL = activeLine;
    if (PL->lastLetter != nullptr){
        cursor = PL->lastLetter;
        while (cursor != nullptr){
            deleteCharacter(PL, temp, cursor);
            cursor = cursor->next;
        }
    }
    if (L.first == PL){
        deleteFirstLine(L, PL);
        cursor = L.first->firstLetter;
        activeLine = L.first;
    }else if (L.last == PL){
        deleteLastLine(L, PL);
        cursor = L.last->lastLetter;
        activeLine = L.last;
    }else{
        cursor = PL->prev->lastLetter;
        activeLine = PL->prev;
        deleteAfterLine(L, PL->prev, PL);
    }
}

// Primitive addLetter
void insertFirstLetter(adrLine &PL, adrLetter PLT){
    if (PL->firstLetter == nullptr){
        PL->firstLetter = PLT;
        PL->lastLetter = PLT;
    }else{
        PLT -> next = PL->firstLetter;
        PL->firstLetter -> prev = PLT;
        PL->firstLetter = PLT;
    }
}

void insertLastLetter(adrLine &PL, adrLetter PLT){
    if (PL->firstLetter == nullptr){
        PL->firstLetter = PLT;
        PL->lastLetter = PLT;
    }else{
        PL->lastLetter -> next = PLT;
        PLT -> prev = PL->lastLetter;
        PL->lastLetter = PLT;
    }
}

void insertAfterLetter(adrLine &PL, adrLetter prec, adrLetter PLT){
    PLT -> next = prec -> next;
    prec -> next -> prev = PLT;
    prec -> next = PLT;
    PLT -> prev = prec;
}

void deleteFirstLetter(adrLine &PL, adrLetter &PLT){
    if (PL->firstLetter != nullptr){
        if (PL->firstLetter -> next == nullptr){
            PLT = PL->firstLetter;
            PL->firstLetter = nullptr;
            PL->lastLetter = nullptr;
        }else{
            PLT = PL->firstLetter;
            PL->firstLetter = PL->firstLetter -> next;
            PLT -> next = nullptr;
            PL->firstLetter -> prev = nullptr;
        }
    }
}

void deleteLastLetter(adrLine &PL, adrLetter &PLT){
    if (PL->firstLetter != nullptr){
        if (PL->firstLetter -> next == nullptr){
            PLT = PL->firstLetter;
            PL->firstLetter = nullptr;
            PL->lastLetter = nullptr;
        }else{
            PLT = PL->lastLetter;
            PL->lastLetter = PL->lastLetter -> prev;
            PLT -> prev = nullptr;
            PL->lastLetter -> next = nullptr;
        }
    }
}

void deleteAfterLetter(adrLine &PL, adrLetter prec, adrLetter &PLT){
    PLT = prec -> next;
    prec -> next = PLT -> next;
    PLT -> next -> prev = prec;
    PLT -> next = nullptr;
    PLT -> prev = nullptr;
}

// Letter
adrLetter createLetter(char letter){
    adrLetter newLetter;
    newLetter = new elmLetter;

    newLetter -> info = letter;
    newLetter -> next = nullptr;
    newLetter -> prev = nullptr;

    return newLetter;
}

void insertCharacter(adrLine &PL, adrLetter PLT, adrLetter &cursor){
    if (PL->firstLetter == nullptr){
        insertFirstLetter(PL,PLT);
        cursor = PL->firstLetter;
    }else if (cursor == PL->lastLetter){
        insertLastLetter(PL,PLT);
        cursor = PL->lastLetter;
    }else{
        insertAfterLetter(PL,cursor,PLT);
        cursor = cursor -> next;
    }
}

void deleteCharacter(adrLine &PL, adrLetter &PLT, adrLetter &cursor){
    if (PL->firstLetter != nullptr){
        if (PL -> firstLetter -> next == nullptr){
            cursor = cursor -> next;
            deleteFirstLetter(PL,PLT);
        }else if (cursor == PL->lastLetter){
            cursor = cursor -> prev;
            deleteLastLetter(PL,PLT);
        }else{
            cursor = cursor -> prev;
            deleteAfterLetter(PL,cursor,PLT);
        }
    }else{
        cout << "Tidak ada karakter"<< endl;
    }
}

void displayAllCharacterInLine(adrLine PL){
    adrLetter temp = PL->firstLetter;
    while (temp != nullptr){
        cout << temp -> info << " ";
    }
}

void selectCharacter(adrLine PL, adrLetter &first, adrLetter &last, adrLetter cursor){
    int jumlahSelectedKarakter;

    cout << "List Karakter : " << endl;
    displayAllCharacterInLine(PL);
    cout << "Posisi Cursor: " << cursor -> info << endl;
    cout << "Jumlah selected karakter (setelah cursor): ";
    cin >> jumlahSelectedKarakter;
    first = cursor;
    last = cursor;

    i=1;
    while (i<=jumlahSelectedKarakter && last->next != nullptr){
        last = last->next;
        i++;
    }
}

void copySelectedCharacter(adrLetter &first, adrLetter &last){
    adrLine newLine;
    adrLetter temp, newLetter, tempCursor;

    createElemenLine(newLine);

    while (first != nullptr && last != nullptr){
        temp = first;
        while (temp != last -> next ){
            newLetter = createLetter(temp -> info);
            insertCharacter(newLine, newLetter, tempCursor);
        }
        first = newLine->firstLetter;
        last = newLine->lastLetter;
    }
}

void pasteSelectedCharacter(adrLine &PL, adrLetter first, adrLetter last, adrLetter &cursor){
    adrLetter tempLast;
    while (first != nullptr && last != nullptr){
        tempLast = cursor -> next;
        cursor -> next = first;
        first -> prev = cursor;
        last -> next = tempLast;
        tempLast -> prev = last;
    }
}

void cutSelectedCharacter(adrLine &PL, adrLetter &first, adrLetter &last, adrLetter &cursor){
    if (first != nullptr && last != nullptr){
        cursor = first -> prev;
        cursor -> next = last -> next;
        first -> prev = nullptr;
        last -> next -> prev = nullptr;
        last -> next = nullptr;
    }
}



//Cursor
void moveCursor(adrLine PL, adrLetter &cursor){
    string choice;
    cout << "Active Line: " << activeLine << endl;
    cout << "Posisi Cursor: " << cursor -> info << endl;
    cout << "        Move Cursor To        " << endl ;
    cout << "------------------------------" << endl;
    cout << "1. Right (R)                  "<< endl;
    cout << "2. Left (L)                   "<< endl;
    cout << "3. Line Up (U)                "<< endl;
    cout << "4. Line Down (D)              "<< endl;
    cout << "------------------------------" << endl;
    cout << "Choose (R/L/U/D): "<< endl;
    cin >> choice;

    if (choice == "R"){
        cursor = cursor -> next;
    }else if (choice == "L"){
        cursor = cursor -> prev;
    }else if (choice == "U"){
        activeLine = activeLine -> prev;
        cursor = activeLine->lastLetter;
    }else if (choice == "D"){
        activeLine = activeLine -> next;
        cursor = activeLine->lastLetter;
    }
}
