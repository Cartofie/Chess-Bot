#include "util.h"
#include "stdio.h"

FILE *debug;

// functia de conversie a pozitiei in indice pentru vectorul tablei
int convertPos(char *pos)
{
    int result;
    // printf("Converting...%s\n", pos);
    result = 12 * (8 - ((int)pos[1] - '0')) + 26 + (int)(pos[0] - 'a');
    // printf("%d\n", result);
    return result;
}

Chess_Table resetGame()
{
    Chess_Table newTable;
    for (int i = 0; i < ourSize; i++)
    { // initializam o tabla noua
        newTable.table[i] = EMPTY;
    }
    /*newTable.table[D2]=wK;
    newTable.table[D4]=wP;
    newTable.table[C5]=dP;
    newTable.table[D6]=dQ;*/

    for (int i = 98; i < 106; i++)
    { // punem pionii de negru
        newTable.table[i] = wP;
    }

    for (int i = 38; i < 46; i++)
    { // punem pionii de alb
        newTable.table[i] = dP;
    }

    // punem restul pieselor
    // alb

    newTable.table[A1] = newTable.table[H1] = wR;
    newTable.table[B1] = newTable.table[G1] = wN;
    newTable.table[C1] = newTable.table[F1] = wB;
    newTable.table[D1] = wQ;
    newTable.table[E1] = wK;

    // negru

    newTable.table[A8] = newTable.table[H8] = dR;
    newTable.table[B8] = newTable.table[G8] = dN;
    newTable.table[C8] = newTable.table[F8] = dB;
    newTable.table[D8] = dQ;
    newTable.table[E8] = dK;

    newTable.side = 1; // 1 pentru alb, 2 pentru negru

    int buffer[13] = {32, 8, 2, 2, 2, 1, 1, 8, 2, 2, 2, 1, 1}; // evidenta pieselor de pe tabla de joc

    for (int i = 0; i < 13; i++)
    {
        newTable.pieceNumber[i] = buffer[i];
    }

    // punem pozitiile pionilor
    for (int i = 0; i < 8; i++)
    {
        newTable.wPawns[i] = A2 + i;
        newTable.dPawns[i] = A7 + i;
    }
    newTable.wPawns[8] = 0;
    newTable.dPawns[8] = 0;
    newTable.dQueens[1] = 0;
    newTable.dQueens[0] = D8;
    newTable.wQueens[1] = 0;
    newTable.wQueens[0] = D1;
    newTable.dRook[0] = A8;
    newTable.dRook[1] = H8;
    newTable.dRook[2] = 0;

    newTable.wRook[0] = A1;
    newTable.wRook[1] = H1;
    newTable.wRook[2] = 0;

    newTable.dKnights[0] = B8;
    newTable.dKnights[1] = G8;
    newTable.dKnights[2] = 0;

    newTable.wKnights[0] = B1;
    newTable.wKnights[1] = G1;
    newTable.wKnights[2] = 0;

    newTable.dBishops[0] = C8;
    newTable.dBishops[1] = F8;
    newTable.dBishops[2] = 0;

    newTable.wBishops[0] = C1;
    newTable.wBishops[1] = F1;
    newTable.wBishops[2] = 0;

    newTable.wKing = E1;
    newTable.dKing = E8;

    return newTable;
}

int checkDP(Chess_Table chess_table, char command[])
{
    int line1, line2, result;
    char *endPos;
    endPos = strndup((command + 2), 2);
    line1 = (int)command[1] - '1';
    line2 = (int)command[3] - '1';
    result = line1 - line2;
    if (command[0] != command[2] && chess_table.table[convertPos(endPos)] < 7)
    {
        // in cazul in care se schimba coloana, dar nu se ataca o piesa inamica, mutarea este invalida
        return 0;
    }
    if (line1 == 7)
    { // daca inca nu a fost mutat, poate inainta 2 casute
        if ((result == 1 || result == 2) && chess_table.table[convertPos(endPos)] != EMPTY)
        {
            return 0;
        }
    }
    if (result == 1 && chess_table.table[convertPos(endPos)] != EMPTY)
    {
        return 0;
    }

    if (result != 1)
    {
        return 0;
    }

    return 1;
}

// playerul face o mutare ( se primeste charul cu mutarea)
// se verifica validitatea ei (asta o face xboard pentru player)
// se muta piesa
// se actualizeaza tabla de joc

