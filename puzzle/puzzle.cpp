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

//4key
#define keyUp 0x048
#define keyDown 0x050
#define keyLeft 0x04b
#define keyRight 0x04d

#define true 1
#define false 0

#define easy 2
#define medium 20
#define hard 30

#define caption " ----------------\n// GAME PUZZLE //\n----------------\n"

#define fieldSize 3
#define WINDOWS 1

void clrscr() {
  #ifdef WINDOWS
  system("cls");
  #define sleep(s) Sleep((s)*20);
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}

char field[fieldSize][fieldSize];
char field2[fieldSize][fieldSize];
char fieldCopy[fieldSize][fieldSize];
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
//move TEMP field
void moveTemp(int arah) {
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
        temp = fieldCopy[y][x];
        fieldCopy[y][x] = fieldCopy[yOld][xOld];
        fieldCopy[yOld][xOld] = temp;
    } else {
        x = xOld;
        y = yOld;
    }
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
int HitungUrutFieldTemp(){ 
	int c, d,jum;
	jum = 0;
    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            if (fieldCopy[c][d] != field2[c][d]) {
                jum += 1;
				}
        }
    }
    return(jum-1);
	
}
//hitung kesamaan dengan field sebelumnya

//meng-COPY field sebelumnya
void copyField() {
    int c, d;
    int match = true;

    for (c = 0; c <= (fieldSize - 1); c++) {
        for (d = 0; d <= (fieldSize - 1); d++) {
            fieldCopy[c][d] = field[c][d];
            }
        }
    }
// end bot program
void AllowMove(char field[3][3], char field2[3][3], int X, int Y){
	int pilih,TempNilai;
	TempNilai = 0;
	bool moveleft,moveright,moveup,movedown;
	moveleft = moveright = moveup = movedown = true;
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
		TempNilai = HitungUrut(field,field2);
		pilih = 0;
		move(bawah);
	}
	if(movedown == true){
		move(bawah);
		if(TempNilai <= HitungUrut(field,field2)){
		TempNilai = HitungUrut(field,field2);
		pilih = 1;
		}
		move(atas);
	}
	if(moveleft == true){
		move(kiri);
		if(TempNilai <= HitungUrut(field,field2)){
		TempNilai = HitungUrut(field,field2);
		pilih = 2;
	
		}
		move(kanan);
	}
	if(moveright == true){
		move(kanan);
		if(TempNilai <= HitungUrut(field,field2)){
		TempNilai = HitungUrut(field,field2);
		pilih = 3;
		}
		move(kiri);
	}
	switch(pilih) {
		case 0 :
			move(atas);
			break;
		case 1 :
			move(bawah);
			break;
		case 2 :
			move(kiri);
			break;
		case 3 :
			move(kanan);
			break;
	}
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
            case 98 :
            	//bot game triggered
            	initField(easy);
            	break;
            case 99 :
            	//bot game triggered
            	sleep(1);
            	initField(easy);
            	break;
            default :
                puts("Level salah!!");
                getch();
                continue;
        }
        
        system("cls");
        if(level==98){
        	int nilai,loop;
        	loop = 0;
			generateOutput();
			while((cekUrut() != true )and(loop < 100)){
			AllowMove(field,field2,TZero(field,'X'),TZero(field,'Y'));
            sleep(100);
        	loop += 1;
        	}
		}
		
		//kamus untuk program
        int ze,Hitung,HitungTemp,keZ; //var y untuk menghitung siapa yang paling sedikit mempunyai ke-Tidak sesuain
        bool selesai;
		if(level == 99){
		generateOutput();
            	sleep(5);
			//run this
			loop = 0;
			selesai = false;
			gerak[0] = 12;
			gerak[1] = 12;
			gerak[2] = 12;
			gerak[3] = 12;
			while((loop <= 100 )and(selesai == false)){
				HitungTemp = 99;
				keZ = 99;
				for(ze=0;ze<=3;ze++){	
				copyField(); 
					if(gerak[ze]==12){	
						switch(ze){
						    	case 0 :
				                    moveTemp(atas);
				                    break;
				                case 1 :
				                    moveTemp(bawah);
				                    break;
				                case 2 :
				                    moveTemp(kiri);
				                    break;
				                case 3 :
				                    moveTemp(kanan);
				                    break;
				            }
				            if(HitungUrut(fieldCopy,field) > 0 and HitungUrut(fieldCopy,field) < HitungUrut(field,field2)){
								Hitung = HitungUrutFieldTemp();
								if(Hitung <= HitungTemp){
									keZ = ze;//memasukan instruksi mana yang akan dimasukan.
									HitungTemp = Hitung;			
            				}
							}
						}
					}
					//pemilihan seleksi sudah benar
					//move error
            	generateOutput();
            	if(cekUrut()==true){
            		selesai == true;
            		printf("SELESAI ? \n");
            		sleep(10000);
				}
				loop += 1;
            } 
		}
			//end of bot
			//note :
			//masih salah dalam pengecekan kandidat yang bisa dilakukan.
		else{
		
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
                system("PAUSE");
                break;
            }
        }
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
