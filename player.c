//#include<stdio.h>
//#include"player.h"

#include "board.h"
#include "stdio.h"

typedef struct {
	char NAMA[20];
	int ROLL;
	int PETAK;
	int SCORE;
	} player;

char angka[10] = "0123456789"

void KONSEKUENSI(player *BIDAK, Square KOTAK, int ROLL){
	*BIDAK.PETAK += ROLL;
	if (KOTAK[*BIDAK.PETAK].event == 'T'){
		for (int i = 0; i < 10; ++i){
			if (KOTAK[*BIDAK.PETAK].eventConnect == angka[i]){
				*BIDAK.PETAK = TujuanTangga[angka[i]];
			}
		}
	}else if (KOTAK[*BIDAK.PETAK].event == 'U'){
		for (int i = 0; i < 10; ++i){
			if (KOTAK[*BIDAK.PETAK].eventConnect == angka[i]){
				*BIDAK.PETAK = TujuanUlar[angka[i]];
			}
		}
	}
}

void PENAMAAN(player *BIDAK){
	fgets(*BIDAK.NAMA, 15, stdin);
}