// posibil sa nu mai fie nevoie sa facem functii de verificare separate pe culori pentru piese
int checkN() {}
// verificam daca poate sa mute si va si returna mutarea
int checkR() {}

int checkB() {}

int checkQ() {}

int checkK() {}

int checkWP(Chess_Table chess_table, char command[])
{
    int line1, line2, result;
    char *endPos;
    endPos = strndup((command + 2), 2);
    line1 = (int)command[1] - '1';
    line2 = (int)command[3] - '1';
    result = line2 - line1;
    if (command[0] != command[2] && chess_table.table[convertPos(endPos)] < 7)
    {
        // in cazul in care se schimba coloana, dar nu se ataca o piesa inamica, mutarea este invalida
        return 0;
    }
    if (line1 == 2)
    { // daca inca nu a fost mutat, poate inainta 2 casute
        if ((result == 1 || result == 2) && chess_table.table[convertPos(endPos)] != EMPTY)
        {
            return 0;
        }
    }
    if (result == 1 && chess_table.table[convertPos(endPos)] != EMPTY)
    {
        return 0;
    }

    if (result != 1)
    {
        return 0;
    }

    return 1;
}

// verificam validitatea mutarii; 1 pentru valid si 0 pentru invalid
int checkForValid(Chess_Table chess_Table, char command[])
{
    // vedem ce piesa e
    // in functie de tipul ei, apelam o functie specifica de validare
    char *initPos, *endPos;
    int pieceType;

    initPos = strndup(command, 2);      // pozitia initiala
    endPos = strndup((command + 2), 2); // pozitia finala

    pieceType = chess_Table.table[convertPos(initPos)]; // luam tipul de piesa
    switch (pieceType)
    {
    case /* constant-expression */ 1:
        return (checkDP(chess_Table, command));
        /* code */
    case 2:
        return (checkN());
    case 3:
        return (checkR());
    case 4:
        return (checkB());
    case 5:
        return (checkK());
    case 6:
        return (checkQ());
    case 7:
        return (checkWP(chess_Table, command));
    case 8:
        return (checkN());
    case 9:
        return (checkR());
    case 10:
        return (checkB());
    case 11:
        return (checkK());
    case 12:
        return (checkQ());
    }
    return 0;
}

void replacePosition(int positions[], int initial, int final)
{
    int i = 0;
    while (positions[i] != 0)
    {
        if (positions[i] == initial)
        {
            positions[i] = final;
            break;
        }
        i++;
    }
}

// gasim tipul de piesa si mergem in vectorul corespunzator pentru
// a modifica pozitia
// pentru a elmina o piesa de pe tabla, trimitem -1 ca pozitie finala a piesei
void findAndReplace(Chess_Table *chess_Table, int type, int initial, int final)
{
    switch (type)
    {
    case dP:
    {
        if (final <= H1 && final >= A1)
        {
            chess_Table->dQueens[chess_Table->pieceNumber[dQ]] = final;
            chess_Table->pieceNumber[dQ]++;
            chess_Table->dQueens[chess_Table->pieceNumber[dQ]] = 0;
            findAndReplace(chess_Table, type, initial, -1);
            chess_Table->pieceNumber[dP]--;
        }
        else
        {
            replacePosition(chess_Table->dPawns, initial, final);
        }
        break;
    }
    case dN:
    {
        replacePosition(chess_Table->dKnights, initial, final);
        break;
    }
    case dB:
    {
        replacePosition(chess_Table->dBishops, initial, final);
        break;
    }
    case dR:
    {
        replacePosition(chess_Table->dRook, initial, final);
        break;
    }
    case dQ:
    {
        replacePosition(chess_Table->dQueens, initial, final);
        break;
    }
    case dK:
    {
        chess_Table->dKing = final;
        break;
    }
    case wP:
    {
        if (final <= H2 && final >= A2)
        {
            chess_Table->wQueens[chess_Table->pieceNumber[wQ]] = final;
            chess_Table->pieceNumber[wQ]++;
            chess_Table->wQueens[chess_Table->pieceNumber[wQ]] = 0;
            findAndReplace(chess_Table, type, initial, -1);
            chess_Table->pieceNumber[wP]--;
        }
        else
        {
            replacePosition(chess_Table->wPawns, initial, final);
        }
        break;
    }
    case wN:
    {
        replacePosition(chess_Table->dKnights, initial, final);
        break;
    }
    case wR:
    {
        replacePosition(chess_Table->dRook, initial, final);
        break;
    }
    case wB:
    {
        replacePosition(chess_Table->dBishops, initial, final);
        break;
    }
    case wQ:
    {
        replacePosition(chess_Table->dQueens, initial, final);
        break;
    }
    case wK:
    {
        chess_Table->wKing = final;
        break;
    }
    };
}

