#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "sah.h"
#include "util.c"


int main(){
     
int index=0, result, position, white_side = 1, black_side = 2;
char *com;
com = malloc(20 * sizeof(char));

setbuf(stdout, NULL);
setbuf(stdin, NULL);

//initializari si setari ale jocului
printf("%s", "protover N\n");
printf("%s", "feature sigint=0 sigterm=0 san=0\n");
printf("%s", "new\n");
printf("%s", "variant 3check\n");

//dam discard la confirmarile pe care le primim legat de initializari si setari
for(int i = 0; i < 17; i++) {
   scanf("%s", com);
}

//creez tabla
Chess_Table *tabla;
tabla = malloc(sizeof(Chess_Table));
*tabla = resetGame();
tabla->side = 0;

while(1) {
    // portiune de cod pentru reinitializarea tablei    
    new:
    if(strcmp(com, "new") == 0) {
        *tabla = resetGame();
        for(int i = 0; i < 7; i++)
            scanf("%s", com);
        white_side = 1;
        black_side = 2;
    }
    // portiune de cod pentru capitularea botului
    resign:
    if(strcmp(com, "resign") == 0) {
        while(1){
            scanf("%s", com);
            if(strcmp(com, "new") == 0)
                goto new;
        }
    }
    // portiune de cod pentru schimbarea culorii botului in alb
    mach_white:
    if(strcmp(com, "black") == 0){
        for(int i = 0; i < 6; i++)
            scanf("%s", com);
        white_side = 2;
        black_side = 1;
        goto bot;
    }
    // portiune de cod pentru schimbarea culorii botului in negru
    mach_black:
    if(strcmp(com, "white") == 0){
        for(int i = 0; i < 6; i++)
            scanf("%s", com);
        white_side = 1;
        black_side = 2;
        goto bot;
    }
    // portiune de cod pentru scoaterea botului din joc
    force: 
     if(strcmp(com, "force") == 0){
        while(1){
        scanf("%s", com);
        if(strcmp(com, "new") == 0)
            goto new;
        if(strcmp(com, "black") == 0)
            goto mach_white;
        if(strcmp(com, "white") == 0)
            goto mach_black;
        afterMove(tabla, com);
        }
    }

    // interpretez mutarea utilizatorului
    tabla->side = white_side;
    for(int i = 0; i < 4; i++){
        scanf("%s", com);
        if(strcmp(com, "new") == 0)
            goto new;
        if(strcmp(com, "black") == 0)
            goto mach_white;
        if(strcmp(com, "force") == 0)
            goto force;
        if(strcmp(com, "white") == 0)
            goto mach_black;
        if(strcmp(com, "result") == 0)
            goto resign;
        if(strcmp(com, "quit") == 0)
            goto quit;
    }
    scanf("%s", com);
    afterMove(tabla, com);
    
    bot:
    // interpretez mutarea bot-ului
    tabla->side = black_side;
    com = attack(tabla);
    
    if (strcmp(com, "resign") == 0) {
        printf("%s\n", com);

    } else {
        printf("move %s\n", com);
        afterMove(tabla, com);
    }
}

quit:
    free(com);
    free(tabla);

return 0;
}
