#ifndef COTYPE_H_INCLUDED
#define COTYPE_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct elmLetter *adrLetter; //Membuat type alias adrLetter berupa pointer to elmletter
typedef struct elmLine *adrLine; //Membuat type alias adrLine berupa pointer to elmline
struct elmLetter{ //Mendefinisikan struct elmLetter dengan atribut info, next,prev
    char info;
    adrLetter next;
    adrLetter prev;
};

struct elmLine{ //Mendefinisikan struct elmLine dengan atribut info, next,prev
    adrLine next;
    adrLine prev;
    adrLetter firstLetter;
    adrLetter lastLetter;
};

struct Line{ //Mendefinisikan struct Line dengan atribut first, last
    adrLine first;
    adrLine last;
};

extern adrLine activeLine; // Membuat variabel global activeLine


// Primitive addLine
void insertFirstLine(Line &L, adrLine PL);
void insertLastLine(Line &L, adrLine PL);
void insertAfterLine(Line &L, adrLine prec, adrLine PL);
void insertBeforeLine(Line &L, adrLine succ, adrLine PL);

void deleteFirstLine(Line &L, adrLine &PL);
void deleteLastLine(Line &L, adrLine &PL);
void deleteAfterLine(Line &L, adrLine prec, adrLine &PL);

// Line
void createLine(Line &L);
void createElemenLine(adrLine &PL);
void addLine(Line &L, adrLetter &cursor);
void deleteLine(Line &L, adrLetter &cursor, adrLine &PL);


// Primitive addLetter
void insertFirstLetter(adrLine &PL, adrLetter PLT);
void insertLastLetter(adrLine &PL, adrLetter PLT);
void insertAfterLetter(adrLine &PL, adrLetter prec, adrLetter PLT);

void deleteFirstLetter(adrLine &PL, adrLetter &PLT);
void deleteLastLetter(adrLine &PL, adrLetter &PLT);
void deleteAfterLetter(adrLine &PL, adrLetter prec, adrLetter &PLT);


// Letter
adrLetter createLetter(char letter);
void insertCharacter(adrLine &PL, adrLetter PLT, adrLetter &cursor);
void deleteCharacter(adrLine &PL, adrLetter &PLT, adrLetter &cursor);
void selectCharacter(adrLine PL, adrLetter &first, adrLetter &last, adrLetter cursor);
void copySelectedCharacter(adrLetter &first, adrLetter &last);
void pasteSelectedCharacter(adrLine &PL, adrLetter first, adrLetter last, adrLetter &cursor);
void cutSelectedCharacter(adrLine &PL, adrLetter &first, adrLetter &last, adrLetter &cursor);

//Cursor
void moveCursor(adrLine PL, adrLetter &cursor);

#endif // COTYPE_H_INCLUDED