// update-am tabla dupa ce s-a facut o mutare

void afterMove(Chess_Table *chess_Table, char command[])
{
    // printf("afterMove ... %s\n", command);
    // luam primele 2 caractere si vedem ce piesa avem la pozitia data
    // luam urmatoarele 2 caractere si mutam piesa acolo
    // in vct piesei resp, tre' sa modif poz in vct piesei resp
    char *initPos, *endPos;
    int finder, deleter;
    initPos = strndup(command, 2);
    endPos = strndup((command + 2), 2);
    // printf("%s...%s\n", initPos, endPos);
    // initPos[0] = initPos[0] - 'a';
    // inca nu am tratat eliminarea in sine a peisei de pe tabla
    // endPos[0] = endPos[0] - 'a';
    if (chess_Table->table[convertPos(endPos)] != EMPTY)
    {
        deleter = chess_Table->table[convertPos(endPos)];
        findAndReplace(chess_Table, deleter, convertPos(endPos), -1);
        chess_Table->pieceNumber[deleter]--;
    }
    chess_Table->table[convertPos(endPos)] = chess_Table->table[convertPos(initPos)];
    finder = chess_Table->table[convertPos(initPos)]; // ii luam tipul piesei inainte de a fi mutat
    findAndReplace(chess_Table, finder, convertPos(initPos), convertPos(endPos));
    chess_Table->table[convertPos(initPos)] = EMPTY;
    // printf("Leaving afterMove\n");
}

char *convertToLabel(int position, int endPos)
{
    int column, row, column1, row1;
    char *buffer;
    buffer = (char *)calloc(5, sizeof(char));
    column = position % 12;
    row = 10 - (position / 12);
    column1 = endPos % 12;
    row1 = 10 - (endPos / 12);

    buffer[0] = 'a' + column - 2;
    buffer[1] = (char)row + '0';
    buffer[2] = 'a' + column1 - 2;
    buffer[3] = (char)row1 + '0';
    buffer[4] = '\0';

    return buffer;
}

int isCheck(int *chess_Table, int color, int king_pos)
{
    //debug = fopen("debug", "at");
    int directions[8] = {13, -13, 11, -11, 12, -12, 1, -1}, i, aux, pos; // vector de miscare
    int directionsK[8] = {14, -14, 10, -10, 25, -25, 23, -23};
    if (color == 1)
    {
        pos = king_pos;
        //fprintf(debug, "[king pos]%d\n", pos);
        for (i = 0; i < 8; i++)
        {
            aux = pos + directions[i];
            //fprintf(debug, "%d ", aux);
            while (chess_Table[aux] == EMPTY)
            {
                //fprintf(debug, "%d ", aux);
                aux = aux + directions[i];
            }
            //fprintf(debug, "[piesa]%d\n", chess_Table[aux]);
            if (i < 4)
            {
                if (dQ == chess_Table[aux] || dB == chess_Table[aux])
                {
                    return 1;
                }
            }

            if (i >= 4)
            {
                if (dQ == chess_Table[aux] || dR == chess_Table[aux])
                {
                    return 1;
                }
            }
        }
        if (dP == chess_Table[pos - 11] || dP == chess_Table[pos - 13])
        {
            return 1;
        }

        for (i = 0; i < 8; i++)
        {
            if (dK == chess_Table[pos + directionsK[i]])
            {
                return 1;
            }
        }
    }

    if (color == 2)
    {
        pos = king_pos;
        //fprintf(debug, "[king pos]%d\n", pos);
        for (i = 0; i < 8; i++)
        {
            aux = pos + directions[i];
            //fprintf(debug, "%d ", aux);
            while (chess_Table[aux] == EMPTY)
            {
                //fprintf(debug, "%d ", aux);
                aux = aux + directions[i];
            }

            //fprintf(debug, "[piesa]%d\n", chess_Table[aux]);
            if (i < 4)
            {
                if (wQ == chess_Table[aux] || wB == chess_Table[aux])
                {
                    return 1;
                }
            }

            if (i >= 4)
            {
                if (wQ == chess_Table[aux] || wR == chess_Table[aux])
                {
                    return 1;
                }
            }
        }
        if (wP == chess_Table[pos + 11] || wP == chess_Table[pos + 13])
        {
            return 1;
        }

        for (i = 0; i < 8; i++)
        {
            if (wK == chess_Table[pos + directionsK[i]])
            {
                return 1;
            }
        }
    }
    //fclose(debug);
    return 0;
}

