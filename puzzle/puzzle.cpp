#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>


#define atas 1
#define kiri 2
#define bawah 3
#define kanan 4

#define keyUp 0x048
#define keyDown 0x050
#define keyLeft 0x04b
#define keyRight 0x04d

#define true 1
#define false 0

#define easy 10
#define medium 20
#define hard 30

#define caption " ----------------\n// GAME PUZZLE //\n----------------\n"

#define fieldSize 4
#define WINDOWS 1

void clrscr() {
  #ifdef WINDOWS
  system("cls");
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}

char field[fieldSize][fieldSize];
char field2[fieldSize][fieldSize];
unsigned int seed;
int x, y;

int acak(int i);
void initField(int movement);
void move(int arah);
void generateOutput();
int cekUrut();

int acak(int i) {
    int a;
    seed += 5;
    srand(seed);

    a = (rand() % i) + 1;

    return(a);
}

void initField(int movement) {
    int arah, arahOld = -1, nPindah = movement, xOld, yOld;
    int c = 1, i, j;
    char temp;

    srand(time(NULL));
    seed = rand();
    x = y = (fieldSize - 1);

    for (i = 0; i <= (fieldSize - 1); i++) {
        for (j = 0; j <= (fieldSize - 1); j++) {
            field[i][j] = field2[i][j] = c;
            c++;
        }
    }
    field[fieldSize - 1][fieldSize - 1] = field2[fieldSize - 1][fieldSize - 1] = ' ';

    c = 0;
    while (c != nPindah) {
        xOld = x;
        yOld = y;
        arah = acak(4);

        if (arah != 0) {
            if ( c != 0) {
                if ((arah + 2) % 4 == arahOld) {
                    continue;
                }
            }

            switch (arah) {
                case atas :
                    if (y > 0) y--;
                    else continue;
                    break;
                case kiri:
                    if (x > 0) x--;
                    else continue;
                    break;
                case kanan :
                    if (x < fieldSize - 1) x++;
                    else continue;
                    break;
                case bawah :
                    if (y < fieldSize - 1) y++;
                    else continue;
                    break;
                default :
                    break;
            }

            if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {
                temp = field[y][x];
                field[y][x] = field[yOld][xOld];
                field[yOld][xOld] = temp;

                c++;
                arahOld = arah % 4;
            } else {
                x = xOld;
                y = yOld;
            }
        }
    }
}

void move(int arah) {
    int xOld, yOld;
    char temp;

    xOld = x;
    yOld = y;

    switch (arah) {
        case atas :
            if (y > 0) y--;
            break;
        case kiri:
            if (x > 0) x--;
            break;
        case kanan :
            if (x < (fieldSize - 1)) x++;
            break;
        case bawah :
            if (y < (fieldSize - 1)) y++;
            break;
        default :
            break;
    }

    if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {
        temp = field[y][x];
        field[y][x] = field[yOld][xOld];
        field[yOld][xOld] = temp;
    } else {
        x = xOld;
        y = yOld;
    }
    generateOutput();
}

void generateOutput() {
    int i, j, k;
    clrscr();
    puts(caption);
    puts("Tekan ESC untuk keluar / reset permainan...");
    for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");

    for (i = 0; i<=(fieldSize - 1); i++) {
        for (j= 0; j<=(fieldSize - 1); j++) {
            if (i == y && j == x) {
                printf("| %c  ", field[i][j]);
            } else {
                printf("| %2i ", field[i][j]);
            }
        }
        puts("|");

        for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    }
}

int cekUrut() {
    int c, d;
    int match = true;

    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            if (field[c][d] != field2[c][d]) {
                if (match == true) {
                    match = false;
                }
            }
        }
    }
    return(match);
}

main() {
    int i, j, k, level;
    char key;

    system("cls");
    puts(caption);
    puts("Mainkan puzzle dan menyusunnya menjadi urutan yang benar...");
    puts("Geser kotak kosong sehingga menjadi berurutan sbg berikut : \n");
    initField(0);
    for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    for (i = 0; i<=(fieldSize - 1); i++) {
        for (j= 0; j<=(fieldSize - 1); j++) {
            if (i == y && j == x) {
                printf("| %c  ", field2[i][j]);
            } else {
                printf("| %2i ", field2[i][j]);
            }
        }
        puts("|");

        for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    }
    puts("Gunakan tombol panah untuk menggeser kotak kosong...\n");
    puts("Tekan sembarang tombol untuk melanjutkan...");
    getch();
    for(;;) {
        system("cls");
        puts("Level : ");
        puts("\t1. Easy");
        puts("\t2. Medium");
        puts("\t3. Hard");
        printf("Pilih Level yang akan dimainkan : ");
         scanf("%i", &level);
        
        switch (level) {
            case 1 :
                initField(easy);
                break;
            case 2 :
                initField(medium);
                break;
            case 3 :
                initField(hard);
                break;
            default :
                puts("Level salah!!");
                getch();
                continue;
        }
        
        system("cls");

        generateOutput();

        while ((key = getch()) != 27) {
            switch(key) {
                case keyUp :
                    move(atas);
                    break;
                case keyDown :
                    move(bawah);
                    break;
                case keyLeft :
                    move(kiri);
                    break;
                case keyRight :
                    move(kanan);
                    break;
            }
            if (cekUrut() == true) {
                puts("\nANDA MENANG!!!");
                break;
            }
        }
        if (key == 27) {
            printf("Apakah anda ingin keluar ?\n['y' utk keluar / 't' utk reset] : ");
            if (toupper(getchar()) == 'Y') break;
            else continue;
        } else {
            printf("Apakah anda ingin main lagi ? [y/t] : ");
            if (toupper(getchar()) == 'T') {
                puts("\nTerima Kasih Telah Mencoba!!!");
                getch();
                break;
            }
            else continue;
        }
    }
}
