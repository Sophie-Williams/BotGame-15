#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define atas 1
#define kiri 2
#define bawah 3
#define kanan 4

#define true 1
#define false 0
#define caption " ----------------\n// GAME PUZZLE //\n----------------\n"

#define fieldSize 3
#define WINDOWS 1

void clrscr() {
  #ifdef WINDOWS
  system("cls");
  #define sleep(s) Sleep((s)*100);
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}

char field[fieldSize][fieldSize];
char field2[fieldSize][fieldSize];
int gerak[4];
unsigned int seed;
int x, y;

int acak(int i);
void initField(int movement);
void move(int arah);
void generateOutput();
//kamus
void copyField();
void moveTemp(int arah);
int cekUrut();
int TZero(char field,char kor);//menentukan dimana koordinat 0 berada. ex 0 = [0-2,]
int HitungUrutFieldTemp();
int HitungUrut(char field,char field2);
int HitungJarak();
void AllowMove(char field, char field2, int X, int Y);

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

//bot game start
//tentukan letak keping "0"
int TZero(char field[3][3],char kor){
	int c, d;
	int nilai;
    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            if ((kor == 'X') and (field[c][d] == ' ')) {
                nilai = c;
                }
            else if((kor == 'Y')and(field[c][d] == ' ')){
            	nilai = d;
			}
        }
    }
    return(nilai);
}
//bagian akhir
//tentukan boleh move ke mana
//hitung ke-TIDAK-sesuaian
int HitungUrut(char field[3][3], char field2[3][3]) {
    int c, d,jum;
	jum = 0;
    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            if (field[c][d] != field2[c][d]) {
                jum += 1;
				}
        }
    }
    return(jum);
}
//bagian akhir

main() {
    int i, j, k, level,jumlah,loop;
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
        puts("\t1. Lvl 1");
        puts("\t2. Lvl 2");
        puts("\t3. Lvl 3");
        puts("\t4. Lvl 4");
        puts("\t5. Lvl 5");
        puts("\t6. Lvl 6");
        puts("\t7. Lvl 7");
        puts("\t8. Lvl 8");
        puts("\t9. Lvl 9");
        puts("\t10. Lvl 10");
        printf("Pilih Level yang akan dimainkan : ");
        scanf("%i", &level);
        
        switch (level) {
            case 1 :
                initField(1);
                break;
            case 2 :
                initField(3);
                break;
            case 3 :
                initField(5);
                break;
            case 4 :
                initField(7);
                break;
            case 5 :
                initField(11);
                break;
            case 6 :
                initField(13);
                break;
            case 7 :
                initField(17);
                break;
            case 8 :
                initField(19);
                break;
            case 9 :
                initField(23);
                break;
            case 10 :
                initField(31);
                break;
            default :
                puts("Level salah!!");
                getch();
                continue;
        }
        system("cls");
        	int nilai,X,Y;
			generateOutput();
			printf("Game akan dimulai .. \n");
			sleep(10);
			printf("3 .. \n");
			sleep(10);
			printf("2 .. \n");
			sleep(10);
			printf("1 .. \n");
			sleep(10);
			//start
			int pilih,TempNilai,loop;
				loop = 0;
				bool moveleft,moveright,moveup,movedown;
				moveleft = moveright = moveup = movedown = true;
				while((cekUrut()==false)and(loop<=900)){
				pilih = 99; //kirim pilihan status default ke atas
				X = TZero(field,'X');
				Y = TZero(field,'Y');
				TempNilai = HitungUrut(field,field2);
				switch(X){
					case 0 : 
					moveup = false;
					break;
					case 2 :
					movedown = false;
					break;
				}
				switch(Y){
					case 0 :
					moveleft = false;
					break;
					case 2 :
					moveright = false;
					break;
				}
				if(moveup == true){
					move(atas);
					if(TempNilai >= HitungUrut(field,field2)or(pilih == 99)){
					TempNilai = HitungUrut(field,field2);
					pilih = 0;
					}
					move(bawah);
				}
				if(movedown == true){
					move(bawah);
					if(TempNilai >= HitungUrut(field,field2)or(pilih == 99)){
					TempNilai = HitungUrut(field,field2);
					pilih = 1;
					}
					move(atas);
				}
				if(moveleft == true){
					move(kiri);
					if(TempNilai >= HitungUrut(field,field2)or(pilih == 99)){
					TempNilai = HitungUrut(field,field2);
					pilih = 2;
					}
					move(kanan);
				}
				if(moveright == true){
					move(kanan);
					if(TempNilai >= HitungUrut(field,field2)or(pilih == 99)){
					TempNilai = HitungUrut(field,field2);
					pilih = 3;
					}
					move(kiri);
				}
				switch(pilih) {
					case 0 :
						move(atas);
						movedown = false;
						moveup = true;
						moveright = true;
						moveleft = true;
						break;
					case 1 :
						move(bawah);
						moveup = false;
						movedown = true;
						moveright = true;
						moveleft = true;
						break;
					case 2 :
						move(kiri);
						moveright = false;
						moveup = true;
						movedown = true;
						moveleft = true;
						break;
					case 3 :
						move(kanan);
						moveleft = false;
						moveup = true;
						moveright = true;
						movedown = true;
						break;
				}
				loop += 1;
				sleep(10);
		}
            if (cekUrut() == true) {
                puts("\nMENANG!!!");
                sleep(30);
            }
            else {
            	puts("\nKALAH!!!");
            	sleep(30);
			}
			
        if (key == 27) {
            printf("Apakah anda ingin keluar ?\n['y' utk keluar / 't' utk reset] : ");
            system("PAUSE");
            if (toupper(getchar()) == 'Y') break;
            else continue;
        } else {
            printf("Apakah anda ingin main lagi ? [y/t] : ");
            system("PAUSE");
			if (toupper(getchar()) == 'T') {
                puts("\nTerima Kasih Telah Mencoba!!!");
                getch();
                break;
            }
            else continue;
        }
    }
}