int canMovePawn(Chess_Table *chess_Table, int position, int color)
{
    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }

    if (color == 1)
    {
        // daca poate ataca pe dreapta, va returna -11
        if (chess_Table->table[position - 11] < 7 && chess_Table->table[position - 11] != EMPTY)
        {
            clone[position - 11] = wP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->wKing))
            {
                return -11;
            }
            clone[position] = chess_Table->table[position];
            clone[position - 11] = chess_Table->table[position - 11];
        }
        // daca poate ataca pe stanga, va returna -13
        if (chess_Table->table[position - 13] < 7 && chess_Table->table[position - 13] != EMPTY)
        {
            clone[position - 13] = wP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->wKing))
            {
                return -13;
            }
            clone[position] = chess_Table->table[position];
            clone[position - 13] = chess_Table->table[position - 13];
        }
        // daca doar va merge in fata
        if (position > 97 && position < 106)
        {
            // pentru 2 patrate va returna -24
            if (chess_Table->table[position - 12] == EMPTY && chess_Table->table[position - 24] == EMPTY)
            {
                clone[position - 24] = wP;
                clone[position] = EMPTY;
                if (!isCheck(clone, color, chess_Table->wKing))
                {
                    return -24;
                }
                clone[position] = chess_Table->table[position];
                clone[position - 24] = chess_Table->table[position - 24];
            }
        }
        if (chess_Table->table[position - 12] == EMPTY)
        {
            clone[position - 12] = wP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->wKing))
            {
                return -12;
            }
            clone[position] = chess_Table->table[position];
            clone[position - 12] = chess_Table->table[position - 12];
        }
        return 0;
    }
    else
    { // culoarea neagra
        // daca poate ataca in partea dreapta, va returna 13
        if (chess_Table->table[position + 13] > 6)
        {
            clone[position + 13] = dP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->dKing))
            {
                return 13;
            }
            clone[position] = chess_Table->table[position];
            clone[position + 13] = chess_Table->table[position + 13];
        }
        // daca poate ataca pe stanga, va returna 11
        if (chess_Table->table[position + 11] > 6)
        {
            clone[position + 11] = dP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->dKing))
            {
                return 11;
            }
            clone[position] = chess_Table->table[position];
            clone[position + 11] = chess_Table->table[position + 11];
        }
        // daca poate merge 2 patratele, va returna 24
        if (position > 37 && position < 46)
        {
            if (chess_Table->table[position + 12] == EMPTY && chess_Table->table[position + 24] == EMPTY)
            {
                clone[position + 24] = dP;
                clone[position] = EMPTY;
                if (!isCheck(clone, color, chess_Table->dKing))
                {
                    return 24;
                }
                clone[position] = chess_Table->table[position];
                clone[position + 24] = chess_Table->table[position + 24];
            }
        }
        // daca poate muta doar o patratica, va returna 12
        if (chess_Table->table[position + 12] == EMPTY)
        {
            clone[position + 12] = dP;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, chess_Table->dKing))
            {
                return 12;
            }
            clone[position] = chess_Table->table[position];
            clone[position + 12] = chess_Table->table[position + 12];
        }
        return 0;
    }
}

