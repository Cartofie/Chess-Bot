#ifndef SAH_H
#define SAH_H

#define ourSize 144
//      0    1    2   3   4   5   6   7   8   9  10  11  12
enum {EMPTY, dP, dN, dR, dB, dK, dQ, wP, wN, wR, wB, wK, wQ};

enum {
    A8 = 26, B8, C8, D8, E8, F8, G8, H8,
    A7 = 38, B7, C7, D7, E7, F7, G7, H7,
    A6 = 50, B6, C6, D6, E6, F6, G6, H6,
    A5 = 62, B5, C5, D5, E5, F5, G5, H5,
    A4 = 74, B4, C4, D4, E4, F4, G4, H4,
    A3 = 86, B3, C3, D3, E3, F3, G3, H3,
    A2 = 98, B2, C2, D2, E2, F2, G2, H2,
    A1 = 110, B1, C1, D1, E1, F1, G1, H1, PIEDONE
};

typedef struct {
    int wPawns[9], dPawns[9]; // retinem pozitiile curente ale pionilor
    int wKnights[3], dKnights[3], wQueens[9], dQueens[9], wRook[3], dRook[3], wBishops[3], dBishops[3], wKing, dKing;
    // vom adauga la celelalte etape vectorii si pentru celelalte piese
    int nrwQueens, nrdQueens;
    int table[ourSize]; // tabla de joc 
    int side; // retinem partea care trebuie sa mute 1 pentru alb si 2 pentru negru
    int pieceNumber[13]; // numarul de piese de pe tabla la un anumit moment

} Chess_Table;

#endif