// vom return noua pozitie la care poate fi mutata tura pe tabla noastra de joc
int canMoveRock(Chess_Table *chess_Table, int position, int color)
{
    // verificam sa nu aiba in jur piese de aceeasi culoare
    // vedem ce culoare are pentru a sti ce piese nu are voie sa manance
    // mergem cu un while in fiecare directie si ne oprim cand ni se blocheaza calea
    // si tinem cont ca luam piesa daca e de culoare diferita
    int aux_position, i = 1, pos = position, aux_loc, haven = position, king;
    int directions[4] = {12, -12, 1, -1}; // vector de miscare

    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }
    debug = fopen("debug", "at");
    fprintf(debug, "S-a intrat pentru tura\n");
    for (int j = 0; j < 4; j++)
    {
        i = 1;
        haven = position;
        while (1)
        {
            if (color == 1) {
                clone[pos] = wR;
                king = chess_Table->wKing;
            } else {
                clone[pos] = dR;
                king = chess_Table->dKing;
            }
            
            clone[position] = EMPTY;
            if (!isCheck(clone, color, king))
            {
                haven = pos;
            }
            clone[position] = chess_Table->table[position];
            clone[pos] = chess_Table->table[pos];
            pos = position + i * directions[j];     // pozitia ipotetica a turei pe tabla de joc
            aux_position = chess_Table->table[pos]; // vedem daca e vreo piesa la pozitia respectiva
            if (pos < 26 || pos > 117)
            { // ne asiguram ca nu se iese de pe tabla
                pos -= directions[j];
                break;
            }
            aux_loc = pos % 12;
            if (aux_loc < 2 || aux_loc > 9)
            {
                pos -= directions[j];
                break;
            }
            if (aux_position > 6)
            { // in cazul in care se ajunge la o piesa
                // de aceeasi culoare, mergem o patratica inapoi
                if (color == 1)
                {
                    pos -= directions[j];
                }
                break;
            }
            if (aux_position < 7 && aux_position != 0)
            { // daca am gasit o piesa inamica, o vom lua
                if (color == 2)
                {
                    pos -= directions[j];
                }
                break;
            }
            
            i++;
        }
        if (pos != position && haven != position)
        {
            fclose(debug);
            return haven;
        }
    }
    fclose(debug);
    return 0;
}

int canMoveBishop(Chess_Table *chess_Table, int position, int color)
{
    // verificam sa nu aiba in jur piese de aceeasi culoare
    // vedem ce culoare are pentru a sti ce piese nu are voie sa manance
    // mergem cu un while in fiecare directie si ne oprim cand ni se blocheaza calea
    // si tinem cont ca luam piesa daca e de culoare diferita
    int aux_position, i = 1, pos = position, aux_loc, haven = position, king;
    int directions[4] = {13, -13, 11, -11}; // vector de miscare

    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }
    debug = fopen("debug", "at");
    fprintf(debug, "S-a intrat pentru episcop\n");

    for (int j = 0; j < 4; j++)
    {
        i = 1;
        haven = position;
        while (1)
        {
            if (color == 1) {
                clone[pos] = wB;
                king = chess_Table->wKing;
            } else {
                clone[pos] = dB;
                king = chess_Table->dKing;
            }
            
            clone[position] = EMPTY;
            if (!isCheck(clone, color, king))
            {
                haven = pos;
            }
            clone[position] = chess_Table->table[position];
            clone[pos] = chess_Table->table[pos];
            pos = position + i * directions[j];     // pozitia ipotetica a nebunului pe tabla de joc
            aux_position = chess_Table->table[pos]; // vedem daca e vreo piesa la pozitia respectiva
            if (pos < 26 || pos > 117)
            { // ne asiguram ca nu se iese de pe tabla
                pos -= directions[j];
                break;
            }
            aux_loc = pos % 12;
            if (aux_loc < 2 || aux_loc > 9)
            {
                pos -= directions[j];
                break;
            }
            if (aux_position > 6)
            { // in cazul in care se ajunge la o piesa
                // de aceeasi culoare, mergem o patratica inapoi
                if (color == 1)
                {
                    pos -= directions[j];
                }
                break;
            }
            if (aux_position < 7 && aux_position != 0)
            { // daca am gasit o piesa inamica, o vom lua
                if (color == 2)
                {
                    pos -= directions[j];
                }
                break;
            }
            
            i++;
        }
        if (pos != position && haven != position)
        {
            fclose(debug);
            return haven;
        }
    }
    fclose(debug);
    return 0;
}

int canMoveKnight(Chess_Table *chess_Table, int position, int color)
{
    // verificam sa nu aiba in jur piese de aceeasi culoare
    // vedem ce culoare are pentru a sti ce piese nu are voie sa manance
    // mergem cu un while in fiecare directie si ne oprim cand ni se blocheaza calea
    // si tinem cont ca luam piesa daca e de culoare diferita
    int aux_position, i = 1, pos = position, aux_loc, king, haven;
    int directions[8] = {14, -14, 10, -10, 25, -25, 23, -23}; // vector de miscare

    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }
    debug = fopen("debug", "at");
    fprintf(debug, "S-a intrat pentru cal\n");

    for (int j = 0; j < 8; j++)
    {
        // facem o clona a tablei pentru a verifica daca 
        // la o anumita mutare a calului regele nu este in sah
        haven = position;
        pos = position + directions[j];         // pozitia ipotetica a calului pe tabla de joc
        aux_position = chess_Table->table[pos]; // vedem daca e vreo piesa la pozitia respectiva
        if (color == 1)
        {
            clone[pos] = wN;
            king = chess_Table->wKing;
        }
        else
        {
            clone[pos] = dN;
            king = chess_Table->dKing;
        }

        clone[position] = EMPTY;
        fprintf(debug, "Asta mutarea care se verifica: %d\n", pos);
        if (!isCheck(clone, color, king))
        {
            haven = pos;
        }
        clone[position] = chess_Table->table[position];
        clone[pos] = chess_Table->table[pos];
        pos = position + i * directions[j]; // pozitia ipotetica a calului pe tabla de joc
        aux_position = chess_Table->table[pos];
        if (pos < 26 || pos > 117)
        { // ne asiguram ca nu se iese de pe tabla
            pos -= directions[j];
        }
        aux_loc = pos % 12;
        if (aux_loc < 2 || aux_loc > 9)
        {
            pos -= directions[j];
        }
        if (aux_position > 6)
        { // in cazul in care se ajunge la o piesa
            // de aceeasi culoare, mergem o patratica inapoi
            if (color == 1)
            {
                pos -= directions[j];
            }
        }
        if (aux_position < 7 && aux_position != 0)
        { // daca am gasit o piesa inamica, o vom lua
            if (color == 2)
            {
                pos -= directions[j];
            }
        }
        if (pos != position && haven != position)
        {
            fclose(debug);
            return haven;
        }
    }
    
    fclose(debug);
    return 0;
}

int canMoveQueen(Chess_Table *chess_Table, int position, int color)
{
    // verificam sa nu aiba in jur piese de aceeasi culoare
    // vedem ce culoare are pentru a sti ce piese nu are voie sa manance
    // mergem cu un while in fiecare directie si ne oprim cand ni se blocheaza calea
    // si tinem cont ca luam piesa daca e de culoare diferita
    int aux_position, i = 1, pos = position, aux_loc, haven, flag, king;
    int directions[8] = {13, -13, 11, -11, 12, -12, 1, -1}; // vector de miscare

    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }
    debug = fopen("debug", "at");
    fprintf(debug, "S-a intrat pentru regina\n");

    for (int j = 0; j < 8; j++)
    {
        i = 1;
        haven = position;
        while (1)
        {
            if (color == 1) {
                clone[pos] = wQ;
                king = chess_Table->wKing;
            } else {
                clone[pos] = dQ;
                king = chess_Table->dKing;
            }
            
            clone[position] = EMPTY;
            if (!isCheck(clone, color, king))
            {
                haven = pos;
            }
            clone[position] = chess_Table->table[position];
            clone[pos] = chess_Table->table[pos];
            pos = position + i * directions[j];     // pozitia ipotetica a reginei pe tabla de joc
            aux_position = chess_Table->table[pos]; // vedem daca e vreo piesa la pozitia respectiva
            if (pos < 26 || pos > 117)
            { // ne asiguram ca nu se iese de pe tabla
                pos -= directions[j];
                break;
            }
            aux_loc = pos % 12;
            if (aux_loc < 2 || aux_loc > 9)
            {
                pos -= directions[j];
                break;
            }
            if (aux_position > 6)
            { // in cazul in care se ajunge la o piesa
                // de aceeasi culoare, mergem o patratica inapoi
                if (color == 1)
                {
                    pos -= directions[j];
                }
                break;
            }
            if (aux_position < 7 && aux_position != 0)
            { // daca am gasit o piesa inamica, o vom lua
                if (color == 2)
                {
                    pos -= directions[j];
                }
                break;
            }
            
            i++;
        }
        if (pos != position && haven != position)
        {
            return haven;
        }
    }

    return 0;
}

int canMoveKing(Chess_Table *chess_Table, int position, int color)
{
    // verificam sa nu aiba in jur piese de aceeasi culoare
    // vedem ce culoare are pentru a sti ce piese nu are voie sa manance
    // mergem cu un while in fiecare directie si ne oprim cand ni se blocheaza calea
    // si tinem cont ca luam piesa daca e de culoare diferita
    int aux_position, i = 1, pos = position, aux_loc;
    int directions[8] = {13, -13, 11, -11, 12, -12, 1, -1}; // vector de miscare

    int clone[ourSize];
    for (int i = 0; i < ourSize; i++)
    {
        clone[i] = chess_Table->table[i];
    }

    for (int j = 0; j < 8; j++)
    {

        pos = position + directions[j];         // pozitia ipotetica a turei pe tabla de joc
        aux_position = chess_Table->table[pos]; // vedem daca e vreo piesa la pozitia respectiva
        if (color == 1 && aux_position < 7 && pos > 25 && pos < 118)
        {
            clone[pos] = wK;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, pos))
            {
                return pos;
            }
            clone[position] = chess_Table->table[position];
            clone[pos] = chess_Table->table[pos];
        }
        else if (color == 2 && (aux_position > 6 || aux_position == EMPTY) 
            && pos > 25 && pos < 118 && (pos %12 >= 2 && pos % 12 < 10) )
        {
            clone[pos] = dK;
            clone[position] = EMPTY;
            if (!isCheck(clone, color, pos))
            {
                return pos;
            }
            clone[position] = chess_Table->table[position];
            clone[pos] = chess_Table->table[pos];
        }
    }

    return 0;
}

char *attack(Chess_Table *chess_Table)
{
    int result, position;
    char *buffer;
    buffer = malloc(10 * sizeof(char));

    if (chess_Table->side == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            position = chess_Table->wPawns[i];
            if (position != -1)
            {
                result = canMovePawn(chess_Table, position, 1);
                if (result != 0)
                {
                    buffer = convertToLabel(position, position + result);
                    return buffer;
                }
            }
        }

        position = chess_Table->wKing;
        if (position != -1)
        {
            result = canMoveKing(chess_Table, position, 1);
            if (result != 0)
            {
                buffer = convertToLabel(position, result);
                return buffer;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->wQueens[i];
            if (position != -1)
            {
                result = canMoveQueen(chess_Table, position, 1);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->wKnights[i];
            if (position != -1)
            {
                result = canMoveKnight(chess_Table, position, 1);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->wBishops[i];
            if (position != -1)
            {
                result = canMoveBishop(chess_Table, position, 1);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->wRook[i];
            if (position != -1)
            {
                result = canMoveRock(chess_Table, position, 1);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        // gasim primul pion care poate fi mutat si-l mutam
    }
    else
    {
        position = chess_Table->dKing;
        if (position != -1)
        {
            result = canMoveKing(chess_Table, position, 2);
            if (result != 0)
            {
                buffer = convertToLabel(position, result);
                return buffer;
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->dBishops[i];
            if (position != -1)
            {
                result = canMoveBishop(chess_Table, position, 2);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->dQueens[i];
            if (position != -1)
            {
                result = canMoveQueen(chess_Table, position, 2);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->dRook[i];
            if (position != -1)
            {
                result = canMoveRock(chess_Table, position, 2);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        
        for (int i = 0; i < 2; i++)
        {
            position = chess_Table->dKnights[i];
            if (position != -1)
            {
                result = canMoveKnight(chess_Table, position, 2);
                if (result != 0)
                {
                    buffer = convertToLabel(position, result);
                    return buffer;
                }
            }
        }
        

        for (int i = 0; i < 8; i++)
        {
            position = chess_Table->dPawns[i];
            if (position != -1)
            {
                result = canMovePawn(chess_Table, position, 2);
                if (result != 0)
                {
                    buffer = convertToLabel(position, position + result);
                    return buffer;
                }
            }
        }
    }

    strcpy(buffer, "resign");
    return buffer;
}
